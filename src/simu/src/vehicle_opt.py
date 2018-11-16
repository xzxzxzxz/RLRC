#!/usr/bin/env python
# -*- coding: utf-8 -*-
from numpy import zeros, append, ones
import numpy as np
from math import cos, sin, pi
from scipy import stats
from dynamics_opt import f_6s
from dynamics_opt import f_st
import rospy

class vehicle:

    def __init__(self, dt, linear, fixed_speed, horizon, random, seed, errorBound, F_side=0):
        """
        vehicle model
        input: dt: timestep length
               linear: if true use linear model, else use nonlinear model
               what is horizon?
               random: boolean, randomize vehicle model
               seed: random seed, used as vehicle ID
rm
               errBound: bound of random number
               F_side: Y direction side force
        state: 7 dof: pos & vel [X, Y, phi, v_x, v_y, r] + steering [d_f]
        """
        self.dt = dt
        self.linear = linear
        self.fixed_speed = fixed_speed
        self.horizon = horizon
        self.F_side = F_side
        self.setParameter()
        self.state = zeros(7)   # X(m), Y(m), phi(rad), v_x(m/s), v_y(m/s), r(rad/s), d_f (rad)
        if random:
            np.random.seed(seed)
            weights = np.random.uniform(-errorBound, errorBound, size=16)
            self.vhMdl = (weights[0:4] + 1) * self.vhMdl
            self.trMdl[0] = (weights[4:8] + 1) * self.trMdl[0]
            self.trMdl[1] = (weights[8:12] + 1) * self.trMdl[1]
            self.F_ext = (weights[12:14] + 1) * self.F_ext
            print self.vhMdl[3]
            #self.maxSteeringRate = (weights[14] + 1) * self.maxSteeringRate
            #self.maxSteering = (weights[15] + 1) * self.maxSteering
            #self.steeringRatio = (weights[16] + 1) * self.steeringRatio

    def setStart(self, X0, Y0, phi0, initial_speed=10):
        self.state = zeros(7)
        self.state[0] = X0
        self.state[1] = Y0
        self.state[2] = phi0
        self.state[3] = initial_speed

    def setState(self, state):
    	self.state = state

    def setParameter(self):
        # for vhMdl (based on LincolnMKZ vehicle model)
        a  = 1.20
        b  = 1.65
        m  = 1800.0
        Iz = 3270.0
        # for trMdl (now assuming front/rear tires are same)
        B  = 10.0
        C  = 1.9
        D  = 1.0
        E  = 0.97
        # for F_ext (now assuming no friction/resistance)
        a0 = 0.0
        Crr= 0.0
        # make params into tuple
        self.vhMdl = [a, b, m, Iz]
        self.trMdl = [[B, C, D, E], [B, C, D, E]]
        self.F_ext = [a0, Crr]
        # max steering and dvxdt
        self.maxSteeringRate = 850/180*pi
        self.maxSteering = 525.0/180*pi
        self.steeringRatio = 16         # steering angle / tire angle = 16
        self.maxDvxdt = 5               # warning! tuning needed! (human factor, no need to rand)

    def simulate(self, action):
        """
        updates self.state
        input: action = [% longitudinal acceleration, % steering angle change] (-1 ~ 1) if not fixed speed
                        [% steering angle change] (-1 ~ 1)  if fixed speed
        output: void
        """
        if self.fixed_speed:
            real_action = np.hstack((np.array([0]), action))
        else:
            real_action = action
        self.state = self.simulateWithState(real_action, self.state)

    def simulateWithState(self, action, state):
        """
        given current state and action, calculate next step state
        input: action = [% longitudinal acceleration, % steering angle change] (-1 ~ 1)
               state: valid 7 dof state (pos & vel [X, Y, phi, v_x, v_y, r] + steering [d_f])
        output: nextState
        """
        nextState = zeros(7)
        action[0] = max(min(action[0], 1), -1)
        action[1] = max(min(action[1], 1), -1)

        dvxdt = self.maxDvxdt * action[0]
        steering = action[1]*self.maxSteeringRate*self.dt + state[6]*self.steeringRatio
        nextState[6] = max(min(steering,self.maxSteering),-self.maxSteering)/self.steeringRatio
        u = (nextState[6], dvxdt)
        if self.linear:
            nextState[:6] = f_st(state[:6], u, self.vhMdl, self.trMdl, self.dt, self.F_side)
        else:
            nextState[:6] = f_6s(state[:6], u, self.vhMdl, self.trMdl, self.F_ext, self.dt, self.F_side)
        return nextState






    def getMeasurement(self, track):
        """
        input: track
        output: obs: vehicle states [v_x, v_y, r, d_f] + [ref] (see getRef in tracks.py)
                status: 1 if completed, 0 if normal driving, -1 if deviation large enough

                if there is an obstacle, then
                obs further include [refOb]
                status further include [statusOb], which is 0 if normal, -1 if hit the obstacle
        """
        position = (self.state[0], self.state[1])
        phi = self.state[2]
        v_x = self.state[3]
        ref, status = track.getRef(position, phi, v_x)
        obs = append(self.state[3:], ref)
        if track.obstacleIndex:
            refOb, statusOb = track.getRefObstacle(position, phi, v_x)
            obs = append(obs, refOb)
            status = append(status, statusOb)
        return obs, status

    def getActionSpaceDim(self):
        if self.fixed_speed:
            return 1
        else:
            return 2

    def getObservSpaceDim(self):
        return 4

    def getActionUpperBound(self):
        return ones(2)

    def getActionLowerBound(self):
        return -ones(2)
