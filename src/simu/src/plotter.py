#!/usr/bin/env python
import rospy
import scipy.io 
from path_follower.msg import state_Dynamic
import matplotlib.pyplot as plt
import os, rospkg
axis_range = 30

def callback(data):
	global axis_range
	plt.plot(data.X, data.Y, color = 'red', marker = '*', markersize = 5)
	plt.axis([data.X - axis_range, data.X + axis_range, data.Y - axis_range, data.Y + axis_range])
	plt.draw()

def plotter():
	global ref_x, ref_y

	# initialize node
	rospy.init_node('plotter', anonymous=True)
        rospack = rospkg.RosPack()
	reference = scipy.io.loadmat(os.path.join(rospack.get_path("planning_policy"), "src", "Tra_1.mat"))['Tra_1']
    	ref_x = reference[0][:]
    	ref_y = reference[1][:]

	plt.plot(ref_x, ref_y)

	rospy.Subscriber('state_estimate', state_Dynamic, callback)

	plt.show()
	rospy.spin()

if __name__ == '__main__':
        plotter()
