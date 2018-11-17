/*
 * DOB_ros.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.185
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Sat Nov 17 12:19:06 2018
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_DOB_ros_h_
#define RTW_HEADER_DOB_ros_h_
#include <stddef.h>
#include <string.h>
#ifndef DOB_ros_COMMON_INCLUDES_
# define DOB_ros_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* DOB_ros_COMMON_INCLUDES_ */

#include "DOB_ros_types.h"

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
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport In1;/* '<S7>/In1' */
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport b_varargout_2;
  char_T cv0[25];
  SL_Bus_DOB_ros_controller_TrackingInfo In1_i;/* '<S8>/In1' */
} B_DOB_ros_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T D1_states[5];               /* '<Root>/D1' */
  real32_T Delay1_DSTATE[2];           /* '<Root>/Delay1' */
  real32_T Q1_states[2];               /* '<Root>/Q1' */
  robotics_slros_internal_block_T obj; /* '<S10>/SinkBlock' */
  robotics_slros_internal_block_T obj_e;/* '<S6>/SinkBlock' */
  robotics_slros_internal_blo_k_T obj_a;/* '<S3>/SourceBlock' */
  robotics_slros_internal_blo_k_T obj_ax;/* '<S2>/SourceBlock' */
  boolean_T objisempty;                /* '<S10>/SinkBlock' */
  boolean_T objisempty_d;              /* '<S3>/SourceBlock' */
  boolean_T objisempty_n;              /* '<S2>/SourceBlock' */
  boolean_T objisempty_k;              /* '<S6>/SinkBlock' */
} DW_DOB_ros_T;

/* Parameters (auto storage) */
struct P_DOB_ros_T_ {
  real32_T Dd[6];                      /* Variable: Dd
                                        * Referenced by: '<Root>/D1'
                                        */
  real32_T Dn[6];                      /* Variable: Dn
                                        * Referenced by: '<Root>/D1'
                                        */
  real32_T dt_ros_single;              /* Variable: dt_ros_single
                                        * Referenced by: '<S1>/Gain'
                                        */
  real32_T kc1;                        /* Variable: kc1
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real32_T kc2;                        /* Variable: kc2
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real32_T steering_ratio;             /* Variable: steering_ratio
                                        * Referenced by: '<S1>/Gain1'
                                        */
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport Out1_Y0;/* Computed Parameter: Out1_Y0
                                                      * Referenced by: '<S7>/Out1'
                                                      */
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport Constant_Value;/* Computed Parameter: Constant_Value
                                                             * Referenced by: '<S2>/Constant'
                                                             */
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                            * Referenced by: '<S5>/Constant'
                                                            */
  SL_Bus_DOB_ros_controller_TrackingInfo Out1_Y0_n;/* Computed Parameter: Out1_Y0_n
                                                    * Referenced by: '<S8>/Out1'
                                                    */
  SL_Bus_DOB_ros_controller_TrackingInfo Constant_Value_j1;/* Computed Parameter: Constant_Value_j1
                                                            * Referenced by: '<S3>/Constant'
                                                            */
  SL_Bus_DOB_ros_controller_TrackingInfo Constant_Value_i;/* Computed Parameter: Constant_Value_i
                                                           * Referenced by: '<S9>/Constant'
                                                           */
  real32_T D1_InitialStates;           /* Computed Parameter: D1_InitialStates
                                        * Referenced by: '<Root>/D1'
                                        */
  real32_T Delay1_InitialCondition;    /* Computed Parameter: Delay1_InitialCondition
                                        * Referenced by: '<Root>/Delay1'
                                        */
  real32_T Q1_NumCoef[3];              /* Expression: NQ{1}
                                        * Referenced by: '<Root>/Q1'
                                        */
  real32_T Q1_DenCoef[3];              /* Expression: DQ{1}
                                        * Referenced by: '<Root>/Q1'
                                        */
  real32_T Q1_InitialStates;           /* Computed Parameter: Q1_InitialStates
                                        * Referenced by: '<Root>/Q1'
                                        */
  uint32_T Delay1_DelayLength;         /* Computed Parameter: Delay1_DelayLength
                                        * Referenced by: '<Root>/Delay1'
                                        */
  boolean_T Constant_Value_ij;         /* Computed Parameter: Constant_Value_ij
                                        * Referenced by: '<S1>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_DOB_ros_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_DOB_ros_T DOB_ros_P;

#ifdef __cplusplus

}
#endif

/* Block signals (auto storage) */
extern B_DOB_ros_T DOB_ros_B;

/* Block states (auto storage) */
extern DW_DOB_ros_T DOB_ros_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void DOB_ros_initialize(void);
  extern void DOB_ros_step(void);
  extern void DOB_ros_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_DOB_ros_T *const DOB_ros_M;

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
 * '<Root>' : 'DOB_ros'
 * '<S1>'   : 'DOB_ros/Enabled Subsystem1'
 * '<S2>'   : 'DOB_ros/Subscribe'
 * '<S3>'   : 'DOB_ros/Subscribe1'
 * '<S4>'   : 'DOB_ros/Tracking Received'
 * '<S5>'   : 'DOB_ros/Enabled Subsystem1/Blank Message'
 * '<S6>'   : 'DOB_ros/Enabled Subsystem1/Publish'
 * '<S7>'   : 'DOB_ros/Subscribe/Enabled Subsystem'
 * '<S8>'   : 'DOB_ros/Subscribe1/Enabled Subsystem'
 * '<S9>'   : 'DOB_ros/Tracking Received/Blank Message'
 * '<S10>'  : 'DOB_ros/Tracking Received/Publish'
 */
#endif                                 /* RTW_HEADER_DOB_ros_h_ */
