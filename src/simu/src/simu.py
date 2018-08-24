#!/usr/bin/env python


import rospy
import scipy.io ,time
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
import os, rospkg
from geometry_msgs.msg import TwistStamped
from dbw_mkz_msgs.msg import SteeringReport,SteeringCmd
from vehicle_opt import vehicle
from numpy import sign
action=[0,0]
dt=0.02
car=vehicle(dt,False,0,500,False,34,0)
def cmd_vel_stampedCallback(data):
   global action,car
   action[0]=(data.twist.linear.x-car.state[3])/dt/car.maxDvxdt


def steering_cmdCallback(data):
   global action,car
   steering_cmd = data.steering_wheel_angle_cmd
   action[1] = (steering_cmd-car.state[6]*car.steeringRatio)/dt/car.maxSteeringRate

def simu():
  global action
  rospy.init_node('simu', anonymous=True)
  time.sleep(1.5)
  rate = rospy.Rate(1/dt)
  rospy.loginfo("simulator node starts")

 #  state=[558640.9252,4196656.6405,1.20719921,10,0,0,0]
  state=[0,1,0,10,0,0,0]
  car.setState(state)
  car.setParameter()
  rospy.Subscriber('/vehicle/cmd_vel_stamped', TwistStamped, cmd_vel_stampedCallback,queue_size=1)
  rospy.Subscriber('/vehicle/steering_cmd', SteeringCmd, steering_cmdCallback,queue_size=1)
  pub1 = rospy.Publisher('/vehicle/steering_report', SteeringReport, queue_size=1)
  pub2 = rospy.Publisher('state_estimate', state_Dynamic, queue_size=1)
  steering_report=SteeringReport()
  state_report=state_Dynamic()
  while (rospy.is_shutdown() != 1): 
    car.simulate(action)
    
    steering_report.steering_wheel_angle=car.state[6]*car.steeringRatio 

    '''
    rospy.loginfo("Y%f",car.state[1])
    rospy.loginfo("phi%f",car.state[2])
    rospy.loginfo("v_x%f",car.state[3])
    rospy.loginfo("v_y%f",car.state[4])
    rospy.loginfo("r%f",car.state[5])
    '''
 #   rospy.loginfo("d_f%f",car.state[6])	
    state_report.vx=car.state[3];
    state_report.vy=car.state[4];
    state_report.X=car.state[0];
    state_report.Y=car.state[1];
    state_report.psi=car.state[2];
    state_report.wz=car.state[5];
    pub1.publish(steering_report)
    pub2.publish(state_report)	
    rate.sleep()

if __name__ == '__main__':
        simu()
