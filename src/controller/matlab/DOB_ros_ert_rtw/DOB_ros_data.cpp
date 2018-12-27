/*
 * DOB_ros_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.192
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Thu Dec 27 10:14:04 2018
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
  { 1.0F, -1.81470156F, 0.984061122F, -0.163423911F, 0.0F, 0.0F },

  /* Variable: Dn
   * Referenced by: '<Root>/D1'
   */
  { 2.7922976F, -8.87775F, 10.3539515F, -5.24384308F, 0.975344062F, 0.0F },

  /* Variable: dt_ros_single
   * Referenced by: '<S2>/Gain'
   */
  0.02F,

  /* Variable: kc1
   * Referenced by: '<Root>/Gain3'
   */
  0.3F,

  /* Variable: kc2
   * Referenced by: '<Root>/Gain5'
   */
  0.1F,

  /* Variable: steering_ratio
   * Referenced by: '<S2>/Gain1'
   */
  14.8F,

  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S9>/Out1'
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
    false,                             /* FaultPower */

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
   * Referenced by: '<S3>/Constant'
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
    false,                             /* FaultPower */

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
   * Referenced by: '<S7>/Constant'
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
   * Referenced by: '<S10>/Out1'
   */
  {
    0.0F,                              /* Vx */
    0.0F,                              /* Dy */
    0.0F                               /* Dtheta */
  },

  /* Computed Parameter: Constant_Value_j1
   * Referenced by: '<S4>/Constant'
   */
  {
    0.0F,                              /* Vx */
    0.0F,                              /* Dy */
    0.0F                               /* Dtheta */
  },

  /* Computed Parameter: Constant_Value_k
   * Referenced by: '<S5>/Constant'
   */
  {
    0.0F,                              /* DEst */
    0.0F                               /* DCancel */
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
  { 0.1F, 0.0F, 0.0F },

  /* Expression: DQ{1}
   * Referenced by: '<Root>/Q1'
   */
  { 1.0F, -1.0F, 0.1F },

  /* Computed Parameter: Q1_InitialStates
   * Referenced by: '<Root>/Q1'
   */
  0.0F,

  /* Computed Parameter: Delay1_DelayLength
   * Referenced by: '<Root>/Delay1'
   */
  2U,

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S2>/Constant'
   */
  1
};
