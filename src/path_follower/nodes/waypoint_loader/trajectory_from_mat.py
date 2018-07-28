#!/usr/bin/env python
# Software License Agreement (BSD License)
#
# Copyright (c) 2008, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Revision $Id$

## Simple talker demo that published std_msgs/Strings messages
## to the 'chatter' topic

import rospy
import tf
import scipy.io 
import numpy as np
from std_msgs.msg import String, Header
from geometry_msgs.msg import PoseStamped, TwistStamped, Pose2D
from path_follower.msg import waypoint,TrajectoryPoint2D,Trajectory2D

def talker():
    pub = rospy.Publisher('final_trajectory',Trajectory2D, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    waypoints_mat = scipy.io.loadmat('/home/bdd/Desktop/PathFollower_ws/src/path_follower/nodes/waypoint_loader/New_tra_2.mat')['New_tra_2']
    x = waypoints_mat[0][:]
    y = waypoints_mat[1][:]
    theta = waypoints_mat[2][:]
    v = waypoints_mat[3][:]
    t =waypoints_mat[4][:]
    kappa =waypoints_mat[5][:]


    now = rospy.get_rostime() 

    trajectory_record = Trajectory2D()
    trajectory_record.header.stamp = now;
    trajectory_record.point = [ ]

    for i in range(waypoints_mat.shape[1]):
        # define pose
        temp_trajectory = TrajectoryPoint2D()
        temp_trajectory.x = x[i]
        temp_trajectory.y = y[i]
        temp_trajectory.theta = theta[i];
        temp_trajectory.v = v[i]
        temp_trajectory.t = t[i]
        temp_trajectory.kappa = kappa[i];

        trajectory_record.point.append(temp_trajectory)

    while not rospy.is_shutdown():
        trajectory_record.header = Header()
        trajectory_record.header.stamp = rospy.get_rostime() 
        pub.publish(trajectory_record)
        rate.sleep()

if __name__ == '__main__':
    try:
        print "waypoints_from_mat node starts"
        talker()
    except rospy.ROSInterruptException:
        pass
