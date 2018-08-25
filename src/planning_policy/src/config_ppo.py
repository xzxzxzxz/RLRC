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
                 track='sine_curve'
                 ):

        self.log_name = log_name
        self.model_path = './' + log_name + '/'

        self.s_dim = s_dim
        self.a_dim = a_dim

        self.vehicle_random = vehicle_random
        self.vehicle_seed = vehicle_seed
        self.vehicle_err = vehicle_err
        self.track = track
