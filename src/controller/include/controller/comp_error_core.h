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
#include <qpOASES.hpp>
USING_NAMESPACE_QPOASES

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/LU>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
using namespace Eigen;

void Array2realt(ArrayXd A, real_t *t);

double getDistance(const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, double ra_to_cg, double ds);

vector<double> ComputeLateralError(const path_follower::Trajectory2D traj, const path_follower::state_Dynamic state, double ra_to_cg, double ds);

path_follower::Trajectory2D Transient(const path_follower::Trajectory2D traj, const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, double ra_to_cg, double ds, int num_points);

#endif
