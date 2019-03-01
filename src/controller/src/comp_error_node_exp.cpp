/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#include "controller/comp_error_core.h"
#include <controller/DynamicParamConfig.h>
#include <dynamic_reconfigure/server.h>
#include <std_msgs/Bool.h>
#include <iostream>   
using namespace std;

path_follower::state_Dynamic current_state;
path_follower::Trajectory2D ref_traj;

bool received_traj_flag = false,received_state_flag = false;
double ds;
bool sys_enable_;

void StateCallback(const path_follower::state_Dynamic msg) 
{
  current_state = msg;
  received_state_flag = true;
}

void TrajCallback(const path_follower::Trajectory2D msg)
{
  ref_traj = msg;
  received_traj_flag = true;
}

void DynamicCallback(controller::DynamicParamConfig &config, uint32_t level)
{
  ds = config.ds;
}

void EnableCallback(const std_msgs::Bool::ConstPtr& msg)
{
  sys_enable_ = msg->data;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "comp_error");
  ros::NodeHandle n;
  ros::Subscriber sub_state = n.subscribe("state_estimate", 1, StateCallback); 
  ros::Subscriber sub_traj  = n.subscribe("final_trajectory", 1, TrajCallback);
  ros::Subscriber sub_enable_ = n.subscribe("vehicle/dbw_enabled", 1, EnableCallback);
  dynamic_reconfigure::Server<controller::DynamicParamConfig> server;
  dynamic_reconfigure::Server<controller::DynamicParamConfig>::CallbackType f;
  f = boost::bind(&DynamicCallback, _1, _2);
  server.setCallback(f);

  ros::Publisher error_pub = n.advertise<controller::TrackingInfo>("tracking_info", 1); 
  //ros::Publisher vel_cmd_pub = n.advertise<geometry_msgs::TwistStamped>("/vehicle/cmd_vel_stamped", 1);
  ros::Publisher traj_cg_pub = n.advertise<path_follower::Trajectory2D>("/vehicle/traj_cg", 1);
  ros::Rate loop_rate(50);

  //geometry_msgs::TwistStamped cmd_vel_stamped;
  controller::TrackingInfo tracking_info;
  path_follower::Trajectory2D traj_cg;
  path_follower::TrajectoryPoint2D cg_point,ds_point,ref_point;

  vlr::vehicle_state p_vs;
  p_vs.set_mkz_params();

  ROS_INFO_STREAM("error computation node starts");
 
  while(ros::ok())
  {
  	ros::spinOnce();
    if (received_traj_flag == true && received_state_flag == true)
    {
      double factor = (sys_enable_) ? 1. : 0.;
      vector<double> error_msg = ComputeLateralError(ref_traj, current_state, p_vs.param.b, ds);
      tracking_info.v = sqrt(pow(current_state.vx, 2) + pow(current_state.vy, 2));
      tracking_info.dy = error_msg[0] * factor;
      tracking_info.dtheta = error_msg[1] * factor;
      tracking_info.kappa = error_msg[6];
      ds_point.x=error_msg[7];
      ds_point.y=error_msg[8];
      ref_point.x=error_msg[2];
      ref_point.y=error_msg[3];
      ref_point.v=error_msg[4];
      ref_point.theta=error_msg[5];
      ref_point.kappa=error_msg[6];
      traj_cg.point.push_back(ds_point);
      traj_cg.point.push_back(ref_point);

      error_pub.publish(tracking_info);
      traj_cg_pub.publish(traj_cg);
      traj_cg.point.clear();
    }

  	loop_rate.sleep();
  }

  return 0;
}
