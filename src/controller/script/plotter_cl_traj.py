#!/usr/bin/env python
import rospy
import matplotlib.pyplot as plt
from std_msgs.msg import Int8
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
import os, rospkg
import scipy.io 

ini_flag = 0;
pause_signal = 1
init_time = 0
time_list = []
traj_x = []
traj_y = []
axis_range = 25
axis_range_y = 50

def pauseCallback(signal):
    global pause_signal
    if signal.data:
        pause_signal = pause_signal*-1

def trajCallback(data):
    global ax, traj_x, traj_y, ini_flag, ref_x, ref_y, ref_y1
    global axis_range, axis_range_y
    traj_x.append(data.point[-1].x)
    traj_y.append(data.point[-1].y)
    if (pause_signal + 1):
        if ini_flag == 0:
            ini_flag = 1
        else:
            ax.clear()
        ax.plot(ref_x, ref_y, 'g')
        ax.plot(ref_x, ref_y1, 'g')
        if len(traj_x) > 0:
            ax.plot(traj_x, traj_y, color='blue', marker='.', markersize=6)
            plt.axis('scaled')
            ax.axis([traj_x[-1] - axis_range/2, traj_x[-1] + axis_range, traj_y[-1] - axis_range_y/2, traj_y[-1] + axis_range_y])
        plt.draw()
        plt.pause(0.01)

def clearmomery():
    print("clear done")
    plt.clf()
    plt.close('all')

def plotter():
    global ax, ref_x, ref_y, ref_y1
    rospack = rospkg.RosPack()
    reference = scipy.io.loadmat(os.path.join(rospack.get_path("planning_policy"), "src", "long_straight.mat"))['long_straight']
    ref_x = reference[0][:]
    ref_y = reference[1][:]
    ref_y1 = reference[1][:] + 9.5
    rospy.init_node('plotter', anonymous=True)
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    rospy.Subscriber('pause_signal', Int8, pauseCallback, queue_size=10)
    rospy.Subscriber('/vehicle/traj_cg', Trajectory2D, trajCallback, queue_size=1)
    plt.show()
    rospy.spin()
    rospy.on_shutdown(clearmomery)

if __name__ == '__main__':
    plotter()
