#!/usr/bin/env python
import rospy
import scipy.io
import os, rospkg
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D, vehicleinfo, vehicleinfomation
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from math import cos, sin

ini_flag = False
ini_flag2 = False
ini_flag3 = False
X2 = [0.0]
Y2 = [0.0]
X3 = [0.0]
Y3 = [0.0]
lx = [0.0]
ly = [0.0]
angle = [0]
number = 0

def callback(data):
    global ini_flag, X, Y, psi
    X = data.X
    Y = data.Y
    psi = data.psi       
    ini_flag = True 

def ref_traj_callback(data) :
    global ini_flag2, X2, Y2
    X2tem = []
    Y2tem = []
    ini_flag2 = True
    for index in range(200):
        X2tem.append(data.point[index].x)
        Y2tem.append(data.point[index].y)
    X2 = X2tem
    Y2 = Y2tem

def vcallback(data) :
    global ini_flag3, X3, Y3, lx, ly, angle, number
    X3tem = []
    Y3tem = []
    lxtem = []
    lytem = []
    angletem = []
    ini_flag3 = True
    number = len(data.point)
    for inde in range(number):
        X3tem.append(data.point[inde].X)
        Y3tem.append(data.point[inde].Y)
        lxtem.append(data.point[inde].lx)
        lytem.append(data.point[inde].ly)
        angletem.append(data.point[inde].psi)
    X3 = X3tem
    Y3 = Y3tem
    lx = lxtem
    ly = lytem
    angle = angletem

def plotter():
    global ini_flag, ini_flag2, ini_flag3, X, Y, psi, X2, Y2, X3, Y3, lx, ly, angle, number, veh
    # initialize node
    rospy.init_node('plotter', anonymous=True)
    rospack = rospkg.RosPack()
    reference = scipy.io.loadmat(os.path.join(rospack.get_path("path_follower"), "scripts", "waypoint_loader", "Tra_demo.mat"))['Tra_demo']
    ref_x = reference[0][:]
    ref_y = reference[1][:]
    rospy.Subscriber('state_estimate', state_Dynamic, callback, queue_size=1)
    rospy.Subscriber('vehicle_state', vehicleinfo, vcallback, queue_size=1)
    rospy.Subscriber('final_trajectory', Trajectory2D, ref_traj_callback, queue_size=1)
    v_pub = rospy.Publisher("vehicle", Marker, queue_size=1)
    l_pub = rospy.Publisher("line", Marker, queue_size=1)
    p_pub = rospy.Publisher("path", Marker, queue_size=1)
    pub = rospy.Publisher("veh", MarkerArray, queue_size=1)
    rate = rospy.Rate(20)

    while (rospy.is_shutdown() != 1):
        vmarker = Marker()
        lmarker = Marker()
        point_marker = Marker()
        pmarker = Marker()
        pmarker.header.frame_id = "/my_frame"
        pmarker.header.stamp = rospy.get_rostime()
        pmarker.type = pmarker.LINE_STRIP
        pmarker.ns = "mkzvehicle"
        pmarker.id = 0
        pmarker.scale.x = 0.5
        pmarker.color.b = 1.0
        pmarker.color.a = 1.0
        pmarker.action = pmarker.ADD

        leng = len(ref_x)
        for i in range(0, leng, 50):
            p = Point()
            p.x = ref_x[i]-558700.0
            p.y = ref_y[i]-4196800.0
            p.z = 0

            pmarker.points.append(p)
        p_pub.publish(pmarker)


        vmarker.header.stamp = rospy.get_rostime()
        lmarker.header.stamp = rospy.get_rostime()
        vmarker.header.frame_id = "/my_frame"
        lmarker.header.frame_id = "/my_frame"
        lmarker.ns = "mkzvehicle"
        vmarker.ns = "mkzvehicle"
        lmarker.id = 1
        vmarker.id = 2

        vmarker.scale.x = 2.85
        vmarker.scale.y = 1.6
        vmarker.scale.z = 1.5
        lmarker.scale.x = 0.6

        lmarker.color.g = 1.0
        lmarker.color.a = 1.0
        vmarker.color.r = 1.0
        vmarker.color.a = 1.0

        lmarker.type = lmarker.LINE_STRIP
        vmarker.type = vmarker.CUBE

        lmarker.action = lmarker.ADD
        vmarker.action = vmarker.ADD

        if ini_flag == True:
            vmarker.pose.position.x = X-558700.0
            vmarker.pose.position.y = Y-4196800.0
            vmarker.pose.position.z = 0.75
            vmarker.pose.orientation.x = 0.0
            vmarker.pose.orientation.y = 0.0
            vmarker.pose.orientation.z = sin(psi/2.0)
            vmarker.pose.orientation.w = cos(psi/2.0)
            v_pub.publish(vmarker)

        if ini_flag2 == True:
            length = len(X2)
            for i in range(0, length, 50):
                p = Point()
                p.x = X2[i]-558700.0
                p.y = Y2[i]-4196800.0
                p.z = 0.3

                lmarker.points.append(p)
            l_pub.publish(lmarker)

        if ini_flag3 == True:
            vehi = MarkerArray()
            for i in range(number):
                veh = Marker()
                veh.header.frame_id = "/my_frame"
                veh.header.stamp = rospy.get_rostime()
                veh.type = veh.CUBE
                veh.ns = "mkzvehicle"
                veh.scale.z = 1.5
                veh.color.b = 1.0
                veh.color.a = 1.0
                veh.pose.position.z = 0.75
                veh.pose.orientation.x = 0.0
                veh.pose.orientation.y = 0.0
                veh.action = veh.ADD
                veh.id = 4+2*i
                veh.scale.x = lx[i]
                veh.scale.y = ly[i]
                
                veh.pose.position.x = X3[i]
                veh.pose.position.y = Y3[i]
                
                veh.pose.orientation.z = sin(angle[i]/2.0)
                veh.pose.orientation.w = cos(angle[i]/2.0)
                vehi.markers.append(veh)
            
            pub.publish(vehi)

        rate.sleep()
    rospy.spin()

if __name__ == '__main__':
    plotter()
