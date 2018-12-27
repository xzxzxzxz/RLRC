#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <controller/TrackingInfo.h>
#include <dbw_mkz_msgs/SteeringCmd.h>
#include <dbw_mkz_msgs/SteeringReport.h>
#include <ros/time.h>
#include <std_msgs/Header.h>
#include "PID_ros_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(controller::TrackingInfo* msgPtr, SL_Bus_PID_ros_controller_TrackingInfo const* busPtr);
void convertToBus(SL_Bus_PID_ros_controller_TrackingInfo* busPtr, controller::TrackingInfo const* msgPtr);

void convertFromBus(dbw_mkz_msgs::SteeringCmd* msgPtr, SL_Bus_PID_ros_dbw_mkz_msgs_SteeringCmd const* busPtr);
void convertToBus(SL_Bus_PID_ros_dbw_mkz_msgs_SteeringCmd* busPtr, dbw_mkz_msgs::SteeringCmd const* msgPtr);

void convertFromBus(dbw_mkz_msgs::SteeringReport* msgPtr, SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport const* busPtr);
void convertToBus(SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport* busPtr, dbw_mkz_msgs::SteeringReport const* msgPtr);

void convertFromBus(ros::Time* msgPtr, SL_Bus_PID_ros_ros_time_Time const* busPtr);
void convertToBus(SL_Bus_PID_ros_ros_time_Time* busPtr, ros::Time const* msgPtr);

void convertFromBus(std_msgs::Header* msgPtr, SL_Bus_PID_ros_std_msgs_Header const* busPtr);
void convertToBus(SL_Bus_PID_ros_std_msgs_Header* busPtr, std_msgs::Header const* msgPtr);


#endif
