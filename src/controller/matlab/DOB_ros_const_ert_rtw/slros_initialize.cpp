#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "DOB_ros_const";

// For Block DOB_ros_const/Subscribe
SimulinkSubscriber<dbw_mkz_msgs::SteeringReport, SL_Bus_DOB_ros_const_dbw_mkz_msgs_SteeringReport> Sub_DOB_ros_const_191;

// For Block DOB_ros_const/Subscribe1
SimulinkSubscriber<controller::TrackingInfo, SL_Bus_DOB_ros_const_controller_TrackingInfo> Sub_DOB_ros_const_174;

// For Block DOB_ros_const/DOB Info/Publish
SimulinkPublisher<controller::DobInfo, SL_Bus_DOB_ros_const_controller_DobInfo> Pub_DOB_ros_const_209;

// For Block DOB_ros_const/Enabled Subsystem1/Publish
SimulinkPublisher<dbw_mkz_msgs::SteeringCmd, SL_Bus_DOB_ros_const_dbw_mkz_msgs_SteeringCmd> Pub_DOB_ros_const_152;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

