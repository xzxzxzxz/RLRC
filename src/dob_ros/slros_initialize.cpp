#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "DOB_ros";

// For Block DOB_ros/Subscribe
SimulinkSubscriber<dbw_mkz_msgs::SteeringReport, SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport> Sub_DOB_ros_191;

// For Block DOB_ros/Subscribe1
SimulinkSubscriber<controller::TrackingInfo, SL_Bus_DOB_ros_controller_TrackingInfo> Sub_DOB_ros_174;

// For Block DOB_ros/Enabled Subsystem1/Publish
SimulinkPublisher<dbw_mkz_msgs::SteeringCmd, SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd> Pub_DOB_ros_152;

// For Block DOB_ros/Tracking Received/Publish
SimulinkPublisher<controller::TrackingInfo, SL_Bus_DOB_ros_controller_TrackingInfo> Pub_DOB_ros_158;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

