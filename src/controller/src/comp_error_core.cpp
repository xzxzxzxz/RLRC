/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#include "controller/comp_error_core.h"
using namespace std;

float getDistance(const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, float ra_to_cg, float ds)
{
  float x_traj_cg = point.x + cos(point.theta) * ra_to_cg;
  float y_traj_cg = point.y + sin(point.theta) * ra_to_cg;
  float x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  float y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);
  float dist = sqrt(pow(x_traj_cg - x_cg_ds, 2) + pow(y_traj_cg - y_cg_ds, 2));
  return dist;
}

vector<float> ComputeTrackingError(const path_follower::Trajectory2D traj, const path_follower::state_Dynamic state, float ra_to_cg, float ds)
{
  int index = 0;
  for (int i = (int)traj.point.size() - 1; i >= 0; i--)
  {
    if (getDistance(traj.point[index], state, ra_to_cg, ds) > getDistance(traj.point[i], state, ra_to_cg, ds))
      index = i; 
  }

  float beta_s = atan2(state.vy, state.vx) + ds / state.vx * state.wz;
  float x_traj_cg = traj.point[index].x + cos(traj.point[index].theta) * ra_to_cg;
  float y_traj_cg = traj.point[index].y + sin(traj.point[index].theta) * ra_to_cg;

  float x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  float y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);

  float delta_x = - x_cg_ds + x_traj_cg;
  float delta_y = - y_cg_ds + y_traj_cg;
  float delta_yaw = fmod(traj.point[index].theta - beta_s - state.psi, 2 * M_PI);

  if (delta_yaw > M_PI) 
  {
    delta_yaw = delta_yaw - 2 * M_PI;
  }
  float lateral_error = delta_x * sin(state.psi) - delta_y * cos(state.psi);
  vector<float> error_msg_vector;
  error_msg_vector.push_back(traj.point[index].v);
  error_msg_vector.push_back(lateral_error);
  error_msg_vector.push_back(delta_yaw);

 // ROS_INFO_STREAM("dy"<<lateral_error<<"dthe"<<delta_yaw);
  error_msg_vector.push_back(x_traj_cg);
  error_msg_vector.push_back(y_traj_cg); 
  error_msg_vector.push_back(x_cg_ds);
  error_msg_vector.push_back(y_cg_ds);

  return error_msg_vector;
}
