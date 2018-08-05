/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/
#include "controller/comp_error_core.h"
#include <controller/DynamicParamConfig.h>
#include <dynamic_reconfigure/server.h>
using namespace std;

path_follower::state_Dynamic current_state;
path_follower::Trajectory2D ref_traj;
double ds;

void StateCallback(const path_follower::state_Dynamic msg) 
{
  current_state = msg;
}

void TrajCallback(const path_follower::Trajectory2D msg)
{
  ref_traj = msg;
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
  ros::Subscriber sub_traj  = n.subscribe("ref_trajectory", 1, TrajCallback);
  dynamic_reconfigure::Server<controller::DynamicParamConfig> server;
  dynamic_reconfigure::Server<controller::DynamicParamConfig>::CallbackType f;
  f = boost::bind(&DynamicCallback, _1, _2);
  server.setCallback(f);

  ros::Publisher error_pub = n.advertise<geometry_msgs::Pose2D>("tracking_error", 1); 
  ros::Publisher vel_cmd_pub = n.advertise<geometry_msgs::TwistStamped>("/vehicle/cmd_vel_stamped", 1);
  ros::Rate loop_rate(50);

  geometry_msgs::TwistStamped cmd_vel_stamped;
  geometry_msgs::Pose2D tracking_error;

  vlr::vehicle_state p_vs;
  p_vs.set_mkz_params();

  ROS_INFO_STREAM("error computation node starts");

  while(ros::ok())
  {
  	ros::spinOnce();
    vector<double> error_msg = ComputeTrackingError(ref_traj, current_state, p_vs.param.b, ds);

    tracking_error.x = error_msg[0];
    tracking_error.y = error_msg[1];
    tracking_error.theta = error_msg[2];

    cmd_vel_stamped.header.stamp = ros::Time::now();
    cmd_vel_stamped.twist.linear.x = error_msg[0];

    error_pub.publish(tracking_error);
    vel_cmd_pub.publish(cmd_vel_stamped);
  	loop_rate.sleep();
  }

  return 0;
}