/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#include "controller/comp_error_core.h"
using namespace std;

float getDistance(const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, float ra_to_cg, float ds)
{
  float x_traj_cg = point.x;
  float y_traj_cg = point.y;
  float x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  float y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);
  float dist = sqrt(pow(x_traj_cg - x_cg_ds, 2) + pow(y_traj_cg - y_cg_ds, 2));
  return dist;
}

vector<float> ComputeLateralError(const path_follower::Trajectory2D traj, const path_follower::state_Dynamic state, float ra_to_cg, float ds)
{
  float x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  float y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);
  float beta_s = atan2(state.vy, state.vx) + ds / state.vx * state.wz; 
  float ref_x = x_cg_ds;
  float ref_y = y_cg_ds; 
  float ref_yaw = 0; 
  float ref_kappa = 0; 
  float ref_v = state.vx;
  float wx = 0;
  float wy = 0;
  for (int i = (int)traj.point.size() - 1; i >= 1; i--)
  {
    float wx_i = cos(state.psi + beta_s);
    float wy_i = sin(state.psi + beta_s);
    float p1x = traj.point[i-1].x - x_cg_ds;
    float p1y = traj.point[i-1].y - y_cg_ds;
    float p2x = traj.point[i].x - x_cg_ds;
    float p2y = traj.point[i].y - y_cg_ds;
    float d1 = p1x * wx_i + p1y * wy_i;
    float d2 = p2x * wx_i + p2y * wy_i;
    if (signbit(d1) != signbit(d2) || d1 == 0 || d2 == 0) {
      ref_x = (traj.point[i-1].x * abs(d2) + traj.point[i].x * abs(d1)) / (abs(d1) + abs(d2));
      ref_y = (traj.point[i-1].y * abs(d2) + traj.point[i].y * abs(d1)) / (abs(d1) + abs(d2));
      ref_yaw = (traj.point[i-1].theta * abs(d2) + traj.point[i].theta * abs(d1)) / (abs(d1) + abs(d2));
      ref_kappa = (traj.point[i-1].kappa * abs(d2) + traj.point[i].kappa * abs(d1)) / (abs(d1) + abs(d2));
      ref_v = (traj.point[i-1].v * abs(d2) + traj.point[i].v * abs(d1)) / (abs(d1) + abs(d2));
      wy = wy_i;
      wx = wx_i;
      break;
    }
  }
  float error = wy * (ref_x - x_cg_ds) - wx * (ref_y - y_cg_ds);
  float delta_yaw = fmod(-ref_yaw + beta_s + state.psi, 2 * M_PI);
  if (delta_yaw > M_PI) 
  {
    delta_yaw = delta_yaw - 2 * M_PI;
  }

  vector<float> error_msg_vector;
  error_msg_vector.push_back(error);
  error_msg_vector.push_back(delta_yaw);

 // ROS_INFO_STREAM("dy"<<lateral_error<<"dthe"<<delta_yaw);
  error_msg_vector.push_back(ref_x);
  error_msg_vector.push_back(ref_y);
  error_msg_vector.push_back(ref_v);
  error_msg_vector.push_back(ref_yaw);
  error_msg_vector.push_back(ref_kappa);
  error_msg_vector.push_back(x_cg_ds);
  error_msg_vector.push_back(y_cg_ds);

  return error_msg_vector;
}
