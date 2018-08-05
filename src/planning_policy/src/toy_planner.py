#!/usr/bin/env python

import rospy
from dbw_mkz_msgs.msg import SteeringReport
from path_follower import state_Dynamic, Trajectory2D, TrajectoryPoint2D
from tracks import Tra

def stateEstimateCallback(data):
    global vx, vy, X, Y, psi, wz
    vx = data.vx
    vy = data.vy
    X = data.X
    Y = data.Y
    psi = data.psi
    wz = data.wz
    
def steeringReportCallback(data):
    global d_f
    d_f = data.steering_wheel_angle / 16.0

def main(dt, horizon):
    global vx, vy, X, Y, psi, wz, d_f

    track = Tra('Tra_1', dt, horizon)
    rospy.init_node('toy_planner', anonymous=True)

    rospy.Subscriber('state_estimate', state_Dynamic, stateEstimateCallback)
    rospy.Subscriber('vehicle/steering_report', SteeringReport, steeringReportCallback)
    pub = rospy.Publisher('ref_trajectory', Trajectory2D, queue_size=1)

    rate = rospy.Rate(1/dt)
    track.setStartPosYaw

    # first set the horizon to be very large to get where the vehicle is
    track.horizon = 5000
    track.currentIndex, _ = track.searchClosestPt(X, Y, 5000)

    # set the horizon back to horizon
    track.horizon = horizon

    while (rospy.is_shutdown() != 1):
        track.currentIndex, _ = track.searchClosestPt(X, Y, track.currentIndex)
        track.setPosObstacle(track.currentIndex)

        traj = Trajectory2D()
        pt = TrajectoryPoint2D()
        for i in range(15):
            pt.t = i * dt
            pt.x = track.x[track.obstacleIndex]
            pt.y = track.y[track.obstacleIndex]
            pt.theta = track.psi[track.obstacleIndex]
            pt.v = vx
            traj.point.append(pt)
            track.obstacleMove(vx)

        pub.publish(traj)
        rate.sleep()

if __name__ == '__main__':
    main(0.02, 50)