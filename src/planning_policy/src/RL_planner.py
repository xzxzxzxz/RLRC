#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import twisted
import numpy as np
from config_ppo import Config_PPO
from run_ppo import Run_PPO
from dbw_mkz_msgs.msg import SteeringReport
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
import driving

vx = 0
vy = 0
X = 0
Y = 0
psi = 0
wz = 0
d_f = 0
stateEstimate_mark = False


def stateEstimateCallback(data):
    global vx, vy, X, Y, psi, wz, stateEstimate_mark
    vx = data.vx
    vy = data.vy
    X = data.X
    Y = data.Y
    psi = data.psi
    wz = data.wz
    stateEstimate_mark = True

def steeringReportCallback(data):
    global d_f
    d_f = data.steering_wheel_angle / 16.0

def main(sim_steps):
    global vx, vy, X, Y, psi, wz, d_f, stateEstimate_mark

    # define the initial states and timestep
    vx = 0
    vy = 0
    X = 0
    Y = 0
    psi = 0
    wz = 0
    stateEstimate_mark = False




    # import track file
    rospy.init_node('RL_planner', anonymous=True)
    rospy.Subscriber('state_estimate', state_Dynamic, stateEstimateCallback)
    rospy.Subscriber('vehicle/steering_report', SteeringReport, steeringReportCallback)
    pub = rospy.Publisher('ref_trajectory_origin', Trajectory2D, queue_size=1)

    dt = 0.02
    rate = rospy.Rate(1 / dt)

    # get the expert ready
    config = Config_PPO(log_name='model')
    expert = Run_PPO(config)
    expert.restore()

    # get the sim_env ready
    env = driving.LaneKeeping()
    env.reset()
    env.track.currentIndex = 0

    while (rospy.is_shutdown() != 1):
        if stateEstimate_mark:
            current_state = np.array([X, Y, psi, vx, vy, wz, d_f])
            env.vehicle.setState(current_state)
            ob, _ = env.vehicle.getMeasurement(env.track)
            traj = Trajectory2D()
            for i in range(sim_steps):
                pt = TrajectoryPoint2D()
                pt.t = i * dt
                pt.x = env.vehicle.state[0]
                pt.y = env.vehicle.state[1]
                pt.theta = env.vehicle.state[2]
                pt.v = env.vehicle.state[3]
                traj.point.append(pt)

                ac = expert.obs_to_dyn_act(ob)
                ob, _, _ = env.step(ac, i)
            pub.publish(traj)
            rate.sleep()

if __name__ == '__main__':
    try: 
        main(60)
    except rospy.ROSInterruptException:
        pass 
