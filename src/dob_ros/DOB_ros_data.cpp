/*
 * DOB_ros_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.184
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Sat Nov 17 11:17:43 2018
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DOB_ros.h"
#include "DOB_ros_private.h"

/* Block parameters (auto storage) */
P_DOB_ros_T DOB_ros_P = {
  /* Variable: Dd
   * Referenced by: '<Root>/D1'
   */
  { 1.0F, -1.98136818F, 1.23095572F, -0.245135844F, 0.0F, 0.0F },

  /* Variable: Dn
   * Referenced by: '<Root>/D1'
   */
  { 2.09422326F, -6.6583128F, 7.76546383F, -3.93288231F, 0.731508F, 0.0F },

  /* Variable: dt_ros_single
   * Referenced by: '<S1>/Gain'
   */
  0.02F,

  /* Variable: kc1
   * Referenced by: '<Root>/Gain3'
   */
  0.4F,

  /* Variable: kc2
   * Referenced by: '<Root>/Gain5'
   */
  0.06F,

  /* Variable: steering_ratio
   * Referenced by: '<S1>/Gain1'
   */
  14.8F,

  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S7>/Out1'
   */
  {
    0.0F,                              /* SteeringWheelAngle */
    0.0F,                              /* SteeringWheelAngleCmd */
    0.0F,                              /* SteeringWheelTorque */
    0.0F,                              /* Speed */
    false,                             /* Enabled */
    false,                             /* Override */
    false,                             /* Timeout */
    false,                             /* FaultWdc */
    false,                             /* FaultBus1 */
    false,                             /* FaultBus2 */
    false,                             /* FaultCalibration */

    {
      0U,                              /* Seq */

      {
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U }
      ,                                /* FrameId */

      {
        0U,                            /* CurrentLength */
        0U                             /* ReceivedLength */
      },                               /* FrameId_SL_Info */

      {
        0.0,                           /* Sec */
        0.0                            /* Nsec */
      }                                /* Stamp */
    }                                  /* Header */
  },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S2>/Constant'
   */
  {
    0.0F,                              /* SteeringWheelAngle */
    0.0F,                              /* SteeringWheelAngleCmd */
    0.0F,                              /* SteeringWheelTorque */
    0.0F,                              /* Speed */
    false,                             /* Enabled */
    false,                             /* Override */
    false,                             /* Timeout */
    false,                             /* FaultWdc */
    false,                             /* FaultBus1 */
    false,                             /* FaultBus2 */
    false,                             /* FaultCalibration */

    {
      0U,                              /* Seq */

      {
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U }
      ,                                /* FrameId */

      {
        0U,                            /* CurrentLength */
        0U                             /* ReceivedLength */
      },                               /* FrameId_SL_Info */

      {
        0.0,                           /* Sec */
        0.0                            /* Nsec */
      }                                /* Stamp */
    }                                  /* Header */
  },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S5>/Constant'
   */
  {
    0.0F,                              /* SteeringWheelAngleCmd */
    0.0F,                              /* SteeringWheelAngleVelocity */
    false,                             /* Enable */
    false,                             /* Clear */
    false,                             /* Ignore */
    false,                             /* Quiet */
    0U                                 /* Count */
  },

  /* Computed Parameter: Out1_Y0_n
   * Referenced by: '<S8>/Out1'
   */
  {
    0.0F,                              /* Vx */
    0.0F,                              /* Dy */
    0.0F                               /* Dtheta */
  },

  /* Computed Parameter: Constant_Value_j1
   * Referenced by: '<S3>/Constant'
   */
  {
    0.0F,                              /* Vx */
    0.0F,                              /* Dy */
    0.0F                               /* Dtheta */
  },

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S9>/Constant'
   */
  {
    0.0F,                              /* Vx */
    0.0F,                              /* Dy */
    0.0F                               /* Dtheta */
  },

  /* Computed Parameter: D1_InitialStates
   * Referenced by: '<Root>/D1'
   */
  0.0F,

  /* Computed Parameter: Delay1_InitialCondition
   * Referenced by: '<Root>/Delay1'
   */
  0.0F,

  /* Expression: NQ{1}
   * Referenced by: '<Root>/Q1'
   */
  { 0.01F, 0.0F, 0.0F },

  /* Expression: DQ{1}
   * Referenced by: '<Root>/Q1'
   */
  { 1.0F, -1.0F, 0.01F },

  /* Computed Parameter: Q1_InitialStates
   * Referenced by: '<Root>/Q1'
   */
  0.0F,

  /* Computed Parameter: Delay1_DelayLength
   * Referenced by: '<Root>/Delay1'
   */
  2U
};
