/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#ifndef COMP_ERROR
#define COMP_ERROR

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <path_follower/Trajectory2D.h>
#include <path_follower/state_Dynamic.h>
#include <controller/TrackingInfo.h>

#include <path_follower/Vehicle.h>
#include <math.h>
#include <vector>
using namespace std;

float getDistance(const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, float ra_to_cg, float ds);

vector<float> ComputeLateralError(const path_follower::Trajectory2D traj, const path_follower::state_Dynamic state, float ra_to_cg, float ds);

#endif
