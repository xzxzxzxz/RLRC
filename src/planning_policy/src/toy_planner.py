#!/usr/bin/env python

import rospy
from dbw_mkz_msgs.msg import SteeringReport
from path_follower.msg import state_Dynamic, Trajectory2D, TrajectoryPoint2D
from tracks import Tra
import os, rospkg
vx=0
vy=0
X=0
Y=0
psi=0
wz=0
stateEstimate_mark=False
def stateEstimateCallback(data):
    global vx, vy, X, Y, psi, wz,stateEstimate_mark
    vx = data.vx
    vy = data.vy
    X = data.X
    Y = data.Y
    psi = data.psi
    wz = data.wz
    stateEstimate_mark=True
   
    
def steeringReportCallback(data):
    global d_f
    d_f = data.steering_wheel_angle / 16.0

def main(dt, horizon):
    global vx, vy, X, Y, psi, wz, d_f,stateEstimate_mark
    dt=0.02
    track = Tra('Tra_1', dt, horizon)
    rospy.init_node('toy_planner', anonymous=True)

    rospy.Subscriber('state_estimate', state_Dynamic, stateEstimateCallback)
    rospy.Subscriber('vehicle/steering_report', SteeringReport, steeringReportCallback)
    pub = rospy.Publisher('ref_trajectory', Trajectory2D, queue_size=1)

    rate = rospy.Rate(1/dt)

    # first set the horizon to be very large to get where the vehicle is
    track.horizon = 500
    track.currentIndex = track.horizon

    # set the horizon back to horizon
    track.horizon = horizon*10
    #tmp, _=track.searchClosestPt(586409, 4196656, track.currentIndex)
   # rospy.loginfo("%d",tmp)
    while (rospy.is_shutdown() != 1):
	if stateEstimate_mark == True :   
            #    rospy.loginfo("X_getttttttttt%d  Y_gett%d",X,Y)
		track.currentIndex, _ = track.searchClosestPt(X, Y, track.currentIndex)
    		#rospy.loginfo("curindex%d  X%d  Y%d",track.currentIndex,X,Y)
		track.setPosObstacle(track.currentIndex)
		traj = Trajectory2D()
		for i in range(15):
		    pt = TrajectoryPoint2D()
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
