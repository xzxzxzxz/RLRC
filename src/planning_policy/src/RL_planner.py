#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import numpy as np
from dbw_mkz_msgs.msg import SteeringReport
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
from std_msgs.msg import Int8
from palnet.network.palnet import Palnet
from palnet.env.driving.base_policy.expert import Expert
from palnet.config.utility import *
import tensorflow as tf
from driving_env.driving import Driving

vx = 0
vy = 0
X = 0
Y = 0
psi = 0
wz = 0
d_f = 0
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

def steeringReportCallback(data):
    global d_f
    d_f = data.steering_wheel_angle / 16.0

def laneChangeCallback(data):
    global laneChange
    laneChange = data.data

def main(sim_steps):
    global vx, vy, X, Y, psi, wz, d_f, stateEstimate_mark, laneChange

    model_path = "/home/zhuoxu/trained_model"
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
    env = Driving(story_index=0, track_data='Tra_1', lane_deviation=6)

    # define the initial states and timestep
    vx = 0
    vy = 0
    X = 0
    Y = 0
    psi = 0
    wz = 0
    stateEstimate_mark = False

    # import track file
    rospy.init_node('RL_planner', anonymous=True)
    rospy.Subscriber('state_estimate', state_Dynamic, stateEstimateCallback)
    rospy.Subscriber('vehicle/steering_report', SteeringReport, steeringReportCallback)
    rospy.Subscriber('lane_signal', Int8, laneChangeCallback)
    pub = rospy.Publisher('ref_trajectory_origin', Trajectory2D, queue_size=1)

    dt = 0.02
    rate = rospy.Rate(1 / dt)

    # get the sim_env ready
    env.reset()
    steps = 0

    while (rospy.is_shutdown() != 1):
        if stateEstimate_mark:
            env.ego.state = np.array([X, Y, vx, psi])
            if laneChange != 0:
                env.hand_lanechange(laneChange)
                laneChange = 0
            env.get_all_ref()
            ob = np.append(env.ego.state[2], env.ego_track_ref_list[env.ego.track_select])

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
                dudt = dudt0
                ac = np.zeros(2)
                ac[0] = dudt[0] / 5
                ac[1] = dudt[1]
                np.clip(ac, -1, 1, out=ac)
                ob, r, done, obstacle_ref_list = env.step(ac)

                # speed limit
                # if ob[0] > 5:
                #     ac[0]=0
            pub.publish(traj)
            steps += 1
            rate.sleep()

if __name__ == '__main__':
    try: 
        main(180)
    except rospy.ROSInterruptException:
        pass 
