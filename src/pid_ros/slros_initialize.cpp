#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "PID_ros";

// For Block PID_ros/Subscribe
SimulinkSubscriber<dbw_mkz_msgs::SteeringReport, SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport> Sub_PID_ros_191;

// For Block PID_ros/Subscribe1
SimulinkSubscriber<controller::TrackingInfo, SL_Bus_PID_ros_controller_TrackingInfo> Sub_PID_ros_174;

// For Block PID_ros/Enabled Subsystem1/Publish
SimulinkPublisher<dbw_mkz_msgs::SteeringCmd, SL_Bus_PID_ros_dbw_mkz_msgs_SteeringCmd> Pub_PID_ros_152;

// For Block PID_ros/Tracking Received/Publish
SimulinkPublisher<controller::TrackingInfo, SL_Bus_PID_ros_controller_TrackingInfo> Pub_PID_ros_158;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

