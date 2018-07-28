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
from geometry_msgs.msg import PoseStamped, TwistStamped
from path_follower_to_controller.msg import dtlane,lane,waypoint

def talker():
    pub = rospy.Publisher('final_waypoints',lane, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    waypoints_mat = scipy.io.loadmat('/home/chen/control_ws/src/path_follower/nodes/waypoint_loader/waypoints.mat')['data']
    x = waypoints_mat[0][:]
    y = waypoints_mat[1][:]
    yaw = waypoints_mat[3][:]
    v = waypoints_mat[2][:]
    now = rospy.get_rostime() 

    # define lane
    lane_record = lane()
    lane_record.increment = 0
    lane_record.waypoints = [ ]

    for i in range(waypoints_mat.shape[1]):
        # define pose
        temp_pose = PoseStamped()
        temp_pose.header.stamp = now;
        temp_pose.pose.position.x = x[i]
        temp_pose.pose.position.y = y[i]
        temp_pose.pose.position.z = 0
        quaternion = tf.transformations.quaternion_from_euler(yaw[i],0,0,'rzyx')
        temp_pose.pose.orientation.x = quaternion[0]
        temp_pose.pose.orientation.y = quaternion[1]
        temp_pose.pose.orientation.z = quaternion[2]
        temp_pose.pose.orientation.w = quaternion[3]
        # define twist
        temp_twist = TwistStamped()
        temp_twist.header.stamp = now;
        temp_twist.twist.linear.x = v[i]
        temp_twist.twist.linear.y = 0
        temp_twist.twist.linear.z = 0
        temp_twist.twist.angular.x = 0
        temp_twist.twist.angular.y = 0
        temp_twist.twist.angular.z = 0
        # define dtlane (default not used)
        temp_dtlane = dtlane()
        # define waypoint
        temp_waypoint = waypoint()
        temp_waypoint.pose = temp_pose
        temp_waypoint.twist = temp_twist
        temp_waypoint.dtlane = temp_dtlane
        temp_waypoint.change_flag = 0
        # add to the list
        lane_record.waypoints.append(temp_waypoint)

    while not rospy.is_shutdown():
        lane_record.header = Header()
        lane_record.header.stamp = rospy.get_rostime() 
        pub.publish(lane_record)
        rate.sleep()

if __name__ == '__main__':
    try:
        print "waypoints_from_mat node starts"
        talker()
    except rospy.ROSInterruptException:
        pass
