#!/usr/bin/env python  
from path_follower.msg import state_Dynamic
import rospy
import tf
from math import cos, sin

ini_flag = False

def callback(data):
    global ini_flag, X, Y, psi
    X = data.X
    Y = data.Y
    psi = data.psi       
    ini_flag = True 

def plotter():
    global ini_flag, X, Y, psi
    rospy.init_node('trans')
    br = tf.TransformBroadcaster()
    rate = rospy.Rate(10.0)
    rospy.Subscriber('state_estimate', state_Dynamic, callback, queue_size=1)
    while not rospy.is_shutdown():
        while ini_flag:
            br.sendTransform((X-558700.0, Y-4196800.0, 0.0),
                             (0.0, 0.0, sin(psi/2.0), cos(psi/2.0)),
                             rospy.Time.now(),
                             "velodyne",
                             "my_frame")
            rate.sleep()

if __name__ == '__main__':
    plotter()
