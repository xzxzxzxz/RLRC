/*
 * DOB_ros_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.187
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Thu Dec 13 11:03:58 2018
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_DOB_ros_types_h_
#define RTW_HEADER_DOB_ros_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd_
#define DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd_

typedef struct {
  real32_T SteeringWheelAngleCmd;
  real32_T SteeringWheelAngleVelocity;
  boolean_T Enable;
  boolean_T Clear;
  boolean_T Ignore;
  boolean_T Quiet;
  uint8_T Count;
} SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

typedef struct {
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
} SL_Bus_ROSVariableLengthArrayInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_ros_time_Time_

typedef struct {
  real_T Sec;
  real_T Nsec;
} SL_Bus_DOB_ros_ros_time_Time;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_std_msgs_Header_

typedef struct {
  uint32_T Seq;
  uint8_T FrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;
  SL_Bus_DOB_ros_ros_time_Time Stamp;
} SL_Bus_DOB_ros_std_msgs_Header;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport_
#define DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport_

typedef struct {
  real32_T SteeringWheelAngle;
  real32_T SteeringWheelAngleCmd;
  real32_T SteeringWheelTorque;
  real32_T Speed;
  boolean_T Enabled;
  boolean_T Override;
  boolean_T Timeout;
  boolean_T FaultWdc;
  boolean_T FaultBus1;
  boolean_T FaultBus2;
  boolean_T FaultCalibration;
  SL_Bus_DOB_ros_std_msgs_Header Header;
} SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_controller_TrackingInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_DOB_ros_controller_TrackingInfo_

typedef struct {
  real32_T Vx;
  real32_T Dy;
  real32_T Dtheta;
} SL_Bus_DOB_ros_controller_TrackingInfo;

#endif

#ifndef typedef_robotics_slros_internal_block_T
#define typedef_robotics_slros_internal_block_T

typedef struct {
  int32_T isInitialized;
} robotics_slros_internal_block_T;

#endif                                 /*typedef_robotics_slros_internal_block_T*/

#ifndef typedef_robotics_slros_internal_blo_k_T
#define typedef_robotics_slros_internal_blo_k_T

typedef struct {
  int32_T isInitialized;
} robotics_slros_internal_blo_k_T;

#endif                                 /*typedef_robotics_slros_internal_blo_k_T*/

/* Parameters (auto storage) */
typedef struct P_DOB_ros_T_ P_DOB_ros_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_DOB_ros_T RT_MODEL_DOB_ros_T;

#endif                                 /* RTW_HEADER_DOB_ros_types_h_ */
