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
    config['run_type'] = 'validate'
    config['continue'] = True
    # construction configuration:
    # driver problem
    config['env_type'] = 'driver,obstacles'
    config['update_name'] = 'obstacles'
    config['e_update_type'] = 'regular'
    # network config:
    network_config(config, model_path)
    network = Palnet(config)
    network.restore()
    all_attributes = config['a_names']
    # start expert structure.
    g1 = tf.Graph()
    with g1.as_default():
        expert = Expert(model_path)
        expert.restore()
    env = Driving(story_index=101, dt=0.02, track_data='line_curve')
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
    longi_acc_cmd_pub = rospy.Publisher('/vehicle/longi_acc_cmd', Float64, queue_size=1)
    yaw_rate_cmd_pub = rospy.Publisher('/vehicle/yaw_rate_cmd', Float64, queue_size=1)
    obstacle_pub1 = rospy.Publisher('obstacle1_pos', TrajectoryPoint2D, queue_size=1)
    obstacle_pub2 = rospy.Publisher('obstacle2_pos', TrajectoryPoint2D, queue_size=1)

    dt = 0.02
    rate = rospy.Rate(1 / dt)

    # get the sim_env ready
    env.reset()
    steps = 0

    while (rospy.is_shutdown() != 1):
        if stateEstimate_mark:
            steps += 1
            env.ego.state = np.array([X, Y, vx, psi])
            env.ego_state_list.append(env.ego.state.copy())
            for i in range(len(env.obstacles)):
                env.obstacles[i].simulate()
                env.obstacles_state_list[i].append(env.obstacles[i].state.copy())

            obstacle1 = TrajectoryPoint2D()
            obstacle1.t = 0
            obstacle1.x = env.obstacles[0].state[0]
            obstacle1.y = env.obstacles[0].state[1]
            obstacle1.v = env.obstacles[0].state[2]
            obstacle1.theta = env.obstacles[0].state[3]
            obstacle_pub1.publish(obstacle1)

            obstacle2 = TrajectoryPoint2D()
            obstacle2.t = 0
            obstacle2.x = env.obstacles[1].state[0]
            obstacle2.y = env.obstacles[1].state[1]
            obstacle2.v = env.obstacles[1].state[2]
            obstacle2.theta = env.obstacles[1].state[3]
            obstacle_pub2.publish(obstacle2)

            # get the initial observation and obstacle ref
            env.get_all_ref()
            ob = np.append(env.ego.state[2], env.ego_ref["tracks"][env.ego.track_select])
            obstacle_ref_list = env.ego_ref["obstacles"]

            ac0 = expert.choose_action(ob)
            dudt0 = np.multiply(ac0[:, np.newaxis], np.array([[5], [0.5]]))

            # extract parameters from obstacle_ref_list
            data = {}
            for attribute in all_attributes:
                data[attribute] = np.vstack(env.ego_ref[attribute])[:, :-3]
            means = network.predict_means(data)
            # None, 3.
            for attribute in all_attributes:
                if attribute != 'obstacles':
                    means[attribute][:, 0] = abs(means[attribute][:, 0])
                    means[attribute][:, 1] = np.zeros([means[attribute].shape[0], 1])
            means_array = np.vstack([means[attribute] for attribute in all_attributes])
            M = means_array[:, :-1]
            b = means_array[:, -1:]

            try:
                sol = solvers.qp(P=matrix(0.5 * P), q=matrix(- np.matmul(P, dudt0)), G=matrix(M), h=matrix(b))
                dudt = sol['x']
            except:
                try:
                    # if dAger is not useful, transfer back.
                    # print("RL_planner:Something wrong with dAger run.")
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
                except:
                    dudt = dudt0

            ac = np.zeros(2)
            ac[0] = dudt[0] / 5
            ac[1] = dudt[1]
            np.clip(ac, -1, 1, out=ac)

            cmd_vel_stamped = TwistStamped()
            cmd_vel_stamped.twist.linear.x = ac[0] * 5 * dt + vx
            vel_cmd_pub.publish(cmd_vel_stamped)
            longi_acc_cmd_pub.publish(ac[0])
            yaw_rate_cmd_pub.publish(ac[1])
            steering_cmd = SteeringCmd()
            steering_cmd.enable = True
            beta = asin(min(max(ac[1] * 0.5 * 1.65 / (vx+0.0000001), -1), 1))
            delta = atan(tan(beta) * (1.65 + 1.20) / 1.65)
            steering_cmd.steering_wheel_angle_cmd = delta * 14.8
            steering_cmd_pub.publish(steering_cmd)
            if steps == 1000:
                plot(env, 'tl1.png', T1=0, T2=999, dt=33, tl='r')
                render(env, '/home/zhuoxu/RLRC/render_traj', show=False, debugview_bool=False)

            rate.sleep()

if __name__ == '__main__':
    try: 
        main()
    except rospy.ROSInterruptException:
        pass 
