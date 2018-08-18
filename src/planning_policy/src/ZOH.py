#!/usr/bin/env python

import rospy
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
traj = Trajectory2D()
ref_tra_mark = False
def ref_trajectoryCallback(data):
    global traj,ref_tra_mark
    traj=data
    ref_tra_mark = True

def main(dt):
    global traj,ref_tra_mark
    dt=0.02
    rospy.init_node('ZOH', anonymous=True)
    rospy.Subscriber('ref_trajectory_origin', Trajectory2D,ref_trajectoryCallback)
    pub = rospy.Publisher('ref_trajectory', Trajectory2D, queue_size=1)
    rate = rospy.Rate(1/dt)
    while (rospy.is_shutdown() != 1):
	if ref_tra_mark == True :   
		pub.publish(traj)
	rate.sleep()

if __name__ == '__main__':
    main(0.02)
