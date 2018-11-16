#!/usr/bin/env python
# -*- coding: utf-8 -*-
from vehicle import vehicle
from tracks import Tra
from math import sqrt, sin, cos, pi, atan, degrees
import numpy as np
import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.patches as patches
from scipy.io import savemat


class LaneKeeping:

    def __init__(self, track='Tra_1', dt=0.02, linear=False, fixed_speed=False, horizon=50, random=False,
                 seed=0, errorBound=0.3, F_side=0):
        """
        input:
        state:
        """
        self.fixed_speed = fixed_speed
        self.vehicle = vehicle(dt, linear, fixed_speed, horizon, random, seed, errorBound, F_side)
        self.track = Tra(track, dt, horizon)
        self.trajectory = []
        self.indexList = []

    def reset(self):
        # randomly generated initial state
        X0, Y0, phi0 = self.track.setStartPosYaw()
        self.vehicle.setStart(X0, Y0, phi0, initial_speed=10)
        # save the list for traj and index
        self.trajectory = [self.vehicle.state]
        self.indexList = [self.track.currentIndex]
        # get vehicle and track measurement
        obs, status = self.vehicle.getMeasurement(self.track)
        return obs

    '''
    def resetWithState(self, state):
        self.vehicle.state[0] = state[0]
        self.vehicle.state[1] = state[1]
        self.vehicle.state[2] = state[2]
        self.vehicle.state[3] = state[3]
        self.vehicle.state[4] = state[4]
        self.vehicle.state[5] = state[5]
        self.vehicle.state[6] = state[6]
        self.track.currentIndex, _ = self.track.searchClosestPt(self.vehicle.state[0], self.vehicle.state[1], self.track.currentIndex)

        self.trajectory = [self.vehicle.state]
        self.indexList = [self.track.currentIndex]
        obs, status = self.vehicle.getMeasurement(self.track)
        return obs
    '''

    def step(self, action, steps):
        # simulate the vehicle forward
        self.vehicle.simulate(action)
        # add the traj and index into list
        self.trajectory.append(self.vehicle.state)
        self.indexList.append(self.track.currentIndex)
        # get vehicle and track measurement
        ob, status = self.vehicle.getMeasurement(self.track)
        # calculate reward
        r = self.rewardFunc(ob, status)
        return ob, r, status != 0

    def rewardFunc(self, obs, status):
        """
        input: obs: vehicle states [v_x, v_y, r, d_f] + [ref] (see getRef in tracks.py)
               status: 1 if completed, 0 if normal driving, -1 if deviation large enough
        """
        q_error = 20
        q_relyaw = 2

        ref = obs[4:]
        error = ref[:int(ref.size/2)]
        relyaw = ref[int(ref.size/2):]

        cost = q_error * np.sum(error[0]**2 - 0.8**2) #+ q_relyaw * np.sum(relyaw[0]**2 - 0.8**2)
        v_along = obs[0] * cos(relyaw[0] * pi / 3) + obs[1] * sin(relyaw[0] * pi / 3)
        v_vertical = obs[1] * cos(relyaw[0] * pi / 3) - obs[0] *sin(relyaw[0] * pi / 3)
        reward = v_along - abs(v_vertical)

        if status == -1:
            terminalReward = -100
        elif status == 1:
            terminalReward = 0
        else:
            terminalReward = 0

        return - cost + 2 * reward + terminalReward

    def getRefPoint(self, ds):
        return self.track.getRefPoint((self.vehicle.state[0], self.vehicle.state[1]), self.vehicle.state[2], ds)

    def getActionSpaceDim(self):
        return self.vehicle.getActionSpaceDim()

    def getObservSpaceDim(self):
        return self.vehicle.getObservSpaceDim() + self.track.getRefSize()

    def getActionUpperBound(self):
        return self.vehicle.getActionUpperBound()

    def getActionLowerBound(self):

        return self.vehicle.getActionLowerBound()

    def writeTraj(self, dir):
        """
        write the current trajectory to a csv file
        input: dir : directory of the csv file (same with the video dir)
        return: null (save the csv file and plot speed profile)
        """
        f = open(dir + 'traj.csv', 'w')
        log_writer = csv.writer(f, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
        log_writer.writerow(['X', 'Y', 'phi', 'v_x', 'v_y', 'r', 'steering'])
        for i in range(len(self.trajectory)):
            log_writer.writerow(self.trajectory[i])
        f.close()
        # plot the speed profile
        phi_array = np.array(self.trajectory)[:, 2]
        for i in range(len(self.trajectory)):
            phi_array[i] = phi_array[i]% (2 * pi)
            if phi_array[i] > pi:
                phi_array[i] -= 2 * pi
        plt.plot(phi_array, 'g--', )
        #plt.plot(np.array(self.trajectory)[:, 3], '--')
        plt.plot(np.array(self.trajectory)[:, 4], 'b--')
        plt.plot(np.array(self.trajectory)[:, 5], 'r--')
        plt.plot(np.array(self.trajectory)[:, 6], 'y--')
        plt.show()

    def render(self, interval, itr, dir, show=0):
        NumtimeStep = len(self.trajectory)
        fig = plt.figure()
        ax = fig.add_subplot(1,1,1)
        plt.axis('scaled')
        trackPlot, = plt.plot([], [], color='green')
        trackPlot.set_zorder = 0
        tracksPlot = [trackPlot]
        tracks = [self.track]
        self.carPlot = patches.Rectangle((0,0), 3.8, 1.8, 0, color='red')
        self.carPlot.set_zorder = 1
        ax.add_patch(self.carPlot)
        plt.xlabel('X(m)')
        plt.ylabel('Y(m)')
        plt.ylim(-5, 5)
        animate = animation.FuncAnimation(fig, self.updatePlot, NumtimeStep, 
            fargs = (tracks, ax, tracksPlot), interval = interval)
        if show:
            plt.show()
        else:
            Writer = animation.writers['ffmpeg']
            writer = Writer(fps=50, metadata=dict(artist='Me'), bitrate=1800)
            name = dir + 'video' + str(itr) +".mp4"
            animate.save(name,writer=writer)
            data = {'trajectory': np.array(self.trajectory), 'indexList': np.array(self.indexList), 'trackX': self.track.x, 'trackY': self.track.y}
            savemat(dir + 'data' + str(itr) + '.mat', data)

    def updatePlot(self, num, tracks, ax, tracksPlot):
        self.carPlot = updatePlot(num, self.trajectory, self.indexList, tracks, ax, self.carPlot, tracksPlot)


class LaneChanging:

    def __init__(self, track='sine_curve', dt=0.02, linear=False, fixed_speed=False, horizon=50, random=False,
                 seed=0, errorBound=0.3, F_side=0):
        """
        Currently consider a simple deterministic case:
            change lane at 200 from 0 to +3
            change lane at 400 from +3 to 0
            change lane at 600 from 0 to -3
            change lane at 800 from -3 to 0
        """
        self.vehicle = vehicle(dt, linear, fixed_speed, horizon, random, seed, errorBound, F_side)
        self.track0 = Tra(track, dt, horizon)
        self.track1 = Tra(track, dt, horizon, deviation=3)
        self.track2 = Tra(track, dt, horizon, deviation=-3)
        self.trajectory = []
        self.indexList = []
        self.trackSelect = []
        if np.random.rand() > -1:
            self.left_change = True
        else:
            self.left_change = False

    def reset(self):
        # randomly generated initial state
        X0, Y0, phi0 = self.track0.setStartPosYaw()
        self.vehicle.setStart(X0, Y0, phi0, initial_speed=10)
        # save the list for traj and index
        self.trajectory = [self.vehicle.state]
        self.indexList = [self.track0.currentIndex]
        self.trackSelect = [0]
        # synchronize currentIndex
        self.track1.currentIndex = self.track0.currentIndex
        self.track2.currentIndex = self.track0.currentIndex
        # get vehicle and track measurement
        obs, status = self.vehicle.getMeasurement(self.track0)
        return obs

    def step(self, action, steps):
        # determine the objective track (assuming 0 <= steps <=1000)

        if steps < 200:
            track = self.track0
            self.trackSelect.append(0)
        elif steps < 400:
            track = self.track1
            self.trackSelect.append(1)
        elif steps < 600:
            track = self.track0
            self.trackSelect.append(0)
        elif steps < 800:
            track = self.track2
            self.trackSelect.append(2)
        else:
            track = self.track0
            self.trackSelect.append(0)
        """
        if self.left_change:
            if steps < 333:
                track = self.track0
                self.trackSelect.append(0)
            elif steps < 666:
                track = self.track1
                self.trackSelect.append(1)
            else:
                track = self.track0
                self.trackSelect.append(0)
        else:
            if steps < 333:
                track = self.track0
                self.trackSelect.append(0)
            elif steps < 666:
                track = self.track2
                self.trackSelect.append(2)
            else:
                track = self.track0
                self.trackSelect.append(0)
        """
        # simulate the vehicle forward
        self.vehicle.simulate(action)
        # add the traj and index into list
        self.trajectory.append(self.vehicle.state)
        self.indexList.append(track.currentIndex)
        # synchronize currentIndex
        self.track0.currentIndex = track.currentIndex
        self.track1.currentIndex = track.currentIndex
        self.track2.currentIndex = track.currentIndex
        # get vehicle and track measurement
        ob, status = self.vehicle.getMeasurement(track)
        # calculate reward
        r = self.rewardFunc(ob, status)
        return ob, r, status != 0

    def rewardFunc(self, obs, status):
        """
        input: obs: vehicle states [v_x, v_y, r, d_f] + [ref] (see getRef in tracks.py)
               status: 1 if completed, 0 if normal driving, -1 if deviation large enough
        """
        q_error = 20
        q_relyaw = 2

        ref = obs[4:]
        error = ref[:int(ref.size/2)]
        relyaw = ref[int(ref.size/2):]

        cost = q_error * np.sum(error[0]**2 - 0.8**2) #+ q_relyaw * np.sum(relyaw[0]**2 - 0.8**2)
        v_along = obs[0] * cos(relyaw[0] * pi / 3) + obs[1] * sin(relyaw[0] * pi / 3)
        v_vertical = obs[1] * cos(relyaw[0] * pi / 3) - obs[0] *sin(relyaw[0] * pi / 3)
        reward = v_along - abs(v_vertical)

        if status == -1:
            terminalReward = -1000
        elif status == 1:
            terminalReward = 0
        else:
            terminalReward = 0

        return - cost + 2 * reward + terminalReward

    def getActionSpaceDim(self):
        return self.vehicle.getActionSpaceDim()

    def getObservSpaceDim(self):
        return self.vehicle.getObservSpaceDim() + self.track0.getRefSize()

    def getActionUpperBound(self):
        return self.vehicle.getActionUpperBound()

    def getActionLowerBound(self):

        return self.vehicle.getActionLowerBound()

    def writeTraj(self, dir):
        """
        write the current trajectory to a csv file
        input: dir : directory of the csv file (same with the video dir)
        return: null (save the csv file and plot speed profile)
        """
        f = open(dir + 'traj.csv', 'w')
        log_writer = csv.writer(f, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
        log_writer.writerow(['X', 'Y', 'phi', 'v_x', 'v_y', 'r', 'steering'])
        for i in range(len(self.trajectory)):
            log_writer.writerow(self.trajectory[i])
        f.close()
        # plot the speed profile
        phi_array = np.array(self.trajectory)[:, 2]
        for i in range(len(self.trajectory)):
            phi_array[i] = phi_array[i]% (2 * pi)
            if phi_array[i] > pi:
                phi_array[i] -= 2 * pi
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)
        line1, = ax.plot(phi_array, 'g--', label='yaw angle phi')
        #line5, = ax.plot(np.array(self.trajectory)[:, 3], '--', label='speed')
        line2, = ax.plot(np.array(self.trajectory)[:, 4], 'b--', label='lateral speed v_y')
        line3, = ax.plot(np.array(self.trajectory)[:, 5], 'r--', label='yaw rate r')
        line4, = ax.plot(np.array(self.trajectory)[:, 6], 'y--', label='steering angle d_f')
        ax.legend()
        plt.show()

    def render(self, interval, itr, dir, show=0):
        NumtimeStep = len(self.trajectory)
        fig = plt.figure()
        ax = fig.add_subplot(1,1,1)
        plt.axis('scaled')
        track0Plot, = plt.plot([], [], color='green')
        track0Plot.set_zorder = 0
        track1Plot, = plt.plot([], [], color='green')
        track1Plot.set_zorder = 0
        track2Plot, = plt.plot([], [], color='green')
        track2Plot.set_zorder = 0
        tracksPlot = [track0Plot, track1Plot, track2Plot]
        tracks = [self.track0, self.track1, self.track2]
        self.carPlot = patches.Rectangle((0,0), 3.8, 1.8, 0, color='green')
        self.carPlot.set_zorder = 1
        ax.add_patch(self.carPlot)
        plt.xlabel('X(m)')
        plt.ylabel('Y(m)')
        plt.ylim(-5, 5)
        animate = animation.FuncAnimation(fig, self.updatePlot, NumtimeStep,
            fargs = (tracks, ax, tracksPlot), interval = interval)
        if show:
            plt.show()
        else:
            Writer = animation.writers['ffmpeg']
            writer = Writer(fps=50, metadata=dict(artist='Me'), bitrate=1800)
            name = dir + 'video' + str(itr) +".mp4"
            animate.save(name,writer=writer)
            data = {'trajectory': np.array(self.trajectory), 'indexList': np.array(self.indexList), 'trackX': self.track0.x, 'trackY': self.track0.y}
            savemat(dir + 'data' + str(itr) + '.mat', data)

    def updatePlot(self, num, tracks, ax, tracksPlot):
        self.carPlot = updatePlot(num, self.trajectory, self.indexList, tracks, ax, self.carPlot, tracksPlot, self.trackSelect)

class ObstacleAvoiding:

    def __init__(self, track='sine_curve', dt=0.02, linear=False, fixed_speed=False, horizon=50, random=False,
                 seed=0, errorBound=0.3, F_side=0):
        """
        input:
        state:
        """
        self.vehicle = vehicle(dt, linear, fixed_speed, horizon, random, seed, errorBound, F_side)
        self.track0 = Tra(track, dt, horizon)
        self.track1 = Tra(track, dt, horizon, deviation=3)
        self.trajectory = []
        self.indexList = []
        self.obstacle_traj = []

    def reset(self):
        # randomly generated initial state
        X0, Y0, phi0 = self.track0.setStartPosYaw()
        self.vehicle.setStart(X0, Y0, phi0, initial_speed=10)
        # synchronize currentIndex
        self.track1.currentIndex = self.track0.currentIndex
        # initiate obstacle position
        self.track0.setStartPosObstacle()
        # save the list for traj and index
        self.trajectory = [self.vehicle.state]
        self.indexList = [self.track0.currentIndex]
        self.obstacle_traj = [np.array([self.track0.x[self.track0.obstacleIndex],
                                        self.track0.y[self.track0.obstacleIndex],
                                        self.track0.psi[self.track0.obstacleIndex]])]
        # get vehicle and track measurement
        obs0, status0 = self.vehicle.getMeasurement(self.track0)
        obs1, status1 = self.vehicle.getMeasurement(self.track1)
        obs = np.append(obs0, obs1[4:])
        return obs

    def step(self, action, steps, ob_v=0):
        # simulate the vehicle and the obstacle forward
        self.vehicle.simulate(action)
        self.track0.obstacleMove(ob_v)
        # synchronize currentIndex
        self.track1.currentIndex = self.track0.currentIndex
        # add the traj and index into list
        self.trajectory.append(self.vehicle.state)
        self.indexList.append(self.track0.currentIndex)
        self.obstacle_traj.append(np.array([self.track0.x[self.track0.obstacleIndex],
                                            self.track0.y[self.track0.obstacleIndex],
                                            self.track0.psi[self.track0.obstacleIndex]]))
        # get vehicle and track measurement
        ob0, status0 = self.vehicle.getMeasurement(self.track0)
        ob1, status1 = self.vehicle.getMeasurement(self.track1)
        ob = np.append(ob0, ob1[4:])
        status = np.hstack((status0, status1))
        # calculate reward
        r = self.rewardFunc(ob, status)
        return ob, r, status[0] != 0 or status[1] != 0 or status[2] != 0

    def rewardFunc(self, obs, status):
        """
        input: obs: vehicle states [v_x, v_y, r, d_f] + [ref] (see getRef in tracks.py)
               status: 1 if completed, 0 if normal driving, -1 if deviation large enough
        """
        q_error = 20
        q_relyaw = 2

        ref0 = obs[4:4+self.track0.getRefSize()]
        error0 = ref0[:int(ref0.size/2)]
        relyaw0 = ref0[int(ref0.size/2):]
        ref1 = obs[7+self.track0.getRefSize():]
        error1 = ref1[:int(ref1.size/2)]
        relyaw1 = ref1[int(ref1.size/2):]

        cost = q_error * np.sum(min(error0[0] ** 2, error1[0]**2) - 0.8 ** 2)  # + q_relyaw * np.sum(relyaw[0]**2 - 0.8**2)
        v_along = obs[0] * cos(relyaw0[0] * pi / 3) + obs[1] * sin(relyaw0[0] * pi / 3)
        v_vertical = obs[1] * cos(relyaw0[0] * pi / 3) - obs[0] * sin(relyaw0[0] * pi / 3)
        reward = v_along - abs(v_vertical)

        if status[0] or status[1] or status[2] == -1:
            terminalReward = -1000
        elif status[0] == 1:
            terminalReward = 0
        else:
            terminalReward = 0

        return - cost + 2 * reward + terminalReward

    def getActionSpaceDim(self):
        return self.vehicle.getActionSpaceDim()

    def getObservSpaceDim(self):
        return self.vehicle.getObservSpaceDim() + \
               self.track0.getRefSize() + \
               self.track0.getRefObSize() + \
               self.track1.getRefSize()


    def getActionUpperBound(self):
        return self.vehicle.getActionUpperBound()

    def getActionLowerBound(self):
        return self.vehicle.getActionLowerBound()

    def writeTraj(self, dir):
        """
        write the current trajectory to a csv file
        input: dir : directory of the csv file (same with the video dir)
        return: null (save the csv file and plot speed profile)
        """
        f = open(dir + 'traj.csv', 'w')
        log_writer = csv.writer(f, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
        log_writer.writerow(['X', 'Y', 'phi', 'v_x', 'v_y', 'r', 'steering'])
        for i in range(len(self.trajectory)):
            log_writer.writerow(self.trajectory[i])
        f.close()
        # plot the speed profile
        plt.plot(np.array(self.trajectory)[:, 2], 'g--')
        plt.plot(np.array(self.trajectory)[:, 3], '--')
        plt.plot(np.array(self.trajectory)[:, 4], 'b--')
        plt.plot(np.array(self.trajectory)[:, 5], 'r--')
        plt.plot(np.array(self.trajectory)[:, 6], 'y--')
        plt.show()

    def render(self, interval, itr, dir, show=0):
        NumtimeStep = len(self.trajectory)
        fig = plt.figure()
        ax = fig.add_subplot(1,1,1)
        plt.axis('scaled')
        track0Plot, = plt.plot([], [], color='green')
        track0Plot.set_zorder = 0
        track1Plot, = plt.plot([], [], color='green')
        track1Plot.set_zorder = 0
        tracksPlot = [track0Plot, track1Plot]
        tracks = [self.track0, self.track1]
        self.carPlot = patches.Rectangle((0,0), 3.8, 1.8, 0, color='green')
        self.carPlot.set_zorder = 1
        obstaclePlot = patches.Rectangle((0,0), 3.8, 1.8, 0, color='red')
        obstaclePlot.set_zorder = 1
        ax.add_patch(self.carPlot)
        ax.add_patch(obstaclePlot)
        plt.xlabel('X(m)')
        plt.ylabel('Y(m)')
        plt.ylim(-5, 5)
        animate = animation.FuncAnimation(fig, self.updatePlot, NumtimeStep,
            fargs = (tracks, ax, tracksPlot, obstaclePlot), interval = interval)
        if show:
            plt.show()
        else:
            Writer = animation.writers['ffmpeg']
            writer = Writer(fps=50, metadata=dict(artist='Me'), bitrate=1800)
            name = dir + 'video' + str(itr) +".mp4"
            animate.save(name,writer=writer)
            data = {'trajectory': np.array(self.trajectory), 'indexList': np.array(self.indexList), 'trackX': self.track0.x, 'trackY': self.track0.y}
            savemat(dir + 'data' + str(itr) + '.mat', data)

    def updatePlot(self, num, tracks, ax, tracksPlot, obstaclePlot):
        self.carPlot = updatePlot(num, self.trajectory, self.indexList, tracks, ax, self.carPlot, tracksPlot, None, self.obstacle_traj, obstaclePlot)

class LC_based_OA:
    """
    lane changing based obstacle avoidance
    """

    def __init__(self, track='sine_curve', dt=0.02, linear=False, fixed_speed=False, horizon=50, random=False,
                 seed=0, errorBound=0.3, F_side=0):
        self.vehicle = vehicle(dt, linear, fixed_speed, horizon, random, seed, errorBound, F_side)
        self.track0 = Tra(track, dt, horizon)
        self.track1 = Tra(track, dt, horizon, deviation=3)
        self.trajectory = []
        self.indexList = []
        self.trackSelect = []
        self.obstacle_traj = []

    def reset(self):
        # randomly generated initial state
        X0, Y0, phi0 = self.track0.setStartPosYaw()
        self.vehicle.setStart(X0, Y0, phi0, initial_speed=10)
        # synchronize currentIndex
        self.track1.currentIndex = self.track0.currentIndex
        # initiate obstacle position
        self.track0.setStartPosObstacle()
        # save the list for traj and index
        self.trajectory = [self.vehicle.state]
        self.indexList = [self.track0.currentIndex]
        self.trackSelect = [0]
        self.obstacle_traj = [np.array([self.track0.x[self.track0.obstacleIndex],
                                        self.track0.y[self.track0.obstacleIndex],
                                        self.track0.psi[self.track0.obstacleIndex]])]
        # get vehicle and track measurement
        obs0, status0 = self.vehicle.getMeasurement(self.track0)
        obs1, status1 = self.vehicle.getMeasurement(self.track1)
        obs = np.append(obs0, obs1[4:])
        return obs

    def step(self, action, steps, ob_v=0):
        # determine the objective track (assuming 0 <= steps <=1000)
        if action[2] > -0.5: # the last figure in obstacle indicates the selected lane
            track = self.track0
            self.trackSelect.append(0)
        else:
            track = self.track1
            self.trackSelect.append(1)
        # simulate the vehicle and the obstacle forward
        self.vehicle.simulate(action[:2])
        self.track0.obstacleMove(ob_v)
        # add the traj and index into list
        self.trajectory.append(self.vehicle.state)
        self.indexList.append(self.track0.currentIndex)
        self.obstacle_traj.append(np.array([self.track0.x[self.track0.obstacleIndex],
                                            self.track0.y[self.track0.obstacleIndex],
                                            self.track0.psi[self.track0.obstacleIndex]]))
        # synchronize currentIndex
        self.track0.currentIndex = track.currentIndex
        self.track1.currentIndex = track.currentIndex
        # get vehicle and track measurement
        ob0, status0 = self.vehicle.getMeasurement(self.track0)
        ob1, status1 = self.vehicle.getMeasurement(self.track1)
        ob = np.append(ob0, ob1[4:])
        status = np.hstack((status0, status1))
        # calculate reward
        r = self.rewardFunc(ob, status)
        return ob, r, status[0] != 0 or status[1] != 0 or status[2] != 0

    def rewardFunc(self, obs, status):
        """
        input: obs: vehicle states [v_x, v_y, r, d_f] + [ref0] + [refOb0] + [ref1]
               status: 1 if completed, 0 if normal driving, -1 if deviation large enough
        """
        q_error = 20
        q_relyaw = 2

        ref = []
        error = []
        relyaw = []

        ref.append(obs[4:4+self.track0.getRefSize()])
        ref.append(obs[7+self.track0.getRefSize():])

        error.append(ref[0][:int(ref[0].size/2)])
        error.append(ref[1][:int(ref[1].size/2)])

        relyaw.append(ref[0][int(ref[0].size/2):])
        relyaw.append(ref[1][int(ref[1].size/2):])

        selected_lane = self.trackSelect[-1]
        cost = q_error * np.sum(error[selected_lane][0] ** 2 - 0.8 ** 2)  # + q_relyaw * np.sum(relyaw[0]**2 - 0.8**2)
        v_along = obs[0] * cos(relyaw[selected_lane][0] * pi / 3) + obs[1] * sin(relyaw[selected_lane][0] * pi / 3)
        v_vertical = obs[1] * cos(relyaw[selected_lane][0] * pi / 3) - obs[0] * sin(relyaw[selected_lane][0] * pi / 3)
        reward = v_along - abs(v_vertical)

        if status[0] or status[1] or status[2] == -1:
            terminalReward = -1000
        elif status[0] == 1:
            terminalReward = 0
        else:
            terminalReward = 0

        return - cost + 2 * reward + terminalReward

    def getActionSpaceDim(self):
        return self.vehicle.getActionSpaceDim() + 1

    def getObservSpaceDim(self):
        return self.vehicle.getObservSpaceDim() + \
               self.track0.getRefSize() + \
               self.track0.getRefObSize() + \
               self.track1.getRefSize()

    def getActionUpperBound(self):
        return np.hstack((self.vehicle.getActionUpperBound(), np.array([1])))

    def getActionLowerBound(self):
        return np.hstack((self.vehicle.getActionLowerBound(), np.array([-1])))

    def writeTraj(self, dir):
        """
        write the current trajectory to a csv file
        input: dir : directory of the csv file (same with the video dir)
        return: null (save the csv file and plot speed profile)
        """
        f = open(dir + 'traj.csv', 'w')
        log_writer = csv.writer(f, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
        log_writer.writerow(['X', 'Y', 'phi', 'v_x', 'v_y', 'r', 'steering'])
        for i in range(len(self.trajectory)):
            log_writer.writerow(self.trajectory[i])
        f.close()
        # plot the speed profile
        phi_array = np.array(self.trajectory)[:, 2]
        for i in range(len(self.trajectory)):
            phi_array[i] = phi_array[i]% (2 * pi)
            if phi_array[i] > pi:
                phi_array[i] -= 2 * pi
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)
        line1, = ax.plot(phi_array, 'g--', label='yaw angle phi')
        # plt.plot(np.array(self.trajectory)[:, 3], '--')
        line2, = ax.plot(np.array(self.trajectory)[:, 4], 'b--', label='lateral speed v_y')
        line3, = ax.plot(np.array(self.trajectory)[:, 5], 'r--', label='yaw rate r')
        line4, = ax.plot(np.array(self.trajectory)[:, 6], 'y--', label='steering angle d_f')
        ax.legend()
        plt.show()

    def render(self, interval, itr, dir, show=0):
        NumtimeStep = len(self.trajectory)
        fig = plt.figure()
        ax = fig.add_subplot(1,1,1)
        plt.axis('scaled')
        track0Plot, = plt.plot([], [], color='green')
        track0Plot.set_zorder = 0
        track1Plot, = plt.plot([], [], color='green')
        track1Plot.set_zorder = 0
        track2Plot, = plt.plot([], [], color='green')
        track2Plot.set_zorder = 0
        tracksPlot = [track0Plot, track1Plot, track2Plot]
        tracks = [self.track0, self.track1]
        self.carPlot = patches.Rectangle((0,0), 3.8, 1.8, 0, color='green')
        self.carPlot.set_zorder = 1
        obstaclePlot = patches.Rectangle((0,0), 3.8, 1.8, 0, color='red')
        obstaclePlot.set_zorder = 1
        ax.add_patch(self.carPlot)
        ax.add_patch(obstaclePlot)
        plt.xlabel('X(m)')
        plt.ylabel('Y(m)')
        plt.ylim(-5, 5)
        animate = animation.FuncAnimation(fig, self.updatePlot, NumtimeStep,
            fargs = (tracks, ax, tracksPlot, obstaclePlot), interval = interval)
        if show:
            plt.show()
        else:
            Writer = animation.writers['ffmpeg']
            writer = Writer(fps=50, metadata=dict(artist='Me'), bitrate=1800)
            name = dir + 'video' + str(itr) +".mp4"
            animate.save(name,writer=writer)
            data = {'trajectory': np.array(self.trajectory), 'indexList': np.array(self.indexList), 'trackX': self.track0.x, 'trackY': self.track0.y}
            savemat(dir + 'data' + str(itr) + '.mat', data)
    
    def updatePlot(self, num, tracks, ax, tracksPlot, obstaclePlot):
        self.carPlot = updatePlot(num, self.trajectory, self.indexList, tracks, ax, self.carPlot, tracksPlot, self.trackSelect, self.obstacle_traj, obstaclePlot)

class LC_based_OA_hierarchical:
    """
    lane changing based obstacle avoidance
    """

    def __init__(self, track='sine_curve', dt=0.02, linear=False, fixed_speed=False, horizon=50, random=False,
                 seed=0, errorBound=0.3, F_side=0):
        self.vehicle = vehicle(dt, linear, fixed_speed, horizon, random, seed, errorBound, F_side)
        self.track0 = Tra(track, dt, horizon)
        self.track1 = Tra(track, dt, horizon, deviation=3)
        self.trajectory = []
        self.indexList = []
        self.trackSelect = []
        self.obstacle_traj = []

    def reset(self):
        # randomly generated initial state
        X0, Y0, phi0 = self.track0.setStartPosYaw()
        self.vehicle.setStart(X0, Y0, phi0, initial_speed=10)
        # synchronize currentIndex
        self.track1.currentIndex = self.track0.currentIndex
        # initiate obstacle position
        self.track0.setStartPosObstacle()
        # save the list for traj and index
        self.trajectory = [self.vehicle.state]
        self.indexList = [self.track0.currentIndex]
        self.trackSelect = [0]
        self.obstacle_traj = [np.array([self.track0.x[self.track0.obstacleIndex],
                                        self.track0.y[self.track0.obstacleIndex],
                                        self.track0.psi[self.track0.obstacleIndex]])]
        # get vehicle and track measurement
        obs0, status0 = self.vehicle.getMeasurement(self.track0)
        return obs0[:self.getObservSpaceDim()]

    def step(self, action, steps, ob_v=10):
        # determine the objective track (assuming 0 <= steps <=1000)
        ob0, status0 = self.vehicle.getMeasurement(self.track0)
        if ob0[self.getObservSpaceDim()]:
            track = self.track1
            self.trackSelect.append(1)
        else:
            track = self.track0
            self.trackSelect.append(0)
        # simulate the vehicle and the obstacle forward
        self.vehicle.simulate(action)
        self.track0.obstacleMove(ob_v)
        # add the traj and index into list
        self.trajectory.append(self.vehicle.state)
        self.indexList.append(track.currentIndex)
        self.obstacle_traj.append(np.array([self.track0.x[self.track0.obstacleIndex],
                                            self.track0.y[self.track0.obstacleIndex],
                                            self.track0.psi[self.track0.obstacleIndex]]))
        # synchronize currentIndex
        self.track0.currentIndex = track.currentIndex
        self.track1.currentIndex = track.currentIndex
        # get vehicle and track measurement
        ob, _ = self.vehicle.getMeasurement(track)
        _, status0 = self.vehicle.getMeasurement(self.track0)
        _, status1 = self.vehicle.getMeasurement(self.track1)
        status = np.hstack((status0, status1))
        # calculate reward
        r = self.rewardFunc(ob, status)
        return ob[:self.getObservSpaceDim()], r, status[0] != 0 or status[1] != 0 or status[2] != 0

    def rewardFunc(self, obs, status):
        """
        input: obs: vehicle states [v_x, v_y, r, d_f] + [ref0] + [refOb0] + [ref1]
               status: 1 if completed, 0 if normal driving, -1 if deviation large enough
        """
        q_error = 20
        q_relyaw = 2

        ref = obs[4:]
        error = ref[:int(ref.size/2)]
        relyaw = ref[int(ref.size/2):]

        cost = q_error * np.sum(error[0]**2 - 0.8**2) #+ q_relyaw * np.sum(relyaw[0]**2 - 0.8**2)
        v_along = obs[0] * cos(relyaw[0] * pi / 3) + obs[1] * sin(relyaw[0] * pi / 3)
        v_vertical = obs[1] * cos(relyaw[0] * pi / 3) - obs[0] *sin(relyaw[0] * pi / 3)
        reward = v_along - abs(v_vertical)

        if status[0] or status[1] or status[2] == -1:
            terminalReward = -1000
        elif status[0] == 1:
            terminalReward = 0
        else:
            terminalReward = 0

        return - cost + 2 * reward + terminalReward

    def getActionSpaceDim(self):
        return self.vehicle.getActionSpaceDim()

    def getObservSpaceDim(self):
        return self.vehicle.getObservSpaceDim() + self.track0.getRefSize()

    def getActionUpperBound(self):
        return self.vehicle.getActionUpperBound()

    def getActionLowerBound(self):
        return self.vehicle.getActionLowerBound()

    def writeTraj(self, dir):
        """
        write the current trajectory to a csv file
        input: dir : directory of the csv file (same with the video dir)
        return: null (save the csv file and plot speed profile)
        """
        f = open(dir + 'traj.csv', 'w')
        log_writer = csv.writer(f, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
        log_writer.writerow(['X', 'Y', 'phi', 'v_x', 'v_y', 'r', 'steering'])
        for i in range(len(self.trajectory)):
            log_writer.writerow(self.trajectory[i])
        f.close()
        # plot the speed profile
        phi_array = np.array(self.trajectory)[:, 2]
        for i in range(len(self.trajectory)):
            phi_array[i] = phi_array[i]% (2 * pi)
            if phi_array[i] > pi:
                phi_array[i] -= 2 * pi
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)
        line1, = ax.plot(phi_array, 'g--', label='yaw angle phi')
        #line5, = ax.plot(np.array(self.trajectory)[:, 3], '--', label='speed')
        line2, = ax.plot(np.array(self.trajectory)[:, 4], 'b--', label='lateral speed v_y')
        line3, = ax.plot(np.array(self.trajectory)[:, 5], 'r--', label='yaw rate r')
        line4, = ax.plot(np.array(self.trajectory)[:, 6], 'y--', label='steering angle d_f')
        ax.legend()
        plt.show()

    def render(self, interval, itr, dir, show=0):
        NumtimeStep = len(self.trajectory)
        fig = plt.figure()
        ax = fig.add_subplot(1,1,1)
        plt.axis('scaled')
        track0Plot, = plt.plot([], [], color='green')
        track0Plot.set_zorder = 0
        track1Plot, = plt.plot([], [], color='green')
        track1Plot.set_zorder = 0
        track2Plot, = plt.plot([], [], color='green')
        track2Plot.set_zorder = 0
        tracksPlot = [track0Plot, track1Plot, track2Plot]
        tracks = [self.track0, self.track1]
        self.carPlot = patches.Rectangle((0,0), 3.8, 1.8, 0, color='green')
        self.carPlot.set_zorder = 1
        obstaclePlot = patches.Rectangle((0,0), 3.8, 1.8, 0, color='red')
        obstaclePlot.set_zorder = 1
        ax.add_patch(self.carPlot)
        ax.add_patch(obstaclePlot)
        plt.xlabel('X(m)')
        plt.ylabel('Y(m)')
        plt.ylim(-5, 5)
        animate = animation.FuncAnimation(fig, self.updatePlot, NumtimeStep,
            fargs = (tracks, ax, tracksPlot, obstaclePlot), interval = interval)
        if show:
            plt.show()
        else:
            Writer = animation.writers['ffmpeg']
            writer = Writer(fps=50, metadata=dict(artist='Me'), bitrate=1800)
            name = dir + 'video' + str(itr) +".mp4"
            animate.save(name,writer=writer)
            data = {'trajectory': np.array(self.trajectory), 'indexList': np.array(self.indexList), 'trackX': self.track0.x, 'trackY': self.track0.y}
            savemat(dir + 'data' + str(itr) + '.mat', data)

    def updatePlot(self, num, tracks, ax, tracksPlot, obstaclePlot):
        self.carPlot = updatePlot(num, self.trajectory, self.indexList, tracks, ax, self.carPlot, tracksPlot, self.trackSelect, self.obstacle_traj, obstaclePlot)


def updatePlot(num, traj, indexList, tracks, ax, carPlot, tracksPlot, trackselect=None,
               obstacle_traj=None, obstaclePlot=None):
    """
    the function used to update one frame of the plot
    :param num: steps index in a trajectory
    :param traj: the traj list recording the host vehicle's position and yaw
    :param indexList: the list storing the vehicle's position in the track
    :param tracks: the list of tracks to be ploted
    :param carPlot: the plot variable of the vehicle (rectangular)
    :param tracksPlot: the list of the plots pg the tracks (lines)
    :param trackselect: the list storing hte selected track
    :param obstacle_traj: the list storing the obstacle traj, including the position and yaw
    :param obstaclePlot:  the list storing the obstacle plot variable (rectangular)
    :return: void
    """
    stateK = traj[num]
    x = stateK[0] - sqrt(1.8**2+3.8**2)/2 * cos(stateK[2]+atan(1.8/3.8))
    y = stateK[1] - sqrt(1.8**2+3.8**2)/2 * sin(stateK[2]+atan(1.8/3.8))
    index = indexList[num]
    # plot lanes
    for i, track, trackPlot in zip(range(len(tracks)), tracks, tracksPlot):
        if trackselect:
            if trackselect[num] == i:
                trackPlot.set_color('green')
            else:
                trackPlot.set_color('red')
        TrackX = track.x[max(0, index - 500):min(track.size, index + 1001)]
        TrackY = track.y[max(0, index - 500):min(track.size, index + 1001)]
        trackData = np.array([TrackX, TrackY])
        trackPlot.set_data(trackData)
        trackPlot.axes.set_xlim(TrackX[0], TrackX[-1])
        trackPlot.set_zorder = 0
    # plot vehicle
    stateK = traj[num]
    x = stateK[0] - sqrt(1.8**2+3.8**2)/2 * cos(stateK[2]+atan(1.8/3.8))
    y = stateK[1] - sqrt(1.8**2+3.8**2)/2 * sin(stateK[2]+atan(1.8/3.8))
    carPlot.remove()
    carPlot = patches.Rectangle((x,y), 3.8, 1.8, degrees(stateK[2]), color='green')
    carPlot.set_zorder = 1
    ax.add_patch(carPlot)
    # plot obstacle
    if obstaclePlot and obstacle_traj:
        stateOb = obstacle_traj[num]
        xOb = stateOb[0] - sqrt(1.8 ** 2 + 3.8 ** 2) / 2 * cos(stateOb[2] + atan(1.8 / 3.8))
        yOb = stateOb[1] - sqrt(1.8 ** 2 + 3.8 ** 2) / 2 * sin(stateOb[2] + atan(1.8 / 3.8))
        obstaclePlot.set_xy((xOb, yOb))
        obstaclePlot._angle = degrees(stateOb[2])
        obstaclePlot.visible = True

    return carPlot

