#!/usr/bin/env python


import rospy
import time
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
from geometry_msgs.msg import TwistStamped
from dbw_mkz_msgs.msg import SteeringReport, SteeringCmd
from vehicle_opt import vehicle
from dynamic_reconfigure.server import Server
# from simu.cfg import DynamicParamConfig

action = [0, 0]
dt = 0.02
car = vehicle(dt, False, 0, 500, False, 6, 0.3)
start_flag = False
init_flag = 0


def cmd_vel_stampedCallback(data):
    global action, car
    action[0] = (data.twist.linear.x-car.state[3])/dt/car.maxDvxdt


def steering_cmdCallback(data):
    global action, car
    steering_cmd = data.steering_wheel_angle_cmd*car.steeringRatio
    action[1] = (steering_cmd-car.state[6]*car.steeringRatio)/dt/car.maxSteeringRate


def errorcallback(config):
    global start_flag, init_flag, errorbound
    start_flag = config.Run
    if init_flag == 0 and start_flag == True:
        errorbound = config.errorbound
        car.state[0] = config.X_init
        car.state[1] = config.Y_init
        car.state[2] = config.phi_init
        car.state[3] = config.vx_init
        car.state[6] = config.steering_init / 16
        init_flag = 1


def simu():
    global action
    rospy.init_node('simu', anonymous=True)
    time.sleep(5)
    rate = rospy.Rate(1/dt)
    rospy.loginfo("simulator node starts")
    state=[558640.9252, 4196656.6405, 1.20719921, 5, 0, 0, 0]
    #state = [0, 1, 0, 10, 0, 0, 0]
    car.setState(state)
    rospy.Subscriber('/vehicle/cmd_vel_stamped', TwistStamped, cmd_vel_stampedCallback, queue_size=1)
    rospy.Subscriber('/vehicle/steering_cmd', SteeringCmd, steering_cmdCallback, queue_size=1)
    pub1 = rospy.Publisher('/vehicle/steering_report', SteeringReport, queue_size=1)
    pub2 = rospy.Publisher('state_estimate', state_Dynamic, queue_size=1)
    # srv = Server(DynamicParamConfig, errorcallback)
    steering_report = SteeringReport()
    state_report = state_Dynamic()


    while (rospy.is_shutdown() != 1):
        car.simulate(action)
        steering_report.steering_wheel_angle = car.state[6]*car.steeringRatio
        state_report.vx = car.state[3]
        state_report.vy = car.state[4]
        state_report.X = car.state[0]
        state_report.Y = car.state[1]
        state_report.psi = car.state[2]
        state_report.wz = car.state[5]
        pub1.publish(steering_report)
        pub2.publish(state_report)
        rate.sleep()

if __name__ == '__main__':
    simu()
