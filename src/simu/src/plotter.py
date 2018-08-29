#!/usr/bin/env python

import rospy
import scipy.io 
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
import matplotlib.pyplot as plt
import os, rospkg
axis_range = 30
axis_range_y = 6
i = 0
obj1 = [0]; obj2 = [0]; obj3 = 0; obj4 = 0
ini_flag = 0; ini_flag2 = 0; ini_flag3 = 0
X3 = 0; Y3 = 0; X4 = 0; Y4 = 0; X2 = []; Y2 = []


def vehicle_state_callback(data):
    global ax, i, ini_flag, obj1, obj2, obj3, obj4
    if ini_flag2 * ini_flag3:
        if ini_flag == 1:
            while len(ax.lines) > 1:
                ax.lines.pop(1)
        i = i + 1
        if i >= 1:
            ini_flag = 1
        obj1 = ax.plot(data.X, data.Y, color='red', marker='s', markersize=8)
        ax.axis([data.X - axis_range, data.X + axis_range, -axis_range_y, axis_range_y])
        obj3 = ax.plot(X3, Y3, color='green', marker='o', markersize=8)
        obj4 = ax.plot(X4, Y4, color='black', marker='*', markersize=8)
        obj2 = ax.plot(X2, Y2, color='blue', marker='*', markersize=4)
        ax.legend((obj1[0], obj2[0], obj3[0], obj4[0]), ('vehicle', 'ref_traje','closest_traj_cg','vehi_ds'), loc='upper left')
        plt.draw()
       # plt.pause(0.001)


def ref_traje_callback(data):
    global ini_flag2, X2, Y2
    X2tem = []; Y2tem = []
    ini_flag2 = 1
    for index in range(len(data.point)):
        X2tem.append(data.point[index].x)
        Y2tem.append(data.point[index].y)
    X2 = X2tem; Y2 = Y2tem


def traj_cg_callback(data):
    global X3, Y3, X4, Y4, ini_flag3
    ini_flag3 = 1
    X3 = data.point[0].x
    Y3 = data.point[0].y
    X4 = data.point[1].x
    Y4 = data.point[1].y


def clearmomery():
    print("clear done")
    plt.clf()
    plt.close('all')


def plotter():
    global ref_x, ref_y, ax

    # initialize node
    rospy.init_node('plotter', anonymous=True)
    rospack = rospkg.RosPack()
    reference = scipy.io.loadmat(os.path.join(rospack.get_path("planning_policy"), "src", "sine_curve.mat"))['Tra_curve2']
    ref_x = reference[0][:]
    ref_y = reference[1][:]
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    ax.plot(ref_x, ref_y)
    rospy.Subscriber('state_estimate', state_Dynamic, vehicle_state_callback, queue_size=1)
    rospy.Subscriber('ref_trajectory', Trajectory2D, ref_traje_callback, queue_size=1)
    rospy.Subscriber('/vehicle/traj_cg', Trajectory2D, traj_cg_callback, queue_size=1)
    plt.show()
    rospy.spin()
    rospy.on_shutdown(clearmomery)


if __name__ == '__main__':
    plotter()
