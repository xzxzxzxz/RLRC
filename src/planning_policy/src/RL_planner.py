#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import numpy as np
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
from std_msgs.msg import Int8
from palnet.network.palnet import Palnet
from palnet.env.driving.base_policy.expert import Expert
from palnet.config.utility import *
import tensorflow as tf
from driving_env.driving import Driving
from cvxopt import matrix, solvers
import os, rospkg
from scipy.interpolate import UnivariateSpline
from palnet.config.utility import network_config
from math import cos, sin, tan, sqrt, pi
from driving_env.driving_utils import plot

vx = 0
vy = 0
X = 0
Y = 0
psi = 0
wz = 0
stateEstimate_mark = False
laneChange = 0
dt = 0.1
env = Driving(story_index=101, dt=dt)

def smooth(traj):
    x = []
    y = []
    t = []
    w = np.ones(len(traj.point)) 
    #w[0] = w[0] * 100
    #w[-1] = w[-1] * 100
    for k in range(len(traj.point)):
        x.append(traj.point[k].x)
        y.append(traj.point[k].y)
        t.append(traj.point[k].t)
    spl_x = UnivariateSpline(t, x, k=3, w=w)
    spl_y = UnivariateSpline(t, y, k=3, w=w)
    spl_x_dot = spl_x.derivative()
    spl_y_dot = spl_y.derivative()
    spl_x_ddot = spl_x.derivative(n=2)
    spl_y_ddot = spl_y.derivative(n=2)
    t_resample = np.linspace(t[0], t[-1], int((t[-1]-t[0])/0.02)+1)
    spl_x_val = spl_x(t_resample)
    spl_y_val = spl_y(t_resample)    
    spl_x_dot_val = spl_x_dot(t_resample)
    spl_y_dot_val = spl_y_dot(t_resample)
    spl_x_ddot_val = spl_x_ddot(t_resample)
    spl_y_ddot_val = spl_y_ddot(t_resample)
    spl_v_val = np.sqrt(spl_x_dot_val**2 + spl_y_dot_val**2)
    spl_theta_val = np.arctan2(spl_y_dot_val, spl_x_dot_val)
    spl_k_val = (spl_x_dot_val * spl_y_ddot_val - spl_y_dot_val * spl_x_ddot_val) / spl_v_val ** 3
    traj_resample = Trajectory2D()
    for k in range(len(t_resample)):
        pt = TrajectoryPoint2D()
        pt.t = t_resample[k]
        pt.x = spl_x_val[k]
        pt.y = spl_y_val[k]
        pt.v = spl_v_val[k]
        pt.theta = spl_theta_val[k]
        pt.kappa = spl_k_val[k]
        traj_resample.point.append(pt)

    return traj_resample

def stateEstimateCallback(data):
    global vx, vy, X, Y, psi, wz, stateEstimate_mark
    vx = data.vx
    vy = data.vy
    X = data.X
    Y = data.Y
    psi = data.psi
    wz = data.wz
    stateEstimate_mark = True

def obstacle1Callback(data):
    global env
    env.obstacles[0].state = np.array([data.x, data.y, data.v, data.theta])

def obstacle2Callback(data):
    global env
    env.obstacles[1].state = np.array([data.x, data.y, data.v, data.theta])

def laneChangeCallback(data):
    global laneChange
    laneChange = data.data

def main(sim_steps):
    global vx, vy, X, Y, psi, wz, stateEstimate_mark, laneChange, dt, env

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
    P = np.array([[100, 0], [0, 1]])
    solvers.options['show_progress'] = False  # don't let cvxopt print iterations

    # define the initial states and timestep
    stateEstimate_mark = False

    # import track file
    rospy.init_node('RL_planner', anonymous=True)
    rospy.Subscriber('state_estimate', state_Dynamic, stateEstimateCallback)
    rospy.Subscriber('lane_signal', Int8, laneChangeCallback)
    ref_traj_pub = rospy.Publisher('final_trajectory_origin', Trajectory2D, queue_size=1)
    # ref_traj_pub2 = rospy.Publisher('final_trajectory_origin2', Trajectory2D, queue_size=1)
    obstacle_pub = rospy.Publisher('obstacle_pos', TrajectoryPoint2D, queue_size=1)
    rospy.Subscriber('obstacle1_pos', TrajectoryPoint2D, obstacle1Callback)
    rospy.Subscriber('obstacle2_pos', TrajectoryPoint2D, obstacle2Callback)

    dt_planner = 0.5
    rate = rospy.Rate(1 / dt_planner)

    # get the sim_env ready
    env.reset()
    env.reset()
    steps = 0

    while (rospy.is_shutdown() != 1):
        if stateEstimate_mark:
            env.ego.state = np.array([X, Y, vx, psi])

            # get the initial observation and obstacle ref
            env.get_all_ref()
            ob = np.append(env.ego.state[2], env.ego_ref["tracks"][env.ego.track_select])
            obstacle_ref_list = env.ego_ref["obstacles"]

            # define traj for later data fulfillment
            traj = Trajectory2D()

            for i in range(sim_steps):
                pt = TrajectoryPoint2D()
                pt.t = i * dt
                pt.x = env.ego.state[0]
                pt.y = env.ego.state[1]
                pt.v = env.ego.state[2]
                pt.theta = env.ego.state[3]
                traj.point.append(pt)

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

                ac = np.zeros(2)
                ac[0] = dudt[0] / 5
                ac[1] = dudt[1] / 0.5
                np.clip(ac, -1, 1, out=ac)
                ob, r, done, obstacle_ref_list = env.step(ac)

            smooth_traj = smooth(traj)
            ref_traj_pub.publish(smooth_traj)
            rate.sleep()

if __name__ == '__main__':
    try: 
        main(80)
    except rospy.ROSInterruptException:
        pass 
