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

//#include "qpOASES/qpOASES.hpp"
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/LU>
#include <math.h>
#include <vector>
using namespace std;

/*
void Array2realt(Eigen::ArrayXd A, real_t *t) {
    int k = A.size();
    for(int i=0; i < k; i++)
        t[i] = A[i];
}
*/

float getDistance(const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, float ra_to_cg, float ds);

vector<float> ComputeLateralError(const path_follower::Trajectory2D traj, const path_follower::state_Dynamic state, float ra_to_cg, float ds);

//path_follower::Trajectory2D Transient(const path_follwoer::Trajectory2D traj, const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, float ra_to_cg, float ds, float num_points)

#endif
