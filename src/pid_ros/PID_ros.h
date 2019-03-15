/*
 * PID_ros.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PID_ros".
 *
 * Model version              : 1.191
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Fri Mar 15 13:41:14 2019
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PID_ros_h_
#define RTW_HEADER_PID_ros_h_
#include <stddef.h>
#include <string.h>
#ifndef PID_ros_COMMON_INCLUDES_
# define PID_ros_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* PID_ros_COMMON_INCLUDES_ */

#include "PID_ros_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport In1;/* '<S6>/In1' */
  SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport b_varargout_2;
  char_T cv0[25];
  SL_Bus_PID_ros_controller_TrackingInfo In1_i;/* '<S7>/In1' */
} B_PID_ros_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  robotics_slros_internal_block_T obj; /* '<S5>/SinkBlock' */
  robotics_slros_internal_blo_j_T obj_a;/* '<S3>/SourceBlock' */
  robotics_slros_internal_blo_j_T obj_ax;/* '<S2>/SourceBlock' */
  boolean_T objisempty;                /* '<S3>/SourceBlock' */
  boolean_T objisempty_n;              /* '<S2>/SourceBlock' */
  boolean_T objisempty_k;              /* '<S5>/SinkBlock' */
} DW_PID_ros_T;

/* Parameters (auto storage) */
struct P_PID_ros_T_ {
  real32_T dt_ros_single;              /* Variable: dt_ros_single
                                        * Referenced by: '<S1>/Gain'
                                        */
  real32_T kc11;                       /* Variable: kc11
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real32_T kc12;                       /* Variable: kc12
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T steering_ratio;             /* Variable: steering_ratio
                                        * Referenced by: '<S1>/Gain1'
                                        */
  SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport Out1_Y0;/* Computed Parameter: Out1_Y0
                                                      * Referenced by: '<S6>/Out1'
                                                      */
  SL_Bus_PID_ros_dbw_mkz_msgs_SteeringReport Constant_Value;/* Computed Parameter: Constant_Value
                                                             * Referenced by: '<S2>/Constant'
                                                             */
  SL_Bus_PID_ros_dbw_mkz_msgs_SteeringCmd Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                            * Referenced by: '<S4>/Constant'
                                                            */
  SL_Bus_PID_ros_controller_TrackingInfo Out1_Y0_n;/* Computed Parameter: Out1_Y0_n
                                                    * Referenced by: '<S7>/Out1'
                                                    */
  SL_Bus_PID_ros_controller_TrackingInfo Constant_Value_j1;/* Computed Parameter: Constant_Value_j1
                                                            * Referenced by: '<S3>/Constant'
                                                            */
  real32_T Gain5_Gain;                 /* Computed Parameter: Gain5_Gain
                                        * Referenced by: '<Root>/Gain5'
                                        */
  boolean_T Constant_Value_i;          /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S1>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PID_ros_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_PID_ros_T PID_ros_P;

#ifdef __cplusplus

}
#endif

/* Block signals (auto storage) */
extern B_PID_ros_T PID_ros_B;

/* Block states (auto storage) */
extern DW_PID_ros_T PID_ros_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void PID_ros_initialize(void);
  extern void PID_ros_step(void);
  extern void PID_ros_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_PID_ros_T *const PID_ros_M;

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PID_ros'
 * '<S1>'   : 'PID_ros/Enabled Subsystem1'
 * '<S2>'   : 'PID_ros/Subscribe'
 * '<S3>'   : 'PID_ros/Subscribe1'
 * '<S4>'   : 'PID_ros/Enabled Subsystem1/Blank Message'
 * '<S5>'   : 'PID_ros/Enabled Subsystem1/Publish'
 * '<S6>'   : 'PID_ros/Subscribe/Enabled Subsystem'
 * '<S7>'   : 'PID_ros/Subscribe1/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_PID_ros_h_ */
