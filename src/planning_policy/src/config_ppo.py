#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
The config class containing all the parameters needed
zhuoxu@berkeley.edu
"""
import os


class Config_PPO:

    def __init__(self,
                 log_name,
                 s_dim=9,
                 a_dim=2,
                 vehicle_random=False,
                 vehicle_seed=0,
                 vehicle_err=0.1,
                 track='sine_curve',
                 n_iter=100,
                 max_path_length=1000,
                 min_timesteps_per_batch=10000,
                 gamma=0.99,
                 a_lr=1e-4,
                 c_lr=1e-4,
                 a_update_steps=100,
                 c_update_steps=100,
                 epsilon=0.2,
                 save_iter=50
                 ):

        self.log_name = log_name
        self.model_path = './' + log_name + '/'

        self.s_dim = s_dim
        self.a_dim = a_dim

        self.vehicle_random = vehicle_random
        self.vehicle_seed = vehicle_seed
        self.vehicle_err = vehicle_err
        self.track = track

        self.n_iter = n_iter
        self.max_path_length = max_path_length
        self.min_timesteps_per_batch = min_timesteps_per_batch
        self.gamma = gamma
        self.a_lr = a_lr
        self.c_lr = c_lr
        self.a_update_steps = a_update_steps
        self.c_update_steps = c_update_steps
        self.epsilon = epsilon
        self.save_iter = save_iter
