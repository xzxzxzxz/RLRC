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
  for (int i = 1; i < (int)traj.point.size(); i++)
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
/*
path_follower::Trajectory2D Transient(const path_follwoer::Trajectory2D traj, const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, float ra_to_cg, float ds, float num_points)
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
  float index = 0;
  for (int i = 1; i < (int)traj.point.size(); i++)
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
      index = (abs(d1)>=abs(d2)) ? i : i-1
      break;
    }
  }
  Eigen::MatrixXd x_ref((num_points+1)*2, 1);
  x_ref(0, 0) = 0.;
  x_ref(1, 0) = 0.;
  for (int i=0; i<num_points; i++)
  {
    x_ref((i+1)*2, 0) = traj.point[index+i].x - point.x;
    x_ref((i+1)*2+1, 0) = traj.point[index+i].y - point.y;
  }
  float dt = traj.point[1].t - traj.point[0].t

  float w1 = 1;
  float w2 = 1;
  Eigen::MatrixXd V((num_points-1)*2, (num_points+1)*2);
  Eigen::MatrixXd A((num_points-1)*2, (num_points+1)*2);
  V.setZero();
  A.setZero();
  for (int i=0; i<num_points-1; i++) 
  {
    V.block(i*2, (i+1)*2, 2, 2) = - Eigen::Matrix<float, 2, 2>::Identity() / dt;
    V.block(i*2, (i+2)*2, 2, 2) = Eigen::Matrix<float, 2, 2>::Identity() / dt;
    A.block(i*2, i*2, 2, 2) = Eigen::Matrix<float, 2, 2>::Identity() / pow(dt, 2);
    A.block(i*2, (i+1)*2, 2, 2) = - 2 * Eigen::Matrix<float, 2, 2>::Identity() / pow(dt, 2);
    A.block(i*2, (i+2)*2, 2, 2) = Eigen::Matrix<float, 2, 2>::Identity() / pow(dt, 2);    
  }
  Eigen::MatrixXd H((num_points+1)*2, (num_points+1)*2);
  H = 2 * (Eigen::Matrix<float, (num_points+1)*2, (num_points+1)*2>::Identity() + w1 * V.transpose() * V + w2 * A.transpose() * A)
  g = - 2 * (Eigen::Matrix<float, (num_points+1)*2, (num_points+1)*2>::Identity() + w1 * V.transpose() * V) * x_ref;
  ArrayXd aH = Map<const ArrayXd>(H.data(), H.size());
  ArrayXd ag = Map<const ArrayXd>(g.data(), g.size());
  real_t tH[aH.size()];
  real_t tg[ag.size()];
  Array2realt(aH, tH);
  Array2realt(ag, tg);

  Eigen::Matrix<float, 6, (num_points+1)*2> Ain;
  Ain.block(0, 0, 2, 2) = Eigen::Matrix<float, 2, 2>::Identity();
  Ain.block(2, num_points*2, 2, 2) = Eigen::Matrix<float, 2, 2>::Identity();
  Ain.block(4, 0, 2, 2) = - Eigen::Matrix<float, 2, 2>::Identity() / dt;
  Ain.block(4, 2, 2, 2) = Eigen::Matrix<float, 2, 2>::Identity() / dt;
  ArrayXd aAin = Map<const ArrayXd>(Ain.data(), Ain.size());
  real_t tAin[aAin.size()];
  Array2realt(aAin, tAin);
  real_t lbA[6];
  real_t ubA[6];
  lbA[0] = x_ref(0, 0); lbA[1] = x_ref(1, 0); 
  lbA[2] = x_ref(num_points*2, 0); lbA[3] = x_ref(num_points*2+1, 0); 
  lbA[4] = point.v * cos(point.theta); lbA[5] = point.v * sin(point.theta);
  ubA[0] = x_ref(0, 0); ubA[1] = x_ref(1, 0); 
  ubA[2] = x_ref(num_points*2, 0); ubA[3] = x_ref(num_points*2+1, 0); 
  ubA[4] = point.v * cos(point.theta); ubA[5] = point.v * sin(point.theta);
  real_t lb[(num_points+1)*2] = -100;
  real_t ub[(num_points+1)*2] = 100;

  QProblem example((num_points+1)*2, 6);
  Options options;
  example.setOptions(options);
  int_t nWSR = 100;
  example.init(tH, tg, tAin, lb, ub, lbA, ubA, nWSR);
  real_t xOpt[(num_points+1)*2];
  example.getPrimalSolution(xOpt);

  path_follower::Trajectory2D traj_new;
  traj_new.point[0] = point;
  traj_new.point[0].t = 0;
  for (int i=0; i < (int)traj.point.size() - index; i++)
  {
    if (i >= 0 && i < num_points-1)
    {
      vx = (xOpt[(i+2)*2] - xOpt[(i+1)*2]) / dt;
      vy = (xOpt[(i+2)*2+1] - xOpt[(i+1)*2+1]) / dt;
      ax = (xOpt[i*2] - 2 * xOpt[(i+1)*2] + xOpt[(i+2)*2]) / pow(dt, 2);
      ay = (xOpt[i*2+1] - 2 * xOpt[(i+1)*2+1] + xOpt[(i+2)*2+1]) / pow(dt, 2);
      traj_new.point[i+1].t = (i+1)*dt;
      traj_new.point[i+1].x = xOpt[(i+1)*2];
      traj_new.point[i+1].y = xOpt[(i+1)*2+1];
      traj_new.point[i+1].v = sqrt(pow(vx, 2) + pow(vy, 2));
      traj_new.point[i+1].theta = atan2(vy, vx);
      traj_new.point[i+1].kappa = (vx*ay - vy*ax) / pow(pow(vx, 2) + pow(vy, 2), 1.5);
    }
    else
    {
      traj_new.point[i+1] = traj.point[index+i];
    }
  }
  return traj_new;
}
*/