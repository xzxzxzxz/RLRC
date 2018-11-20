import rosbag
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import savemat
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--nbag', type=str)
parser.add_argument('--nmat', type=str)
args = parser.parse_args()

bag = rosbag.Bag(args.nbag + '.bag')
X = []
Y = []
yaw = []
v = []
time = []
yr = []
initialize = False

for topic, msg, t in bag.read_messages(topics='/state_estimate'):
    if initialize == False:
       t_initial = t.to_sec()
       initialize = True
    X.append(msg.X)
    Y.append(msg.Y)
    yaw.append(msg.psi)
    v.append(msg.vx)
    time.append(t.to_sec()-t_initial)
    yr.append(msg.wz)

X = np.array(X)
Y = np.array(Y)
yaw = np.array(yaw)
v = np.array(v)
time = np.array(time)
yr = np.array(yr)
Tra = np.vstack((X,Y,yaw,v,time,yr))
fig = plt.figure()
ax1 = fig.add_subplot(2,2,1)
ax1.plot(Tra[0, :], Tra[1, :])
ax2 = fig.add_subplot(2,2,2)
ax2.plot(Tra[4, :], Tra[2, :])
ax3 = fig.add_subplot(2,2,3)
ax3.plot(Tra[4, :], Tra[3, :])
ax4 = fig.add_subplot(2,2,4)
ax4.plot(Tra[4, :], Tra[5, :])
plt.show()
savemat(args.nmat, {args.nmat:Tra})
bag.close()
