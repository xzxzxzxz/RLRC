#!/usr/bin/env python
# -*- coding: utf-8 -*-
# define the track class
import scipy.io 
import scipy.optimize
import numpy as np
from math import sqrt, cos, sin, tan, pi
import os, rospkg
class Tra:

    def __init__(self, name, dt=0.02, horizon=50, deviation=0, numPrePts=2, threshold=5):
        """
        track class
        input: track.mat filename
               dt: timestep, must match the dt in vehicle class
               horizon: search area, must match the horizon in vehicle class
               deviation: for a parallel lane, indicates lateral deviation with base lane
               numPrePts: num of predicted waypoints at a certain timestep
               threshold: if farther away from lane than threshold, then terminate the episode
        state: x, y, psi for the watpoints
               size: length of the reference trajectory
               threshold: if deviation larger than threshold then report failure
               currentIndex: index of waypoint corresponding to current vehicle position
        """
        rospack = rospkg.RosPack()
        waypoints_mat = scipy.io.loadmat(os.path.join(rospack.get_path("planning_policy"), "src", "Tra_1.mat"))[name]
        self.x     = waypoints_mat[0][:]
        self.y     = waypoints_mat[1][:] + deviation
        self.psi   = (waypoints_mat[2][:]) % (2 * pi)
        self.size  = waypoints_mat.shape[1]
        self.threshold = threshold
        self.longi_safe = 4
        self.later_safe = 2
        self.currentIndex = 0
        self.obstacleIndex = 0
        self.dt = dt
        self.horizon = horizon
        self.numPrePts = numPrePts

    def setStartPosYaw(self):
        """
        randomly choose a waypoint in the first 1/4 of the traj as starting point
        output: x, y, psi of the starting waypoint
        """
        self.currentIndex = np.random.random_integers(0, int(self.size/4))
        return self.x[self.currentIndex], self.y[self.currentIndex], self.psi[self.currentIndex]

    def setStartPosObstacle(self):
        """
        randomly choose a waypoint in the first 2/3 of the traj length after the currentIndex
        output: x, y of the obstacle

        Note: delta_index != 0, that is -> self,obstacleIndex==0 indicates no obstacle initiated
        """
        delta_index =  5000 # np.random.random_integers(1, int(self.size*2/3))
        self.obstacleIndex = self.currentIndex + delta_index
        return self.x[self.obstacleIndex], self.y[self.obstacleIndex]

    def setPosObstacle(self, index):
        self.obstacleIndex = index

    def getPosObstacle(self):
        return self.obstacleIndex

    def obstacleMove(self, v_x=0):
        """
        given the speed of the obstacle, get the new pos, and assign to self
        input:  v_x: the longtitudinal speed of the obstacle, default static obstacle
                self.dt: timestep
                self.horizon: search in +/- 10* horizon
        output: void
        """
        
        pX = self.x[self.obstacleIndex] + v_x * cos(self.psi[self.obstacleIndex]) * self.dt
        pY = self.y[self.obstacleIndex] + v_x * sin(self.psi[self.obstacleIndex]) * self.dt
        self.obstacleIndex, _ = self.searchClosestPt(pX, pY, standard_index=self.obstacleIndex)

    def getRef(self, position, phi, v_x):
        """
        get the reference position and angle of the vehicle with respect to the traj
        input: position: (x, y) current position of the vehicle
               phi: current yaw angle of the vehicle
               v_x: current longitudinal speed
               self.dt: timestep length of the vehicle simulator
               self.horizon: max num of timesteps to predict
        output: array(ref): first half: distance error | second half: normalized angle error
                            size = self.getRefSize() = 2 * self.numPrePts
                status：1 if completed, 0 if normal driving, -1 if deviation large enough
        """
        tList = self.dt * np.linspace(0, self.horizon, self.numPrePts)  # dt*array([0,horizon]) if numPrePts==2
        errorList = []
        relaAngList = []
        
        for t in tList:
            pX = position[0] + v_x * cos(phi) * t
            pY = position[1] + v_x * sin(phi) * t
            index, distanceMin = self.searchClosestPt(pX, pY, standard_index=self.currentIndex)
            
            if t == 0:
                self.currentIndex = index

            delta_x = self.x[index] - pX
            delta_y = self.y[index] - pY
            relYaw = (self.psi[index] - phi) % (2 * pi)
            if relYaw > pi:
                relYaw -= 2 * pi

            relY = - delta_x * sin(phi) + delta_y * cos(phi)  # + if traj left of vehicle, - else
            errorList.append(distanceMin / self.threshold * np.sign(relY))
            relaAngList.append(relYaw / (pi / 3))

        PreviewIndex = index 

        if abs(errorList[0]) > 1:
            status = -1
        elif PreviewIndex == self.size:    # size - currentIndex < horizon?
            status = 1
        else:
            status = 0

        ref = errorList + relaAngList
        return np.array(ref), status

    def getRefPoint(self, position, phi, ds):
        pX = position[0] + ds * cos(phi)
        pY = position[1] + ds * sin(phi)
        index, _ = self.searchClosestPt(pX, pY, standard_index=self.currentIndex)
        return (self.x[index], self.y[index], self.psi[index])

    def getRefObstacle(self, position, phi, v_x):
        """
        get the reference position and angle of the vehicle with respect to the obstacle
        input: position: (x, y) current position of the vehicle
               phi: current yaw angle of the vehicle
               v_x: current longitudinal speed
               self.dt: timestep length of the vehicle simulator
               self.horizon: max num of timesteps to predict
        output: array(ref): [vX_over_errX, err_x, err_y]
                status：0 if normal driving, -1 if hit the safety boundary
        """
        delta_x = self.x[self.obstacleIndex] - position[0]
        delta_y = self.y[self.obstacleIndex] - position[1]
        distSqr = delta_x**2 + delta_y**2
        err_y = (delta_y - delta_x * tan(phi))* cos(phi)
        err_x =  sqrt(distSqr - err_y**2)
        one_over_time_to_reach = v_x / sqrt(distSqr)
        if one_over_time_to_reach > 1:
            refOb = np.array([1, err_x, err_y])
        else:
            refOb = np.array([0, err_x, err_y])
        if abs(err_x) < self.longi_safe and abs(err_y) < self.later_safe:
            status = -1
        else:
            status = 0
        return refOb, status

    def searchClosestPt(self, pX, pY, standard_index):
        """
        search for the closest point with the designated point on the traj
        input:  pX, pY: accurate point position
                self.horizon: search in +/- 10* horizon
                standard_index: search around the standard index
        output: indexMin: closest traj point's index
                distMin:  distance from the closest traj point to the accurate point

        (one trick: only compare dist**2, save the time used to compute sqrt)
        (another trick: only consider waypoints with index in currentIndex +/- 10*horizon range)
        """
        indexMin = standard_index
        distSqrMin = (pX - self.x[standard_index])**2 + (pY - self.y[standard_index])**2
        for index in range(max(standard_index - self.horizon*10, 0), min(standard_index + self.horizon*10, self.size)):
            distSqr = (pX - self.x[index])**2 + (pY - self.y[index])**2
            if distSqr < distSqrMin:
                indexMin = index
                distSqrMin = distSqr
        return indexMin, sqrt(distSqrMin)


    def getRefSize(self):
        """
        returns the size of the 
        """
        return 2 * self.numPrePts

    def getRefObSize(self):
        return 3
