#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <dbw_mkz_msgs/SteeringCmd.h>
#include <dbw_mkz_msgs/SteeringReport.h>
#include <geometry_msgs/Pose2D.h>
#include <ros/time.h>
#include <std_msgs/Header.h>
#include "DOB_ros_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(dbw_mkz_msgs::SteeringCmd* msgPtr, SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd const* busPtr);
void convertToBus(SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd* busPtr, dbw_mkz_msgs::SteeringCmd const* msgPtr);

void convertFromBus(dbw_mkz_msgs::SteeringReport* msgPtr, SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport const* busPtr);
void convertToBus(SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport* busPtr, dbw_mkz_msgs::SteeringReport const* msgPtr);

void convertFromBus(geometry_msgs::Pose2D* msgPtr, SL_Bus_DOB_ros_geometry_msgs_Pose2D const* busPtr);
void convertToBus(SL_Bus_DOB_ros_geometry_msgs_Pose2D* busPtr, geometry_msgs::Pose2D const* msgPtr);

void convertFromBus(ros::Time* msgPtr, SL_Bus_DOB_ros_ros_time_Time const* busPtr);
void convertToBus(SL_Bus_DOB_ros_ros_time_Time* busPtr, ros::Time const* msgPtr);

void convertFromBus(std_msgs::Header* msgPtr, SL_Bus_DOB_ros_std_msgs_Header const* busPtr);
void convertToBus(SL_Bus_DOB_ros_std_msgs_Header* busPtr, std_msgs::Header const* msgPtr);


#endif
