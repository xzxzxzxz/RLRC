/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#include "controller/comp_error_core.h"
using namespace std;
using namespace Eigen;

#pragma GCC push_options
#pragma GCC optimize("O2")

void Array2realt(ArrayXd A, real_t *t) {
    int k = A.size();
    for(int i=0; i < k; i++)
        t[i] = A[i];
}

double getDistance(const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, double ra_to_cg, double ds)
{
  double x_traj_cg = point.x;
  double y_traj_cg = point.y;
  double x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  double y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);
  double dist = sqrt(pow(x_traj_cg - x_cg_ds, 2) + pow(y_traj_cg - y_cg_ds, 2));
  return dist;
}

vector<double> ComputeLateralError(const path_follower::Trajectory2D traj, const path_follower::state_Dynamic state, double ra_to_cg, double ds)
{
  double x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  double y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);
  double beta_s = atan2(state.vy, state.vx) + ds / state.vx * state.wz; 
  double ref_x = x_cg_ds;
  double ref_y = y_cg_ds; 
  double ref_yaw = 0; 
  double ref_kappa = 0; 
  double ref_v = state.vx;
  double wx = 0;
  double wy = 0;
  for (int i = 1; i < (int)traj.point.size(); i++)
  {
    double wx_i = cos(state.psi + beta_s);
    double wy_i = sin(state.psi + beta_s);
    double p1x = traj.point[i-1].x - x_cg_ds;
    double p1y = traj.point[i-1].y - y_cg_ds;
    double p2x = traj.point[i].x - x_cg_ds;
    double p2y = traj.point[i].y - y_cg_ds;
    double d1 = p1x * wx_i + p1y * wy_i;
    double d2 = p2x * wx_i + p2y * wy_i;
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
  double error = wy * (ref_x - x_cg_ds) - wx * (ref_y - y_cg_ds);
  double delta_yaw = fmod(-ref_yaw + beta_s + state.psi, 2 * M_PI);
  if (delta_yaw > M_PI) 
  {
    delta_yaw = delta_yaw - 2 * M_PI;
  }

  vector<double> error_msg_vector;
  error_msg_vector.push_back(error);
  error_msg_vector.push_back(delta_yaw);
  error_msg_vector.push_back(ref_x);
  error_msg_vector.push_back(ref_y);
  error_msg_vector.push_back(ref_v);
  error_msg_vector.push_back(ref_yaw);
  error_msg_vector.push_back(ref_kappa);
  error_msg_vector.push_back(x_cg_ds);
  error_msg_vector.push_back(y_cg_ds);

  return error_msg_vector;
}

