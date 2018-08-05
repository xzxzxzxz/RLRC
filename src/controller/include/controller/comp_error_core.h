/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#ifndef COMP_ERROR
#define COMP_ERROR

#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/TwistStamped.h>
#include <path_follower/Trajectory2D.h>
#include <path_follower/state_Dynamic.h>

#include <path_follower/Vehicle.h>
#include <math.h>
#include <vector>
using namespace std;

double getDistance(const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, double ra_to_cg);

vector<double> ComputeTrackingError(const path_follower::Trajectory2D traj, const path_follower::state_Dynamic state, double ra_to_cg);

#endif
