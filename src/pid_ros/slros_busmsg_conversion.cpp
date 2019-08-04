#include "slros_busmsg_conversion.h"


// Conversions between SL_Bus_PID_ros_controller_TrackingInfo and controller::TrackingInfo

void convertFromBus(controller::TrackingInfo* msgPtr, SL_Bus_PID_ros_controller_TrackingInfo const* busPtr)
{
  const std::string rosMessageType("controller/TrackingInfo");

  msgPtr->dtheta =  busPtr->Dtheta;
  msgPtr->dy =  busPtr->Dy;
  msgPtr->kappa =  busPtr->Kappa;
  msgPtr->Q =  busPtr->Q;
  msgPtr->v =  busPtr->V;
}

void convertToBus(SL_Bus_PID_ros_controller_TrackingInfo* busPtr, controller::TrackingInfo const* msgPtr)
{
  const std::string rosMessageType("controller/TrackingInfo");

  busPtr->Dtheta =  msgPtr->dtheta;
  busPtr->Dy =  msgPtr->dy;
  busPtr->Kappa =  msgPtr->kappa;
  busPtr->Q =  msgPtr->Q;
  busPtr->V =  msgPtr->v;
}


// Conversions between SL_Bus_PID_ros_dbw_mkz_msgs_SteeringCmd and dbw_mkz_msgs::SteeringCmd

void convertFromBus(dbw_mkz_msgs::SteeringCmd* msgPtr, SL_Bus_PID_ros_dbw_mkz_msgs_SteeringCmd const* busPtr)
{
  const std::string rosMessageType("dbw_mkz_msgs/SteeringCmd");

  msgPtr->clear =  busPtr->Clear;
  msgPtr->count =  busPtr->Count;
  msgPtr->enable =  busPtr->Enable;
  msgPtr->ignore =  busPtr->Ignore;
  msgPtr->quiet =  busPtr->Quiet;
  msgPtr->steering_wheel_angle_cmd =  busPtr->SteeringWheelAngleCmd;
  msgPtr->steering_wheel_angle_velocity =  busPtr->SteeringWheelAngleVelocity;
}

void convertToBus(SL_Bus_PID_ros_dbw_mkz_msgs_SteeringCmd* busPtr, dbw_mkz_msgs::SteeringCmd const* msgPtr)
{
  const std::string rosMessageType("dbw_mkz_msgs/SteeringCmd");

  busPtr->Clear =  msgPtr->clear;
  busPtr->Count =  msgPtr->count;
  busPtr->Enable =  msgPtr->enable;
  busPtr->Ignore =  msgPtr->ignore;
  busPtr->Quiet =  msgPtr->quiet;
  busPtr->SteeringWheelAngleCmd =  msgPtr->steering_wheel_angle_cmd;
  busPtr->SteeringWheelAngleVelocity =  msgPtr->steering_wheel_angle_velocity;
}


// Conversions between SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport and dbw_mkz_msgs::SteeringReport

void convertFromBus(dbw_mkz_msgs::SteeringReport* msgPtr, SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport const* busPtr)
{
  const std::string rosMessageType("dbw_mkz_msgs/SteeringReport");

  msgPtr->enabled =  busPtr->Enabled;
  msgPtr->fault_bus1 =  busPtr->FaultBus1;
  msgPtr->fault_bus2 =  busPtr->FaultBus2;
  msgPtr->fault_calibration =  busPtr->FaultCalibration;
  msgPtr->fault_power =  busPtr->FaultPower;
  msgPtr->fault_wdc =  busPtr->FaultWdc;
  convertFromBus(&msgPtr->header, &busPtr->Header);
  msgPtr->override =  busPtr->Override;
  msgPtr->speed =  busPtr->Speed;
  msgPtr->steering_wheel_angle =  busPtr->SteeringWheelAngle;
  msgPtr->steering_wheel_angle_cmd =  busPtr->SteeringWheelAngleCmd;
  msgPtr->steering_wheel_torque =  busPtr->SteeringWheelTorque;
  msgPtr->timeout =  busPtr->Timeout;
}

void convertToBus(SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport* busPtr, dbw_mkz_msgs::SteeringReport const* msgPtr)
{
  const std::string rosMessageType("dbw_mkz_msgs/SteeringReport");

  busPtr->Enabled =  msgPtr->enabled;
  busPtr->FaultBus1 =  msgPtr->fault_bus1;
  busPtr->FaultBus2 =  msgPtr->fault_bus2;
  busPtr->FaultCalibration =  msgPtr->fault_calibration;
  busPtr->FaultPower =  msgPtr->fault_power;
  busPtr->FaultWdc =  msgPtr->fault_wdc;
  convertToBus(&busPtr->Header, &msgPtr->header);
  busPtr->Override =  msgPtr->override;
  busPtr->Speed =  msgPtr->speed;
  busPtr->SteeringWheelAngle =  msgPtr->steering_wheel_angle;
  busPtr->SteeringWheelAngleCmd =  msgPtr->steering_wheel_angle_cmd;
  busPtr->SteeringWheelTorque =  msgPtr->steering_wheel_torque;
  busPtr->Timeout =  msgPtr->timeout;
}


// Conversions between SL_Bus_PID_ros_ros_time_Time and ros::Time

void convertFromBus(ros::Time* msgPtr, SL_Bus_PID_ros_ros_time_Time const* busPtr)
{
  const std::string rosMessageType("ros_time/Time");

  msgPtr->sec =  busPtr->Sec;
  msgPtr->nsec =  busPtr->Nsec;
}

void convertToBus(SL_Bus_PID_ros_ros_time_Time* busPtr, ros::Time const* msgPtr)
{
  const std::string rosMessageType("ros_time/Time");

  busPtr->Sec =  msgPtr->sec;
  busPtr->Nsec =  msgPtr->nsec;
}


// Conversions between SL_Bus_PID_ros_std_msgs_Header and std_msgs::Header

void convertFromBus(std_msgs::Header* msgPtr, SL_Bus_PID_ros_std_msgs_Header const* busPtr)
{
  const std::string rosMessageType("std_msgs/Header");

  convertFromBusVariablePrimitiveArray(msgPtr->frame_id, busPtr->FrameId, busPtr->FrameId_SL_Info);
  msgPtr->seq =  busPtr->Seq;
  convertFromBus(&msgPtr->stamp, &busPtr->Stamp);
}

void convertToBus(SL_Bus_PID_ros_std_msgs_Header* busPtr, std_msgs::Header const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Header");

  convertToBusVariablePrimitiveArray(busPtr->FrameId, busPtr->FrameId_SL_Info, msgPtr->frame_id, slros::EnabledWarning(rosMessageType, "frame_id"));
  busPtr->Seq =  msgPtr->seq;
  convertToBus(&busPtr->Stamp, &msgPtr->stamp);
}

