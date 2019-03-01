#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import numpy as np
from geometry_msgs.msg import TwistStamped
from path_follower.msg import state_Dynamic
from std_msgs.msg import Int8
from palnet.network.palnet import Palnet
from palnet.env.driving.base_policy.expert import Expert
from palnet.config.utility import *
import tensorflow as tf
from driving_env.driving import Driving
from cvxopt import matrix, solvers
from dbw_mkz_msgs.msg import SteeringCmd 
import os, rospkg
from math import asin, tan, atan

vx = 0
vy = 0
X = 0
Y = 0
psi = 0
wz = 0
stateEstimate_mark = False
laneChange = 0

def stateEstimateCallback(data):
    global vx, vy, X, Y, psi, wz, stateEstimate_mark
    vx = data.vx
    vy = data.vy
    X = data.X
    Y = data.Y
    psi = data.psi
    wz = data.wz
    stateEstimate_mark = True

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
    config['run_type'] = 'train'
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
    env = Driving(story_index=100, track_data='long_straight', lane_deviation=9.5, dt=0.02)
    P = np.array([[100, 0], [0, 1]])
    solvers.options['show_progress'] = False  # don't let cvxopt print iterations

    # define the initial states and timestep
    stateEstimate_mark = False

    # import track file
    rospy.init_node('RL_control', anonymous=True)
    rospy.Subscriber('state_estimate', state_Dynamic, stateEstimateCallback)
    rospy.Subscriber('lane_signal', Int8, laneChangeCallback)
    vel_cmd_pub = rospy.Publisher('/vehicle/cmd_vel_stamped', TwistStamped, queue_size=1)
    steering_cmd_pub = rospy.Publisher('/vehicle/steering_cmd', SteeringCmd, queue_size=1)
    dt = 0.02
    rate = rospy.Rate(1 / dt)

    # get the sim_env ready
    env.reset()

    while (rospy.is_shutdown() != 1):
        if stateEstimate_mark:
            env.ego.state = np.array([X, Y, vx, psi])

            # deal with keyboard lane change command input
            if laneChange != 0:
                env.hand_lanechange(laneChange)
                laneChange = 0

            # a dirty trick, if lane change then disable future lane change
            if env.ego.track_select == 1:
                env.hand_lanechange(0)

            # get the initial observation and obstacle ref
            env.get_all_ref()
            env.ego.track_select = env.ego.closest_track
            ob = np.append(env.ego.state[2], env.ego_track_ref_list[env.ego.track_select])
            obstacle_ref_list = env.ego_obstacle_ref_list

            ac0 = expert.choose_action(ob)
            dudt0 = np.multiply(ac0[:, np.newaxis], np.array([[5], [0.5]]))

            if len(obstacle_ref_list):
                # extract parameters from obstacle_ref_list
                data = {'state0': np.vstack(obstacle_ref_list)[:, :10]}
                feed_data = network.get_feed_dict(data)
                ob_param = network.sess.run(network.means[network.index], feed_data)
                # None, 3.
                M = ob_param[:, :2]
                b = -ob_param[:, -1:]
                if env.ego.track_select == 1:
                    M[0,0] = 0
                    M[0,1] = 0
                    b[0,0] = 1

                try:
                    sol = solvers.qp(P=matrix(0.5 * P), q=matrix(- np.matmul(P, dudt0)), G=matrix(M), h=matrix(b))
                except:
                    # if dAger is not useful, transfer back.
                    print("RL_control:Something wrong with dAger run.")
                    num = len(obstacle_ref_list)
                    for i in range(num):
                        obstacle_ref = obstacle_ref_list[i]
                        A = obstacle_ref[10]
                        B = obstacle_ref[11]
                        C = obstacle_ref[12]
                        M[i, 0] = A
                        M[i, 1] = B
                        b[i, 0] = -C
                    sol = solvers.qp(P=matrix(0.5 * P), q=matrix(- np.matmul(P, dudt0)), G=matrix(M), h=matrix(b))
                dudt = sol['x']
            else:
                dudt = dudt0

            ac = np.zeros(2)            
            ac[0] = dudt[0] / 5
            ac[1] = dudt[1] / 0.5
            np.clip(ac, -1, 1, out=ac)

            cmd_vel_stamped = TwistStamped()
            cmd_vel_stamped.twist.linear.x = ac[0] * 5 * dt + vx
            vel_cmd_pub.publish(cmd_vel_stamped)
            steering_cmd = SteeringCmd()
            steering_cmd.enable = True
            beta = asin(ac[1] * 0.5  * 1.65 / vx)
            delta = atan(tan(beta) * (1.65 + 1.20) / 1.65)
            steering_cmd.steering_wheel_angle_cmd = delta * 14.8
            steering_cmd_pub.publish(steering_cmd)

            rate.sleep()

if __name__ == '__main__':
    try: 
        main()
    except rospy.ROSInterruptException:
        pass 
