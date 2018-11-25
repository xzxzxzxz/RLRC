import rosbag
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import savemat
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--nbag', type=str)
args = parser.parse_args()

bag = rosbag.Bag(args.nbag + '.bag')
X = []
Y = []
yaw = []
v = []
yr = []
vel_cmd = []
time_state = []
time_vel_cmd = []
initialize = False

for topic, msg, t in bag.read_messages(topics='/state_estimate'):
    if initialize == False:
       t_initial = t.to_sec()
       initialize = True
    X.append(msg.X)
    Y.append(msg.Y)
    yaw.append(msg.psi)
    v.append(msg.vx)
    time_state.append(t.to_sec()-t_initial)
    yr.append(msg.wz)

for topic, msg, t in bag.read_messages(topics='/vehicle/cmd_vel_stamped'):
    if initialize == False:
       t_initial = t.to_sec()
       initialize = True
    vel_cmd.append(msg.twist.linear.x)
    time_vel_cmd.append(t.to_sec()-t_initial)

X = np.array(X)
Y = np.array(Y)
yaw = np.array(yaw)
v = np.array(v)
time_state = np.array(time_state)
time_vel_cmd = np.array(time_vel_cmd)
yr = np.array(yr)
fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
ax1.plot(time_vel_cmd, vel_cmd, label='vel_cmd')
ax1.plot(time_state, v, label='vel_state')
plt.legend()
plt.show()
bag.close()
