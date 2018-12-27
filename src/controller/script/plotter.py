#!/usr/bin/env python
import rospy
from controller.msg import DobInfo
import matplotlib.pyplot as plt
from std_msgs.msg import Int8

ini_flag = 0;
pause_signal = 1
init_time = 0
d_est_list = []
d_cancel_list = []
time_list = []
draw_length = 50

def pauseCallback(signal):
    global pause_signal
    if signal.data:
        pause_signal = pause_signal*-1

def dobInfoCallback(data):
    global ax, ini_flag, d_est_list, d_cancel_list, draw_length, init_time
    if (pause_signal + 1):
        if ini_flag == 0:
            init_time = rospy.get_time()
            ini_flag = 1
        else:
            ax.clear()
        time = rospy.get_time() - init_time
        time_list.append(time)
        d_est_list.append(data.d_est)
        d_cancel_list.append(data.d_cancel)
        length = len(time_list)
        ax.plot(time_list[-min(length, draw_length):], d_est_list[-min(length, draw_length):], color='red', marker='s', markersize=2)
        ax.plot(time_list[-min(length, draw_length):], d_cancel_list[-min(length, draw_length):], color='blue', marker='s', markersize=2)
        ax.legend('d_est', 'd_cancel')
        plt.draw()
        plt.pause(0.01)

def clearmomery():
    print("clear done")
    plt.clf()
    plt.close('all')

def plotter():
    global ax
    rospy.init_node('plotter', anonymous=True)
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    rospy.Subscriber('dob_info', DobInfo, dobInfoCallback, queue_size=1)
    rospy.Subscriber('pause_signal', Int8, pauseCallback, queue_size=10)
    plt.show()
    rospy.spin()
    rospy.on_shutdown(clearmomery)

if __name__ == '__main__':
    plotter()
