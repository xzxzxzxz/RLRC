#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import numpy as np
from geometry_msgs.msg import TwistStamped
from dbw_mkz_msgs.msg import SteeringCmd
from path_follower.msg import state_Dynamic
from std_msgs.msg import Int8
from palnet.network.palnet import Palnet
from palnet.env.driving.base_policy.expert import Expert
from palnet.config.utility import *
import tensorflow as tf
from driving_env.driving import Driving
from cvxopt import matrix, solvers
import os, rospkg
from driving_env.driving_utils import plot, render
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
from math import asin, tan, atan
from std_msgs.msg import Float64
from vehicle_opt import vehicle

vx = 0
vy = 0
X = 0
Y = 0
psi = 0
wz = 0
stateEstimate_mark = False
laneChange = 0

def laneChangeCallback(data):
    global laneChange
    laneChange = data.data

def main():
    global vx, vy, X, Y, psi, wz, stateEstimate_mark, laneChange

    # env, base policy, attribute policy and PAL-Net related
    rospack = rospkg.RosPack()
    model_path = os.path.join(rospack.get_path("planning_policy"), "trained_model")
    config = dict()
    config['mode'] = 'Imitation'
    config['run_type'] = 'validate'
    config['continue'] = True
    # construction configuration:
    # driver problem
    config['env_type'] = 'driver'
    config['update_name'] = 'driver'
    config['e_update_type'] = 'regular'
    # network config:
    network_config(config, model_path)
    network = Palnet(config)
    network.restore()
    # start expert structure.
    g1 = tf.Graph()
    with g1.as_default():
        expert = Expert(model_path)
        expert.restore()
    env = Driving(story_index=0, dt=0.02, track_data='sine_curve')
    P = np.array([[100, 0], [0, 1]])
    solvers.options['show_progress'] = False  # don't let cvxopt print iterations

    # define the initial states and timestep
    stateEstimate_mark = False

    # import track file
    rospy.init_node('RL_control', anonymous=True)
    rospy.Subscriber('lane_signal', Int8, laneChangeCallback)
    state_estimate_pub = rospy.Publisher('state_estimate', state_Dynamic, queue_size=1)

    dt = 0.02
    rate = rospy.Rate(1 / dt)

    # get the sim_env ready
    env.reset()

    steps = 0
    state_report = state_Dynamic()

    for i in range(10000):
        steps += 1

        # get the initial observation and obstacle ref
        env.get_all_ref()
        ob = np.append(env.ego.state[2], env.ego_ref["tracks"][env.ego.track_select])

        ac0 = expert.choose_action(ob)
        dudt0 = np.multiply(ac0[:, np.newaxis], np.array([[5], [0.5]]))

        ac = np.zeros(2)
        ac[0] = dudt0[0] / 5
        ac[1] = dudt0[1]
        np.clip(ac, -1, 1, out=ac)
        env.step(action=ac)

        state_report.vx = env.ego.state[2]
        state_report.vy = 0
        state_report.X = env.ego.state[0]
        state_report.Y = env.ego.state[1]
        state_report.psi = env.ego.state[3]
        state_report.wz = 0
        state_estimate_pub.publish(state_report)

        if steps == 1000:
            plot(env, 'tl1.png', T1=0, T2=999, dt=33, tl='r')
            render(env, '/home/zhuoxu/RLRC/render_traj', show=False, debugview_bool=False)

        rate.sleep()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
