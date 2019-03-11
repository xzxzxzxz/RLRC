#!/usr/bin/env python
import rospy
import time
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
from geometry_msgs.msg import TwistStamped
from driving_env.vehicle import Vehicle
import numpy as np
from std_msgs.msg import Float64
from math import sin, cos

action = [0, 0]
dt = 0.02
start_flag = False
init_flag = 0


def longi_acc_cmdCallback(data):
    global action
    print('update longi, action[0] is ', data.data)
    action[0] = data.data


def yaw_rate_cmdCallback(data):
    global action
    print('update lateral, action[1] is ', data.data)
    action[1] = data.data


def simu():
    global action
    rospy.init_node('simu_pt_ms', anonymous=True)
    time.sleep(5)
    rate = rospy.Rate(1/dt)
    rospy.loginfo("simulator node starts")
    state = np.array([20., 0., 10., 0.])
    rospy.Subscriber('/vehicle/longi_acc_cmd', Float64, longi_acc_cmdCallback, queue_size=1)
    rospy.Subscriber('/vehicle/yaw_rate_cmd', Float64, yaw_rate_cmdCallback, queue_size=1)
    pub2 = rospy.Publisher('state_estimate', state_Dynamic, queue_size=1)
    state_report = state_Dynamic()

    while (rospy.is_shutdown() != 1):
        #print('action is ', action)
        dudt = np.multiply(np.array([5, 0.5]), action)
        #print('dudt is ', dudt)
        state[0] = state[0] + state[2] * cos(state[3]) * dt
        state[1] = state[1] + state[2] * sin(state[3]) * dt
        state[2] = state[2] + dudt[0] * dt
        state[3] = state[3] + dudt[1] * dt
        #print('car state is ', state)
        state_report.vx = state[2]
        state_report.vy = 0
        state_report.X = state[0]
        state_report.Y = state[1]
        state_report.psi = state[3]
        state_report.wz = 0
        pub2.publish(state_report)
        rate.sleep()

if __name__ == '__main__':
    simu()
