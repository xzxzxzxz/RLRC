/*
 * DOB_ros_const_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros_const".
 *
 * Model version              : 1.244
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Sat Aug  3 16:06:32 2019
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DOB_ros_const.h"
#include "DOB_ros_const_private.h"

/* Block parameters (auto storage) */
P_DOB_ros_const_T DOB_ros_const_P = {
  /* Variable: Dd
   * Referenced by: '<Root>/D1'
   */
  { 1.0F, -2.66997576F, 2.35075307F, -0.680739403F, 0.0F, 0.0F },

  /* Variable: Dn
   * Referenced by: '<Root>/D1'
   */
  { 1.30035F, -4.36258268F, 5.42075491F, -2.95516133F, 0.596639276F, 0.0F },

  /* Variable: dt_ros_single
   * Referenced by: '<S3>/Gain'
   */
  0.02F,

  /* Variable: kc11
   * Referenced by: '<Root>/Gain3'
   */
  1.0F,

  /* Variable: kc12
   * Referenced by: '<Root>/Gain1'
   */
  0.02F,

  /* Variable: kc2
   * Referenced by: '<Root>/Gain5'
   */
  0.5F,

  /* Variable: steering_ratio
   * Referenced by: '<S3>/Gain1'
   */
  14.8F,

  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S10>/Out1'
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
   * Referenced by: '<S4>/Constant'
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

  /* Computed Parameter: Out1_Y0_n
   * Referenced by: '<S11>/Out1'
   */
  {
    0.0F,                              /* V */
    0.0F,                              /* Kappa */
    0.0F,                              /* Dy */
    0.0F,                              /* Dtheta */
    0.0F                               /* Q */
  },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S5>/Constant'
   */
  {
    0.0F,                              /* V */
    0.0F,                              /* Kappa */
    0.0F,                              /* Dy */
    0.0F,                              /* Dtheta */
    0.0F                               /* Q */
  },

  /* Computed Parameter: Constant_Value_jb
   * Referenced by: '<S8>/Constant'
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

  /* Computed Parameter: Constant_Value_k
   * Referenced by: '<S6>/Constant'
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

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<Root>/Gain'
   */
  1.0F,

  /* Computed Parameter: Delay1_InitialCondition_h
   * Referenced by: '<S2>/Delay1'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_km
   * Referenced by: '<Root>/Constant'
   */
  -1.0F,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<Root>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Delay2_InitialCondition
   * Referenced by: '<S2>/Delay2'
   */
  0.0F,

  /* Computed Parameter: Delay1_DelayLength
   * Referenced by: '<Root>/Delay1'
   */
  2U,

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S3>/Constant'
   */
  1
};
