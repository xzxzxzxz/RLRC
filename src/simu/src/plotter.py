#!/usr/bin/env python


import rospy
import scipy.io 
from path_follower.msg import state_Dynamic
import matplotlib.pyplot as plt
import os, rospkg
axis_range = 30
i=0
point_on_screen=20
ini_flag=0
point=[]
def callback(data):
	global axis_range,ax,i,ini_flag,point_on_screen
      
        if ini_flag==1 :
	    ax.lines.pop(1)
	i=i+1
 	if i>point_on_screen :  
	    ini_flag=1  
	ax.plot(data.X, data.Y, color = 'red', marker = '*', markersize = 5)
	ax.axis([data.X - axis_range, data.X + axis_range, data.Y - axis_range, data.Y + axis_range])
        plt.draw()
	
def plotter():
	global ref_x, ref_y,ax,i

	# initialize node
	rospy.init_node('plotter', anonymous=True)
        rospack = rospkg.RosPack()
	reference = scipy.io.loadmat(os.path.join(rospack.get_path("planning_policy"), "src", "Tra_1.mat"))['Tra_1']
    	ref_x = reference[0][:]
   	ref_y = reference[1][:]
	#rate = rospy.Rate(50)
   	fig = plt.figure()
   	ax = fig.add_subplot(1,1,1)
	ax.plot(ref_x, ref_y)
	rospy.Subscriber('state_estimate', state_Dynamic, callback,queue_size=1)
	plt.show()
	rospy.spin()
  
if __name__ == '__main__':
        plotter()
