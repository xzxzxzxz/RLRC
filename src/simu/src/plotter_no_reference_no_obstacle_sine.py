#!/usr/bin/env python

import rospy
import scipy.io
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use("TkAgg")
import os, rospkg
from std_msgs.msg import Int8

axis_range = 100
axis_range_y = 10
i = 0
obj1 = [0]; obj2 = [0]; obj3 = 0; obj4 = 0; obj5=0
ini_flag = 0; init_flag_ref_traj = 0; init_flag_smooth_traj = 0; init_flag_obstacle = 0; init_flag_ds_cg = 0
X3 = 0; Y3 = 0; X4 = 0; Y4 = 0; X2 = []; Y2 = []; X5 = 0;Y5 = 0
pause_signal = 1

def pausecallback(signal):
    global pause_signal
    if signal.data:
        pause_signal = pause_signal*-1

def vehicle_state_callback(data):
    global ax, i, ini_flag, obj1, obj2, obj3, obj4, obj5
    if (pause_signal + 1):
        if ini_flag == 1:
            while len(ax.lines) > 2:
                ax.lines.pop(2)
        i = i + 1
        if i >= 1:
            ini_flag = 1
        ax.plot(data.X, data.Y, color='red', marker='s', markersize=12)
        ax.plot(X2, Y2, color='green', marker='*', markersize=4)
        ax.plot(X5, Y5, color='orange', marker='.', markersize=2)
        plt.axis('scaled')
        ax.axis([data.X - axis_range/2, data.X + axis_range, data.Y - axis_range_y/2, data.Y + axis_range_y])
        #ax.plot(X3, Y3, color='blue', marker='s', markersize=12)
        #ax.plot(X6, Y6, color='blue', marker='s', markersize=12)
        ax.plot(X4, Y4, color='black', marker='*', markersize=12)
        ax.plot([data.X, X4], [data.Y, Y4], color='black')
        plt.draw()
        plt.pause(0.01)

def ref_traj_callback(data):
    global init_flag_ref_traj, X2, Y2
    X2tem = []; Y2tem = []
    init_flag_ref_traj = 1
    for index in range(len(data.point)):
        X2tem.append(data.point[index].x)
        Y2tem.append(data.point[index].y)
    X2 = X2tem; Y2 = Y2tem

def smooth_traj_callback(data):
    global init_flag_smooth_traj, X5, Y5
    X5tem = []; Y5tem = []
    init_flag_smooth_traj = 1
    for index in range(len(data.point)):
        X5tem.append(data.point[index].x)
        Y5tem.append(data.point[index].y)
    X5 = X5tem; Y5 = Y5tem

def obstacle_state_callback(data):
    global init_flag_obstacle, X3, Y3
    init_flag_obstacle = 1
    X3 = data.x
    Y3 = data.y

def obstacle_state_callback2(data):
    global init_flag_obstacle, X6, Y6
    init_flag_obstacle = 1
    X6 = data.x
    Y6 = data.y

def traj_cg_callback(data):
    global X4, Y4, init_flag_ds_cg
    init_flag_ds_cg = 1
    X4 = data.point[0].x
    Y4 = data.point[0].y

def clearmomery():
    print("clear done")
    plt.clf()
    plt.close('all')

def plotter():
    global ref_x, ref_y, ref_y1, ref_y2, ax

    # initialize node
    rospy.init_node('plotter', anonymous=True)
    rospack = rospkg.RosPack()
    reference = scipy.io.loadmat(os.path.join(rospack.get_path("planning_policy"), "src", "sine_curve.mat"))['sine_curve']
    ref_x = reference[0][:]
    ref_y = reference[1][:]
    ref_y1 = reference[1][:] + 3.5
    fig = plt.figure(figsize=(20, 15))
    ax = fig.add_subplot(1, 1, 1)
    ax.plot(ref_x, ref_y, color='green')
    ax.plot(ref_x, ref_y1, color='green')
    rospy.Subscriber('state_estimate', state_Dynamic, vehicle_state_callback, queue_size=1)
    rospy.Subscriber('final_trajectory', Trajectory2D, ref_traj_callback, queue_size=1)
    rospy.Subscriber('smooth_trajectory', Trajectory2D, smooth_traj_callback, queue_size=1)
    rospy.Subscriber('obstacle1_pos', TrajectoryPoint2D, obstacle_state_callback, queue_size=1)
    rospy.Subscriber('obstacle2_pos', TrajectoryPoint2D, obstacle_state_callback2, queue_size=1)
    rospy.Subscriber('/vehicle/traj_cg', Trajectory2D, traj_cg_callback, queue_size=1)
    rospy.Subscriber('pause_signal', Int8, pausecallback, queue_size=10)
    plt.show()
    rospy.spin()
    rospy.on_shutdown(clearmomery)


if __name__ == '__main__':
    plotter()
