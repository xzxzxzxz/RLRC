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
yr_adapt = []
T_adapt_state = []
for topic, msg, t in adapt_bag.read_messages(topics={'/tracking_info', '/state_estimate'}):
    if not init:
        t_init = t.to_sec()
        t_current = 0
        init = True
    else:
        t_current = t.to_sec() - t_init
    if topic == '/tracking_info':
        dy_adapt.append(msg.dy)
        dtheta_adapt.append(msg.dtheta)
        T_adapt.append(t_current)
    else:
        yr_adapt.append(msg.wz)
        T_adapt_state.append(t_current)
rmse_dy_adapt = np.sqrt(np.mean(np.square(np.array(dy_adapt))))
std_dy_adapt = np.sqrt(np.var(np.square(np.array(dy_adapt))))
rmse_dtheta_adapt = np.sqrt(np.mean(np.square(np.array(dtheta_adapt))))
std_dtheta_adapt = np.sqrt(np.var(np.square(np.array(dtheta_adapt))))
print(rmse_dy_adapt, std_dy_adapt, rmse_dtheta_adapt, std_dtheta_adapt)

init = False
dy_dob = []
dtheta_dob = []
T_dob = []
yr_dob = []
T_dob_state = []
for topic, msg, t in dob_bag.read_messages(topics={'/tracking_info', '/state_estimate'}):  
    if not init:
        t_init = t.to_sec()
        t_current = 0
        init = True
    else:
        t_current = t.to_sec() - t_init
    if topic == '/tracking_info':
        dy_dob.append(msg.dy)
        dtheta_dob.append(msg.dtheta)
        T_dob.append(t_current)
    else:
        yr_dob.append(msg.wz)
        T_dob_state.append(t_current)
rmse_dy_dob = np.sqrt(np.mean(np.square(np.array(dy_dob))))
std_dy_dob = np.sqrt(np.var(np.square(np.array(dy_dob))))
rmse_dtheta_dob = np.sqrt(np.mean(np.square(np.array(dtheta_dob))))
std_dtheta_dob = np.sqrt(np.var(np.square(np.array(dtheta_dob))))
print(rmse_dy_dob, std_dy_dob, rmse_dtheta_dob, std_dtheta_dob)

init = False
dy_pid = []
dtheta_pid = []
T_pid = []
yr_pid = []
T_pid_state = []
for topic, msg, t in pid_bag.read_messages(topics={'/tracking_info', '/state_estimate'}):
    if not init:
        t_init = t.to_sec()
        t_current = 0
        init = True
    else:
        t_current = t.to_sec() - t_init
    if topic == '/tracking_info':
        dy_pid.append(msg.dy)
        dtheta_pid.append(msg.dtheta)
        T_pid.append(t_current)
    else:
        yr_pid.append(msg.wz)
        T_pid_state.append(t_current)
rmse_dy_pid = np.sqrt(np.mean(np.square(np.array(dy_pid))))
std_dy_pid = np.sqrt(np.var(np.square(np.array(dy_pid))))
rmse_dtheta_pid = np.sqrt(np.mean(np.square(np.array(dtheta_pid))))
std_dtheta_pid = np.sqrt(np.var(np.square(np.array(dtheta_pid))))
print(rmse_dy_pid, std_dy_pid, rmse_dtheta_pid, std_dtheta_pid)

n = -1
fig = plt.figure()
ax1 = fig.add_subplot(2,2,1)
ax1.plot(T_pid[:n], dy_pid[:n], label='pid')
ax1.plot(T_dob[:n], dy_dob[:n], label='dob')
ax1.plot(T_adapt[:n], dy_adapt[:n], label='adapt')
ax1.legend()
ax1.set_title('dy')

ax2 = fig.add_subplot(2,2,2)
ax2.plot(T_pid[:n], dtheta_pid[:n], label='pid')
ax2.plot(T_dob[:n], dtheta_dob[:n], label='dob')
ax2.plot(T_adapt[:n], dtheta_adapt[:n], label='adapt')
ax2.legend()
ax2.set_title('dtheta')

ax2 = fig.add_subplot(2,2,3)
ax2.plot(T_pid_state[:n], yr_pid[:n], label='pid')
ax2.plot(T_dob_state[:n], yr_dob[:n], label='dob')
ax2.plot(T_adapt_state[:n], yr_adapt[:n], label='adapt')
ax2.legend()
ax2.set_title('yr')

plt.show()
plt.close(fig)

adapt_bag.close()
dob_bag.close()
pid_bag.close()
