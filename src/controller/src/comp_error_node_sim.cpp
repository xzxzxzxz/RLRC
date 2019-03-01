/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#include "controller/comp_error_core.h"
#include <controller/DynamicParamConfig.h>
#include <dynamic_reconfigure/server.h>
#include <iostream>   
using namespace std;

path_follower::state_Dynamic current_state;
path_follower::Trajectory2D ref_traj, traj_new;
path_follower::TrajectoryPoint2D prev_ref_point;

bool received_traj_flag = false, received_state_flag = false, ref_point_flag = false;
double ds;

void StateCallback(const path_follower::state_Dynamic msg) 
{
  current_state = msg;
  received_state_flag = true;
}

void TrajCallback(const path_follower::Trajectory2D msg)
{
  ref_traj = msg;
  received_traj_flag = true;
  if (received_state_flag && ref_point_flag)
  {
    traj_new = Transient(ref_traj, prev_ref_point, current_state, 0, ds, 50);
    //traj_new = ref_traj;
  }
  else
  {
    traj_new = ref_traj;
  }
}

void DynamicCallback(controller::DynamicParamConfig &config, uint32_t level)
{
  ds = config.ds;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "comp_error");
  ros::NodeHandle n;
  ros::Subscriber sub_state = n.subscribe("state_estimate", 1, StateCallback); 
  ros::Subscriber sub_traj  = n.subscribe("final_trajectory_origin", 1, TrajCallback);
  dynamic_reconfigure::Server<controller::DynamicParamConfig> server;
  dynamic_reconfigure::Server<controller::DynamicParamConfig>::CallbackType f;
  f = boost::bind(&DynamicCallback, _1, _2);
  server.setCallback(f);

  ros::Publisher error_pub = n.advertise<controller::TrackingInfo>("tracking_info", 1); 
  ros::Publisher error_old_pub = n.advertise<controller::TrackingInfo>("tracking_info_old", 1); 
  ros::Publisher traj_cg_pub = n.advertise<path_follower::Trajectory2D>("/vehicle/traj_cg", 1);
  ros::Publisher traj_new_pub = n.advertise<path_follower::Trajectory2D>("smooth_trajectory", 1);
  ros::Rate loop_rate(50);

  controller::TrackingInfo tracking_info;
  controller::TrackingInfo tracking_info_old;
  path_follower::Trajectory2D traj_cg;
  path_follower::TrajectoryPoint2D cg_point,ds_point,ref_point;

  vlr::vehicle_state p_vs;
  p_vs.set_mkz_params();

  ROS_INFO_STREAM("error computation node starts");
 
  bool init = false;
  double prev_dtheta, prev_theta;
  while(ros::ok())
  {
  	ros::spinOnce();
    if (received_traj_flag == true && received_state_flag == true)
    {
      vector<double> error_msg = ComputeLateralError(traj_new, current_state, 0, ds);
      vector<double> error_msg_old = ComputeLateralError(ref_traj, current_state, 0, ds);
      double v = sqrt(pow(current_state.vx, 2) + pow(current_state.vy, 2));
      tracking_info.v = v;
      tracking_info.dy = error_msg[0];
      tracking_info.dtheta = error_msg[1];
      tracking_info.kappa = error_msg[6];
      tracking_info_old.v = v;
      tracking_info_old.dy = error_msg_old[0];
      tracking_info_old.dtheta = error_msg_old[1];
      tracking_info_old.kappa = error_msg_old[6];
      cg_point.x = error_msg[7];
      cg_point.y = error_msg[8];
      ds_point.x = error_msg[7];
      ds_point.y = error_msg[8];
      ref_point.x = error_msg[2];
      ref_point.y = error_msg[3];
      ref_point.v = error_msg[4];
      ref_point.theta = error_msg[5];
      ref_point.kappa = error_msg[6];
      traj_cg.point.push_back(ds_point);
      traj_cg.point.push_back(ref_point);
      error_pub.publish(tracking_info);
      error_old_pub.publish(tracking_info_old);
      traj_cg_pub.publish(traj_cg);
      traj_cg.point.clear();
      prev_ref_point = ref_point;
      ref_point_flag = true;
      traj_new_pub.publish(traj_new);
      //cout<<"curvature: "<<ref_point.kappa<<endl;
    }

  	loop_rate.sleep();
  }

  return 0;
}
