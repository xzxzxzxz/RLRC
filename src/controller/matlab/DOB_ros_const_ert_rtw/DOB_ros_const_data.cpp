/*
 * DOB_ros_const_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros_const".
 *
 * Model version              : 1.234
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Sat Jan 12 11:47:13 2019
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
  /* Variable: a1
   * Referenced by: '<S5>/2-D Lookup Table1'
   */
  { -2.50966859F, -2.51066518F, -2.50966859F, -2.51066518F },

  /* Variable: a2
   * Referenced by: '<S5>/2-D Lookup Table3'
   */
  { 2.07939887F, 2.08146048F, 2.07939887F, 2.08146048F },

  /* Variable: a3
   * Referenced by: '<S5>/2-D Lookup Table7'
   */
  { -0.56875062F, -0.569805086F, -0.56875062F, -0.569805086F },

  /* Variable: b0
   * Referenced by: '<S5>/2-D Lookup Table'
   */
  { 0.671738505F, 0.676619649F, 0.671738505F, 0.676619649F },

  /* Variable: b1
   * Referenced by: '<S5>/2-D Lookup Table2'
   */
  { -2.25363541F, -2.27355146F, -2.25363541F, -2.27355146F },

  /* Variable: b2
   * Referenced by: '<S5>/2-D Lookup Table4'
   */
  { 2.80026913F, 2.83010125F, 2.80026913F, 2.83010125F },

  /* Variable: b3
   * Referenced by: '<S5>/2-D Lookup Table5'
   */
  { -1.5265857F, -1.54602659F, -1.5265857F, -1.54602659F },

  /* Variable: b4
   * Referenced by: '<S5>/2-D Lookup Table6'
   */
  { 0.308213621F, 0.312857211F, 0.308213621F, 0.312857211F },

  /* Variable: b5
   * Referenced by: '<S5>/2-D Lookup Table8'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F },

  /* Variable: dphi_list
   * Referenced by:
   *   '<S5>/2-D Lookup Table'
   *   '<S5>/2-D Lookup Table1'
   *   '<S5>/2-D Lookup Table2'
   *   '<S5>/2-D Lookup Table3'
   *   '<S5>/2-D Lookup Table4'
   *   '<S5>/2-D Lookup Table5'
   *   '<S5>/2-D Lookup Table6'
   *   '<S5>/2-D Lookup Table7'
   *   '<S5>/2-D Lookup Table8'
   */
  { 0.0F, 0.0001F },

  /* Variable: dt_ros_single
   * Referenced by: '<S2>/Gain'
   */
  0.02F,

  /* Variable: kc11
   * Referenced by: '<Root>/Gain3'
   */
  0.3F,

  /* Variable: kc12
   * Referenced by: '<Root>/Gain1'
   */
  1.0F,

  /* Variable: kc2
   * Referenced by: '<Root>/Gain5'
   */
  0.1F,

  /* Variable: steering_ratio
   * Referenced by: '<S2>/Gain1'
   */
  14.8F,

  /* Variable: vx_list
   * Referenced by:
   *   '<S5>/2-D Lookup Table'
   *   '<S5>/2-D Lookup Table1'
   *   '<S5>/2-D Lookup Table2'
   *   '<S5>/2-D Lookup Table3'
   *   '<S5>/2-D Lookup Table4'
   *   '<S5>/2-D Lookup Table5'
   *   '<S5>/2-D Lookup Table6'
   *   '<S5>/2-D Lookup Table7'
   *   '<S5>/2-D Lookup Table8'
   */
  { 10.0F, 10.1F },

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

  /* Computed Parameter: Out1_Y0_n
   * Referenced by: '<S11>/Out1'
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
   * Referenced by: '<S6>/Constant'
   */
  {
    0.0F,                              /* DEst */
    0.0F                               /* DCancel */
  },

  /* Computed Parameter: Delay1_InitialCondition
   * Referenced by: '<S12>/Delay1'
   */
  0.0F,

  /* Computed Parameter: Delay1_InitialCondition_p
   * Referenced by: '<Root>/Delay1'
   */
  0.0F,

  /* Expression: NQ{1}
   * Referenced by: '<Root>/Q1'
   */
  { 0.02F, 0.0F, 0.0F },

  /* Expression: DQ{1}
   * Referenced by: '<Root>/Q1'
   */
  { 1.0F, -1.0F, 0.02F },

  /* Computed Parameter: Q1_InitialStates
   * Referenced by: '<Root>/Q1'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_o
   * Referenced by: '<S5>/Constant'
   */
  0.0F,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<S5>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Delay2_InitialCondition
   * Referenced by: '<S12>/Delay2'
   */
  0.0F,

  /* Computed Parameter: Delay3_InitialCondition
   * Referenced by: '<S12>/Delay3'
   */
  0.0F,

  /* Computed Parameter: Delay4_InitialCondition
   * Referenced by: '<S12>/Delay4'
   */
  0.0F,

  /* Computed Parameter: Delay5_InitialCondition
   * Referenced by: '<S12>/Delay5'
   */
  0.0F,

  /* Computed Parameter: uDLookupTable_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table'
   */
  { 1U, 1U },

  /* Computed Parameter: Delay1_DelayLength
   * Referenced by: '<Root>/Delay1'
   */
  2U,

  /* Computed Parameter: uDLookupTable1_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table1'
   */
  { 1U, 1U },

  /* Computed Parameter: uDLookupTable2_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table2'
   */
  { 1U, 1U },

  /* Computed Parameter: uDLookupTable3_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table3'
   */
  { 1U, 1U },

  /* Computed Parameter: uDLookupTable4_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table4'
   */
  { 1U, 1U },

  /* Computed Parameter: uDLookupTable5_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table5'
   */
  { 1U, 1U },

  /* Computed Parameter: uDLookupTable6_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table6'
   */
  { 1U, 1U },

  /* Computed Parameter: uDLookupTable7_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table7'
   */
  { 1U, 1U },

  /* Computed Parameter: uDLookupTable8_maxIndex
   * Referenced by: '<S5>/2-D Lookup Table8'
   */
  { 1U, 1U },

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S2>/Constant'
   */
  1
};
