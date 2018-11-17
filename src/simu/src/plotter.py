#!/usr/bin/env python

import rospy
import scipy.io 
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
import matplotlib.pyplot as plt
import os, rospkg
from std_msgs.msg import Int8


axis_range = 10
axis_range_y = 10
i = 0
obj1 = [0]; obj2 = [0]; obj3 = 0; obj4 = 0; obj5=0
ini_flag = 0; ini_flag2 = 0; ini_flag3 = 0
X3 = 0; Y3 = 0; X4 = 0; Y4 = 0; X2 = []; Y2 = []; X5 = 0;Y5 = 0
pause_signal = 1

def pausecallback(signal):
    global pause_signal
    if signal.data:
        pause_signal = pause_signal*-1

def vehicle_state_callback(data):
    global ax, i, ini_flag, obj1, obj2, obj3, obj4, obj5
    if ini_flag2 * ini_flag3 * (pause_signal + 1):
        if ini_flag == 1:
            while len(ax.lines) > 3:
                ax.lines.pop(3)
        i = i + 1
        if i >= 1:
            ini_flag = 1
        obj2 = ax.plot(X2, Y2, color='blue', marker='*', markersize=4)
        obj1 = ax.plot(data.X, data.Y, color='red', marker='s', markersize=8)
        ax.axis([data.X - axis_range, data.X + axis_range, data.Y - axis_range_y, data.Y + axis_range_y])
        obj3 = ax.plot(X3, Y3, color='green', marker='o', markersize=8)
        obj4 = ax.plot(X4, Y4, color='black', marker='*', markersize=8)
        obj5 = ax.plot(X5, Y5, color='blue', marker='o', markersize=8)
        ax.plot([data.X, X4], [data.Y, Y4], color='black')
        ax.plot([X3, X5], [Y3, Y5], color='orange')
        ax.legend((obj1[0], obj2[0], obj3[0], obj4[0], obj5[0]), ('vehicle', 'ref_traj', 'closest_traj_cg', 'vehi_ds', 'closest_traj'), loc='upper left')
        plt.draw()
        plt.pause(0.001)


def ref_traje_callback(data):
    global ini_flag2, X2, Y2
    X2tem = []; Y2tem = []
    ini_flag2 = 1
    for index in range(len(data.point)):
        X2tem.append(data.point[index].x)
        Y2tem.append(data.point[index].y)
    X2 = X2tem; Y2 = Y2tem


def traj_cg_callback(data):
    global X3, Y3, X4, Y4, X5, Y5, ini_flag3
    ini_flag3 = 1
    X3 = data.point[0].x
    Y3 = data.point[0].y
    X4 = data.point[1].x
    Y4 = data.point[1].y
    X5 = data.point[2].x
    Y5 = data.point[2].y

def clearmomery():
    print("clear done")
    plt.clf()
    plt.close('all')


def plotter():
    global ref_x, ref_y, ref_y1, ref_y2, ax

    # initialize node
    rospy.init_node('plotter', anonymous=True)
    rospack = rospkg.RosPack()
    reference = scipy.io.loadmat(os.path.join(rospack.get_path("planning_policy"), "src", "Tra_1.mat"))['Tra_1']
    ref_x = reference[0][:]
    ref_y = reference[1][:]
    ref_y1 = reference[1][:] + 3
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    ax.plot(ref_x, ref_y)
    ax.plot(ref_x, ref_y1)
    rospy.Subscriber('state_estimate', state_Dynamic, vehicle_state_callback, queue_size=1)
    rospy.Subscriber('ref_trajectory', Trajectory2D, ref_traje_callback, queue_size=1)
    rospy.Subscriber('/vehicle/traj_cg', Trajectory2D, traj_cg_callback, queue_size=1)
    rospy.Subscriber('pause_signal', Int8, pausecallback, queue_size=10)
    plt.show()
    rospy.spin()
    rospy.on_shutdown(clearmomery)


if __name__ == '__main__':
    plotter()
