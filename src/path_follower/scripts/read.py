#!/usr/bin/env python
import rospy
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from math import cos, sin

info = []
number1 = []
number2 = []
number3 = []
number4 = []
def plotter():

	rospy.init_node('map', anonymous=True)
	pub = rospy.Publisher("map", MarkerArray, queue_size=1)
	rate = rospy.Rate(20)

	for line in open("PATH1019_GE.txt"):  
	    
	    info.append(line)

	for i in range(1, 455):
	    number1.append(int(info[i][:3]))
	    number2.append(int(info[i][4:7]))
	    number3.append(float(info[i][52:63]))
	    number4.append(float(info[i][64:]))

	while (rospy.is_shutdown() != 1):
		vehi = MarkerArray()
		j = 0
		number = 50
		for i in range(number):
			veh = Marker()
			veh.header.frame_id = "/my_frame"
			veh.header.stamp = rospy.get_rostime()
			veh.type = veh.LINE_STRIP
			veh.ns = "mkzvehicle"
			veh.scale.x = 0.15
			veh.color.b = 1.0
			veh.color.r = 1.0
			veh.color.g = 1.0
			veh.color.a = 1.0
			veh.action = veh.ADD
			veh.id = 4+2*i

			if number1[j] == 210:
				veh.color.b = 0.0

			if number1[j] == 300:
				veh.color.b = 0.0
				veh.color.g = 0.0

			if number1[j] == 400:
				veh.color.a = 0.3

			while True:
				p = Point()
				p.x = cos(-0.012)*(number3[j]+6536.5)+sin(-0.012)*(number4[j]-4973)
				p.y = cos(-0.012)*(number4[j]-4973)-sin(-0.012)*(number3[j]+6536.5)
				p.z = 0
				j = j + 1
				veh.points.append(p)
				if (number2[j] == 0):
					break
			vehi.markers.append(veh)
           
		pub.publish(vehi)


if __name__ == '__main__':
    plotter()
