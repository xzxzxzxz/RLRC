import rosbag
import matplotlib.pyplot as plt
import numpy as np
from math import floor, cos, sin
from scipy.interpolate import UnivariateSpline

adapt_bag = rosbag.Bag('adaptive_dob.bag')
dob_bag = rosbag.Bag('constant_dob.bag')
pid_bag = rosbag.Bag('pid.bag')

init = False
dy_adapt = []
dtheta_adapt = []
T_adapt = []
for topic, msg, t in adapt_bag.read_messages(topics='/tracking_info'):
    if not init:
        t_init = t.to_sec()
        t_current = 0
        init = True
    else:
        t_current = t.to_sec() - t_init
    dy_adapt.append(msg.dy)
    dtheta_adapt.append(msg.dtheta)
    T_adapt.append(t_current)
rmse_dy_adapt = np.sqrt(np.mean(np.square(np.array(dy_adapt))))
std_dy_adapt = np.sqrt(np.var(np.square(np.array(dy_adapt))))
rmse_dtheta_adapt = np.sqrt(np.mean(np.square(np.array(dtheta_adapt))))
std_dtheta_adapt = np.sqrt(np.var(np.square(np.array(dtheta_adapt))))
print(rmse_dy_adapt, std_dy_adapt, rmse_dtheta_adapt, std_dtheta_adapt)

init = False
dy_dob = []
dtheta_dob = []
T_dob = []
for topic, msg, t in dob_bag.read_messages(topics='/tracking_info'):  
    if not init:
        t_init = t.to_sec()
        t_current = 0
        init = True
    else:
        t_current = t.to_sec() - t_init
    dy_dob.append(msg.dy)
    dtheta_dob.append(msg.dtheta)
    T_dob.append(t_current)
rmse_dy_dob = np.sqrt(np.mean(np.square(np.array(dy_dob))))
std_dy_dob = np.sqrt(np.var(np.square(np.array(dy_dob))))
rmse_dtheta_dob = np.sqrt(np.mean(np.square(np.array(dtheta_dob))))
std_dtheta_dob = np.sqrt(np.var(np.square(np.array(dtheta_dob))))
print(rmse_dy_dob, std_dy_dob, rmse_dtheta_dob, std_dtheta_dob)

init = False
dy_pid = []
dtheta_pid = []
T_pid = []
for topic, msg, t in pid_bag.read_messages(topics='/tracking_info'):
    if not init:
        t_init = t.to_sec()
        t_current = 0
        init = True
    else:
        t_current = t.to_sec() - t_init
    dy_pid.append(msg.dy)
    dtheta_pid.append(msg.dtheta)
    T_pid.append(t_current)
rmse_dy_pid = np.sqrt(np.mean(np.square(np.array(dy_pid))))
std_dy_pid = np.sqrt(np.var(np.square(np.array(dy_pid))))
rmse_dtheta_pid = np.sqrt(np.mean(np.square(np.array(dtheta_pid))))
std_dtheta_pid = np.sqrt(np.var(np.square(np.array(dtheta_pid))))
print(rmse_dy_pid, std_dy_pid, rmse_dtheta_pid, std_dtheta_pid)

fig = plt.figure()
ax1 = fig.add_subplot(2,1,1)
ax1.plot(T_pid[:1100], dy_pid[:1100], label='pid')
ax1.plot(T_dob[:1100], dy_dob[:1100], label='dob')
ax1.plot(T_adapt[:1100], dy_adapt[:1100], label='adapt')
ax1.legend()

ax2 = fig.add_subplot(2,1,2)
ax2.plot(T_pid[:1100], dtheta_pid[:1100], label='pid')
ax2.plot(T_dob[:1100], dtheta_dob[:1100], label='dob')
ax2.plot(T_adapt[:1100], dtheta_adapt[:1100], label='adapt')
ax2.legend()

plt.show()
plt.close(fig)

adapt_bag.close()
dob_bag.close()
pid_bag.close()
