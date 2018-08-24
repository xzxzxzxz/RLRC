#!/usr/bin/env python

import rospy
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D

def ref_trajectoryCallback(data):
    global traj,ref_tra_mark
    traj=data
    ref_tra_mark = True

def main(dt):
    # define the traj and ref_tra_make variables
    traj = Trajectory2D()
    ref_tra_mark = False
    dt=0.02

    global traj,ref_tra_mark

    rospy.init_node('ZOH', anonymous=True)
    rospy.Subscriber('ref_trajectory_origin', Trajectory2D,ref_trajectoryCallback)
    pub = rospy.Publisher('ref_trajectory', Trajectory2D, queue_size=1)

    rate = rospy.Rate(1/dt)

    while (rospy.is_shutdown() != 1):
        if ref_tra_mark:
            pub.publish(traj)
            ref_tra_mark = False
        rate.sleep()

if __name__ == '__main__':
    main(0.02)
