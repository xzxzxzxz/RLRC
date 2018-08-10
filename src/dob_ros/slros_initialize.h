#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block DOB_ros/Subscribe
extern SimulinkSubscriber<dbw_mkz_msgs::SteeringReport, SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport> Sub_DOB_ros_191;

// For Block DOB_ros/Subscribe1
extern SimulinkSubscriber<controller::TrackingInfo, SL_Bus_DOB_ros_controller_TrackingInfo> Sub_DOB_ros_174;

// For Block DOB_ros/Enabled Subsystem1/Publish
extern SimulinkPublisher<dbw_mkz_msgs::SteeringCmd, SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd> Pub_DOB_ros_152;

// For Block DOB_ros/Tracking Received/Publish
extern SimulinkPublisher<controller::TrackingInfo, SL_Bus_DOB_ros_controller_TrackingInfo> Pub_DOB_ros_158;

void slros_node_init(int argc, char** argv);

#endif
