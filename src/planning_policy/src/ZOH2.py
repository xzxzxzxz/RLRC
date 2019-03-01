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

    rospy.init_node('ZOH2', anonymous=True)
    rospy.Subscriber('final_trajectory_origin2', Trajectory2D, ref_trajectoryCallback, queue_size=1)
    pub = rospy.Publisher('final_trajectory2', Trajectory2D, queue_size=1)
    rate = rospy.Rate(1/dt)

    while (rospy.is_shutdown() != 1):
        if ref_tra_mark:
            pub.publish(traj)
        rate.sleep()

if __name__ == '__main__':
    main(0.02)
