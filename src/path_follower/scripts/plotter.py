#!/usr/bin/env python
import rospy
import scipy.io 
from path_follower.msg import ApplanixPose
import matplotlib.pyplot as plt

axis_range = 20

def callback(data):
    global axis_range
    plt.plot(data.smooth_x, data.smooth_y, color = 'red', marker = '*', markersize = 5)
    plt.axis([data.smooth_x - axis_range, data.smooth_x + axis_range, data.smooth_y - axis_range, data.smooth_y + axis_range])
    plt.draw()

def plotter():
    global ref_x, ref_y

    # initialize node
    rospy.init_node('plotter', anonymous=True)

    reference = scipy.io.loadmat(os.path.join(rospack.get_path("path_follower"), "scripts", "waypoint_loader", "Tra_1.mat"))['Tra_1']
    ref_x = reference[0][:]
    ref_y = reference[1][:]

    plt.plot(ref_x, ref_y)

    rospy.Subscriber('Applanix', ApplanixPose, callback)

    plt.show()
    rospy.spin()

if __name__ == '__main__':
    plotter()