path_follower::Trajectory2D Transient(const path_follower::Trajectory2D traj, const path_follower::TrajectoryPoint2D point, const path_follower::state_Dynamic state, double ra_to_cg, double ds, int num_points)
{
  double start_time = ros::Time::now().toSec();
  double x_cg_ds = state.X + cos(state.psi) * (ra_to_cg + ds);
  double y_cg_ds = state.Y + sin(state.psi) * (ra_to_cg + ds);
  double beta_s = atan2(state.vy, state.vx) + ds / state.vx * state.wz; 
  double ref_x = x_cg_ds;
  double ref_y = y_cg_ds; 
  double ref_yaw = 0; 
  double ref_kappa = 0; 
  double ref_v = state.vx;
  double wx = 0;
  double wy = 0;
  double index = 0;
  for (int i = 1; i < (int)traj.point.size(); i++)
  {
    double wx_i = cos(state.psi + beta_s);
    double wy_i = sin(state.psi + beta_s);
    double p1x = traj.point[i-1].x - x_cg_ds;
    double p1y = traj.point[i-1].y - y_cg_ds;
    double p2x = traj.point[i].x - x_cg_ds;
    double p2y = traj.point[i].y - y_cg_ds;
    double d1 = p1x * wx_i + p1y * wy_i;
    double d2 = p2x * wx_i + p2y * wy_i;
    if (signbit(d1) != signbit(d2) || d1 == 0 || d2 == 0) 
    {
      index = (abs(d1)>=abs(d2)) ? i : i-1;
      break;
    }
  }

  double dt = traj.point[1].t - traj.point[0].t;
  MatrixXd x_ref((num_points+1)*2, 1);
  x_ref.setZero();
  x_ref(0, 0) = 0.;
  x_ref(1, 0) = 0.;
  x_ref(2, 0) = point.v * cos(point.theta) * dt;
  x_ref(3, 0) = point.v * sin(point.theta) * dt;
  for (int i=1; i<num_points; i++)
  {
    x_ref((i+1)*2, 0) = traj.point[index+i].x - point.x;
    x_ref((i+1)*2+1, 0) = traj.point[index+i].y - point.y;
    //cout<<x_ref((i+1)*2, 0)<<','<<x_ref((i+1)*2+1, 0)<<endl;
  }

  double w1 = 70;
  double w2 = 10;
  double factor = 0.01;
  MatrixXd V((num_points-1)*2, (num_points+1)*2);
  MatrixXd A((num_points-1)*2, (num_points+1)*2);
  V.setZero();
  A.setZero();
  for (int i=0; i<num_points-1; i++) 
  {
    V.block(i*2, (i+1)*2, 2, 2) = - Eigen::Matrix<double, 2, 2>::Identity();
    V.block(i*2, (i+2)*2, 2, 2) = Eigen::Matrix<double, 2, 2>::Identity();
    A.block(i*2, i*2, 2, 2) = Eigen::Matrix<double, 2, 2>::Identity() * (1./dt);
    A.block(i*2, (i+1)*2, 2, 2) = - 2 * Eigen::Matrix<double, 2, 2>::Identity() * (1./dt);
    A.block(i*2, (i+2)*2, 2, 2) = Eigen::Matrix<double, 2, 2>::Identity() * (1./dt);    
  }
  MatrixXd H((num_points+1)*2, (num_points+1)*2);
  MatrixXd g((num_points+1)*2, 1);
  H.setZero();
  g.setZero();
  H = factor * 2 * (MatrixXd::Identity((num_points+1)*2, (num_points+1)*2) * pow(dt, 2) + w1 * V.transpose() * V + w2 * A.transpose() * A);
  g = - factor * 2 * (MatrixXd::Identity((num_points+1)*2, (num_points+1)*2) * pow(dt, 2) + w1 * V.transpose() * V) * x_ref;

  MatrixXd Hs((num_points-3)*2, (num_points-3)*2);
  MatrixXd gs((num_points-3)*2, 1);
  Hs = H.block(4, 4, (num_points-3)*2, (num_points-3)*2);
  gs = g.block(4, 0, (num_points-3)*2, 1) + H.block(4, 0, (num_points-3)*2, 4)*x_ref.block(0, 0, 4, 1) + H.block(4, (num_points-1)*2, (num_points-3)*2, 4)*x_ref.block((num_points-1)*2, 0, 4, 1);
  ArrayXd aH = Map<const ArrayXd>(Hs.data(), Hs.size());
  ArrayXd ag = Map<const ArrayXd>(gs.data(), gs.size());
  real_t tH[aH.size()];
  real_t tg[ag.size()];
  Array2realt(aH, tH);
  Array2realt(ag, tg);
  real_t lb[(num_points-3)*2];
  real_t ub[(num_points-3)*2];
  for (int i=0; i<(num_points-3)*2; i++)
  {
    lb[i] = -100;
    ub[i] = 100;
  }
  QProblemB example((num_points-3)*2);
  Options options;
  example.setOptions(options);
  int_t nWSR = 1000;
  example.init(tH, tg, lb, ub, nWSR);
  real_t xOpt[(num_points-3)*2];
  example.getPrimalSolution(xOpt);

  path_follower::Trajectory2D traj_new;
  double ax = 0.;
  double ay = 0.;
  double vx = 0.;
  double vy = 0.;
  traj_new.point.clear();
  traj_new.point.push_back(point);
  traj_new.point[0].t = 0;
  path_follower::TrajectoryPoint2D pt;
  vx = (xOpt[0] - x_ref(2, 0)) / dt;
  vy = (xOpt[1] - x_ref(3, 0)) / dt;
  cout<<xOpt[0]<<','<<xOpt[1]<<','<<x_ref(2, 0)<<','<<x_ref(3, 0)<<endl;
  ax = (x_ref(0, 0) - 2 * x_ref(2, 0) + xOpt[0]) / pow(dt, 2);
  ay = (x_ref(1, 0) - 2 * x_ref(3, 0) + xOpt[1]) / pow(dt, 2);
  pt.t = dt;
  pt.x = x_ref(2, 0) + point.x;
  pt.y = x_ref(3, 0) + point.y;
  pt.v = sqrt(pow(vx, 2) + pow(vy, 2));
  pt.theta = atan2(vy, vx);
  pt.kappa = (vx*ay - vy*ax) / pow(pow(vx, 2) + pow(vy, 2), 1.5);
  traj_new.point.push_back(pt);

  for (int i=1; i < (int)traj.point.size() - index; i++)
  { 
    if (i >= 1 && i < num_points-2)
    {
      double vx = (xOpt[i*2] - xOpt[(i-1)*2]) / dt;
      double vy = (xOpt[i*2+1] - xOpt[(i-1)*2+1]) / dt;
      if (i == 1)
      {
        ax = (x_ref(2, 0) - 2 * xOpt[(i-1)*2] + xOpt[i*2]) / pow(dt, 2);
        ay = (x_ref(3, 0) - 2 * xOpt[(i-1)*2+1] + xOpt[i*2+1]) / pow(dt, 2);
      }
      else if (i == num_points - 3)
      {
        ax = (xOpt[(i-2)*2] - 2 * xOpt[(i-1)*2] + x_ref((num_points-1)*2, 0)) / pow(dt, 2);
        ay = (xOpt[(i-2)*2+1] - 2 * xOpt[(i-1)*2+1] + x_ref((num_points-1)*2+1, 0)) / pow(dt, 2);
      }
      else {
        ax = (xOpt[(i-2)*2] - 2 * xOpt[(i-1)*2] + xOpt[i*2]) / pow(dt, 2);
        ay = (xOpt[(i-2)*2+1] - 2 * xOpt[(i-1)*2+1] + xOpt[i*2+1]) / pow(dt, 2);
      }
      path_follower::TrajectoryPoint2D pt;
      pt.t = (i+1)*dt;
      pt.x = xOpt[(i-1)*2] + point.x;
      pt.y = xOpt[(i-1)*2+1] + point.y;
      pt.v = sqrt(pow(vx, 2) + pow(vy, 2));
      pt.theta = atan2(vy, vx);
      pt.kappa = (vx*ay - vy*ax) / pow(pow(vx, 2) + pow(vy, 2), 1.5);
      traj_new.point.push_back(pt);
    }
    else
    {
      traj_new.point.push_back(traj.point[index+i]);
    }
  }
  double end_time = ros::Time::now().toSec();
  cout<<end_time-start_time<<endl;
  return traj_new;
}
