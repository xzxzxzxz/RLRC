/*
 * DOB_ros_const.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros_const".
 *
 * Model version              : 1.241
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Thu Feb 28 11:58:52 2019
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_DOB_ros_const_h_
#define RTW_HEADER_DOB_ros_const_h_
#include <stddef.h>
#include <string.h>
#ifndef DOB_ros_const_COMMON_INCLUDES_
# define DOB_ros_const_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* DOB_ros_const_COMMON_INCLUDES_ */

#include "DOB_ros_const_types.h"

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
  SL_Bus_DOB_ros_const_dbw_mkz_msgs_SteeringReport In1;/* '<S9>/In1' */
  SL_Bus_DOB_ros_const_dbw_mkz_msgs_SteeringReport b_varargout_2;
  char_T cv0[25];
  SL_Bus_DOB_ros_const_controller_TrackingInfo In1_i;/* '<S10>/In1' */
  SL_Bus_DOB_ros_const_controller_TrackingInfo b_varargout_2_m;
} B_DOB_ros_const_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T D1_states[5];               /* '<Root>/D1' */
  real32_T Delay1_DSTATE[2];           /* '<Root>/Delay1' */
  real32_T Q1_states[2];               /* '<Root>/Q1' */
  robotics_slros_internal_block_T obj; /* '<S8>/SinkBlock' */
  robotics_slros_internal_block_T obj_f;/* '<S6>/SinkBlock' */
  robotics_slros_internal_blo_d_T obj_a;/* '<S4>/SourceBlock' */
  robotics_slros_internal_blo_d_T obj_ax;/* '<S3>/SourceBlock' */
  boolean_T objisempty;                /* '<S4>/SourceBlock' */
  boolean_T objisempty_n;              /* '<S3>/SourceBlock' */
  boolean_T objisempty_k;              /* '<S8>/SinkBlock' */
  boolean_T objisempty_f;              /* '<S6>/SinkBlock' */
} DW_DOB_ros_const_T;

/* Parameters (auto storage) */
struct P_DOB_ros_const_T_ {
  real32_T Dd[6];                      /* Variable: Dd
                                        * Referenced by: '<Root>/D1'
                                        */
  real32_T Dn[6];                      /* Variable: Dn
                                        * Referenced by: '<Root>/D1'
                                        */
  real32_T dt_ros_single;              /* Variable: dt_ros_single
                                        * Referenced by: '<S2>/Gain'
                                        */
  real32_T kc11;                       /* Variable: kc11
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real32_T kc12;                       /* Variable: kc12
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T kc2;                        /* Variable: kc2
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real32_T steering_ratio;             /* Variable: steering_ratio
                                        * Referenced by: '<S2>/Gain1'
                                        */
  SL_Bus_DOB_ros_const_dbw_mkz_msgs_SteeringReport Out1_Y0;/* Computed Parameter: Out1_Y0
                                                            * Referenced by: '<S9>/Out1'
                                                            */
  SL_Bus_DOB_ros_const_dbw_mkz_msgs_SteeringReport Constant_Value;/* Computed Parameter: Constant_Value
                                                                   * Referenced by: '<S3>/Constant'
                                                                   */
  SL_Bus_DOB_ros_const_dbw_mkz_msgs_SteeringCmd Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                                  * Referenced by: '<S7>/Constant'
                                                                  */
  SL_Bus_DOB_ros_const_controller_TrackingInfo Out1_Y0_n;/* Computed Parameter: Out1_Y0_n
                                                          * Referenced by: '<S10>/Out1'
                                                          */
  SL_Bus_DOB_ros_const_controller_TrackingInfo Constant_Value_j1;/* Computed Parameter: Constant_Value_j1
                                                                  * Referenced by: '<S4>/Constant'
                                                                  */
  SL_Bus_DOB_ros_const_controller_DobInfo Constant_Value_k;/* Computed Parameter: Constant_Value_k
                                                            * Referenced by: '<S5>/Constant'
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
  boolean_T Constant_Value_i;          /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S2>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_DOB_ros_const_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_DOB_ros_const_T DOB_ros_const_P;

#ifdef __cplusplus

}
#endif

/* Block signals (auto storage) */
extern B_DOB_ros_const_T DOB_ros_const_B;

/* Block states (auto storage) */
extern DW_DOB_ros_const_T DOB_ros_const_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void DOB_ros_const_initialize(void);
  extern void DOB_ros_const_step(void);
  extern void DOB_ros_const_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_DOB_ros_const_T *const DOB_ros_const_M;

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
 * '<Root>' : 'DOB_ros_const'
 * '<S1>'   : 'DOB_ros_const/DOB Info'
 * '<S2>'   : 'DOB_ros_const/Enabled Subsystem1'
 * '<S3>'   : 'DOB_ros_const/Subscribe'
 * '<S4>'   : 'DOB_ros_const/Subscribe1'
 * '<S5>'   : 'DOB_ros_const/DOB Info/Blank Message'
 * '<S6>'   : 'DOB_ros_const/DOB Info/Publish'
 * '<S7>'   : 'DOB_ros_const/Enabled Subsystem1/Blank Message'
 * '<S8>'   : 'DOB_ros_const/Enabled Subsystem1/Publish'
 * '<S9>'   : 'DOB_ros_const/Subscribe/Enabled Subsystem'
 * '<S10>'  : 'DOB_ros_const/Subscribe1/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_DOB_ros_const_h_ */
