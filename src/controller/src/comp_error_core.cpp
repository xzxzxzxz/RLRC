/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#include "controller/comp_error_core.h"
using namespace std;

double getDistance(const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, double ra_to_cg, double ds)
{
  double x_traj_cg = point.x + cos(point.theta) * ra_to_cg;
  double y_traj_cg = point.y + sin(point.theta) * ra_to_cg;
  double x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  double y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);
  double dist = sqrt(pow(x_traj_cg - x_cg_ds, 2) + pow(y_traj_cg - y_cg_ds, 2));
  return dist;
}

vector<double> ComputeTrackingError(const path_follower::Trajectory2D traj, const path_follower::state_Dynamic state, double ra_to_cg, double ds)
{
  int index = 0;
  for (int i = (int)traj.point.size() - 1; i >= 0; i--)
  {
    if (getDistance(traj.point[index], state, ra_to_cg, ds) > getDistance(traj.point[i], state, ra_to_cg, ds))
      index = i; 
  }

  double beta = atan2(state.vy, state.vx);
  double x_traj_cg = traj.point[index].x + cos(traj.point[index].theta) * ra_to_cg;
  double y_traj_cg = traj.point[index].y + sin(traj.point[index].theta) * ra_to_cg;
  double x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  double y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);

  double delta_x = x_traj_cg - x_cg_ds;
  double delta_y = y_traj_cg - y_cg_ds;
  double delta_yaw = fmod(traj.point[index].theta + beta - state.psi, 2 * M_PI);
  if (delta_yaw > M_PI) 
  {
    delta_yaw = delta_yaw - 2 * M_PI;
  }
  double lateral_error = delta_x * sin(state.psi) - delta_y * cos(state.psi);
  double error_msg[3] = {state.vx, lateral_error, delta_yaw};
  vector<double> error_msg_vector (error_msg, error_msg + sizeof(error_msg) / sizeof(double));

  return error_msg_vector;
}