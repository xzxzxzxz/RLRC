/*
 * DOB_ros.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.233
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Sat Jan 12 12:31:45 2019
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DOB_ros.h"
#include "DOB_ros_private.h"
#define DOB_ros_MessageQueueLen        (1)

/* Block signals (auto storage) */
B_DOB_ros_T DOB_ros_B;

/* Block states (auto storage) */
DW_DOB_ros_T DOB_ros_DW;

/* Real-time model */
RT_MODEL_DOB_ros_T DOB_ros_M_;
RT_MODEL_DOB_ros_T *const DOB_ros_M = &DOB_ros_M_;
real32_T look2_iflf_pbinlxpw(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], uint32_T prevIndex[], const
  uint32_T maxIndex[], uint32_T stride)
{
  real32_T frac;
  uint32_T bpIndices[2];
  real32_T fractions[2];
  real32_T yL_1d;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T found;
  uint32_T bpIdx;

  /* Lookup 2-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex[0U];
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  prevIndex[0U] = bpIdx;
  fractions[0U] = frac;
  bpIndices[0U] = bpIdx;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    bpIdx = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search using Previous Index */
    bpIdx = prevIndex[1U];
    iLeft = 0U;
    iRght = maxIndex[1U];
    found = 0U;
    while (found == 0U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      } else if (u1 < bp1[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      }
    }

    frac = (u1 - bp1[bpIdx]) / (bp1[bpIdx + 1U] - bp1[bpIdx]);
  } else {
    bpIdx = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  prevIndex[1U] = bpIdx;

  /* Interpolation 2-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  iLeft = bpIdx * stride + bpIndices[0U];
  yL_1d = (table[iLeft + 1U] - table[iLeft]) * fractions[0U] + table[iLeft];
  iLeft += stride;
  return (((table[iLeft + 1U] - table[iLeft]) * fractions[0U] + table[iLeft]) -
          yL_1d) * frac + yL_1d;
}

real32_T look2_iflf_binlxpw(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], const uint32_T maxIndex[],
  uint32_T stride)
{
  real32_T frac;
  uint32_T bpIndices[2];
  real32_T fractions[2];
  real32_T yL_1d;
  uint32_T iRght;
  uint32_T bpIdx;
  uint32_T iLeft;

  /* Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  /* Interpolation 2-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_1d = (table[bpIdx + 1U] - table[bpIdx]) * fractions[0U] + table[bpIdx];
  bpIdx += stride;
  return (((table[bpIdx + 1U] - table[bpIdx]) * fractions[0U] + table[bpIdx]) -
          yL_1d) * frac + yL_1d;
}

/* Model step function */
void DOB_ros_step(void)
{
  SL_Bus_DOB_ros_controller_TrackingInfo b_varargout_2;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  SL_Bus_DOB_ros_controller_DobInfo rtb_BusAssignment_o;
  real32_T rtb_uDLookupTable8;
  real32_T rtb_uDLookupTable7;
  real32_T rtb_uDLookupTable5;
  real32_T rtb_Sum1;
  real32_T rtb_Sum4;
  real32_T rtb_Sum3_o;
  real32_T rtb_Q1;
  real32_T Q1_tmp;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S4>/SourceBlock' incorporates:
   *  Inport: '<S11>/In1'
   */
  b_varargout_1 = Sub_DOB_ros_174.getLatestMessage(&b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S11>/Enable'
   */
  if (b_varargout_1) {
    DOB_ros_B.In1_i = b_varargout_2;
  }

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain3'
   */
  rtb_Sum3_o = DOB_ros_P.kc12 * DOB_ros_B.In1_i.Dy + DOB_ros_P.kc11 *
    DOB_ros_B.In1_i.Dtheta;

  /* Lookup_n-D: '<S5>/2-D Lookup Table' */
  rtb_Sum1 = look2_iflf_pbinlxpw(DOB_ros_B.In1_i.Vx, DOB_ros_B.In1_i.Dtheta,
    DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.b0, DOB_ros_DW.m_bpIndex,
    DOB_ros_P.uDLookupTable_maxIndex, 191U);

  /* Sum: '<S12>/Sum1' incorporates:
   *  Product: '<S12>/Product1'
   *  UnitDelay: '<S12>/Delay1'
   */
  rtb_Sum1 = rtb_Sum3_o * rtb_Sum1 + DOB_ros_DW.Delay1_DSTATE;

  /* Sum: '<Root>/Sum4' incorporates:
   *  Delay: '<Root>/Delay1'
   */
  rtb_Sum4 = DOB_ros_DW.Delay1_DSTATE_a[0] - rtb_Sum1;

  /* DiscreteTransferFcn: '<Root>/Q1' */
  Q1_tmp = ((rtb_Sum4 - DOB_ros_P.Q1_DenCoef[1] * DOB_ros_DW.Q1_states[0]) -
            DOB_ros_P.Q1_DenCoef[2] * DOB_ros_DW.Q1_states[1]) /
    DOB_ros_P.Q1_DenCoef[0];

  /* Outputs for Enabled SubSystem: '<Root>/DOB Info' incorporates:
   *  EnablePort: '<S1>/Enable'
   */
  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S4>/SourceBlock' */
  if (b_varargout_1) {
    /* BusAssignment: '<S1>/Bus Assignment' incorporates:
     *  DiscreteTransferFcn: '<Root>/Q1'
     */
    rtb_BusAssignment_o.DEst = rtb_Sum4;
    rtb_BusAssignment_o.DCancel = (DOB_ros_P.Q1_NumCoef[0] * Q1_tmp +
      DOB_ros_P.Q1_NumCoef[1] * DOB_ros_DW.Q1_states[0]) + DOB_ros_P.Q1_NumCoef
      [2] * DOB_ros_DW.Q1_states[1];

    /* Outputs for Atomic SubSystem: '<S1>/Publish' */
    /* MATLABSystem: '<S7>/SinkBlock' */
    Pub_DOB_ros_209.publish(&rtb_BusAssignment_o);

    /* End of Outputs for SubSystem: '<S1>/Publish' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */
  /* End of Outputs for SubSystem: '<Root>/DOB Info' */

  /* Sum: '<Root>/subtract3' incorporates:
   *  Gain: '<Root>/Gain5'
   */
  rtb_Sum4 = 0.0F - DOB_ros_P.kc2 * rtb_Sum3_o;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
  /* MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  Inport: '<S10>/In1'
   */
  b_varargout_1_0 = Sub_DOB_ros_191.getLatestMessage(&DOB_ros_B.b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (b_varargout_1_0) {
    DOB_ros_B.In1 = DOB_ros_B.b_varargout_2;
  }

  /* End of MATLABSystem: '<S3>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe' */

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S4>/SourceBlock' */
  if (b_varargout_1) {
    /* Gain: '<S2>/Gain1' */
    rtb_Q1 = DOB_ros_P.steering_ratio * rtb_Sum4;

    /* BusAssignment: '<S2>/Bus Assignment' incorporates:
     *  Constant: '<S2>/Constant'
     *  Constant: '<S8>/Constant'
     *  Gain: '<S2>/Gain'
     *  Sum: '<S2>/Subtract'
     */
    DOB_ros_B.BusAssignment = DOB_ros_P.Constant_Value_j;
    DOB_ros_B.BusAssignment.SteeringWheelAngleCmd = rtb_Q1;
    DOB_ros_B.BusAssignment.SteeringWheelAngleVelocity = 1.0F /
      DOB_ros_P.dt_ros_single * (rtb_Q1 - DOB_ros_B.In1.SteeringWheelAngle);
    DOB_ros_B.BusAssignment.Enable = DOB_ros_P.Constant_Value_i;

    /* Outputs for Atomic SubSystem: '<S2>/Publish' */
    /* MATLABSystem: '<S9>/SinkBlock' */
    Pub_DOB_ros_152.publish(&DOB_ros_B.BusAssignment);

    /* End of Outputs for SubSystem: '<S2>/Publish' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */
  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem1' */

  /* Lookup_n-D: '<S5>/2-D Lookup Table2' */
  rtb_Q1 = look2_iflf_pbinlxpw(DOB_ros_B.In1_i.Vx, DOB_ros_B.In1_i.Dtheta,
    DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.b1, DOB_ros_DW.m_bpIndex_p,
    DOB_ros_P.uDLookupTable2_maxIndex, 191U);

  /* Lookup_n-D: '<S5>/2-D Lookup Table5' */
  rtb_uDLookupTable5 = look2_iflf_pbinlxpw(DOB_ros_B.In1_i.Vx,
    DOB_ros_B.In1_i.Dtheta, DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.b3,
    DOB_ros_DW.m_bpIndex_j, DOB_ros_P.uDLookupTable5_maxIndex, 191U);

  /* Lookup_n-D: '<S5>/2-D Lookup Table7' */
  rtb_uDLookupTable7 = look2_iflf_pbinlxpw(DOB_ros_B.In1_i.Vx,
    DOB_ros_B.In1_i.Dtheta, DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.a3,
    DOB_ros_DW.m_bpIndex_b, DOB_ros_P.uDLookupTable7_maxIndex, 191U);

  /* Lookup_n-D: '<S5>/2-D Lookup Table8' */
  rtb_uDLookupTable8 = look2_iflf_pbinlxpw(DOB_ros_B.In1_i.Vx,
    DOB_ros_B.In1_i.Dtheta, DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.b5,
    DOB_ros_DW.m_bpIndex_o, DOB_ros_P.uDLookupTable8_maxIndex, 191U);

  /* Update for UnitDelay: '<S12>/Delay1' incorporates:
   *  Lookup_n-D: '<S5>/2-D Lookup Table1'
   *  Product: '<S12>/Product2'
   *  Product: '<S12>/Product3'
   *  Sum: '<S12>/Sum2'
   *  UnitDelay: '<S12>/Delay2'
   */
  DOB_ros_DW.Delay1_DSTATE = (rtb_Sum3_o * rtb_Q1 + DOB_ros_DW.Delay2_DSTATE) -
    rtb_Sum1 * look2_iflf_binlxpw(DOB_ros_B.In1_i.Vx, DOB_ros_B.In1_i.Dtheta,
    DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.a1,
    DOB_ros_P.uDLookupTable1_maxIndex, 191U);

  /* Update for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE_a[0] = DOB_ros_DW.Delay1_DSTATE_a[1];
  DOB_ros_DW.Delay1_DSTATE_a[1] = rtb_Sum4;

  /* Update for DiscreteTransferFcn: '<Root>/Q1' */
  DOB_ros_DW.Q1_states[1] = DOB_ros_DW.Q1_states[0];
  DOB_ros_DW.Q1_states[0] = Q1_tmp;

  /* Update for UnitDelay: '<S12>/Delay2' incorporates:
   *  Lookup_n-D: '<S5>/2-D Lookup Table3'
   *  Lookup_n-D: '<S5>/2-D Lookup Table4'
   *  Product: '<S12>/Product4'
   *  Product: '<S12>/Product5'
   *  Sum: '<S12>/Sum3'
   *  UnitDelay: '<S12>/Delay3'
   */
  DOB_ros_DW.Delay2_DSTATE = (rtb_Sum3_o * look2_iflf_binlxpw(DOB_ros_B.In1_i.Vx,
    DOB_ros_B.In1_i.Dtheta, DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.b2,
    DOB_ros_P.uDLookupTable4_maxIndex, 191U) + DOB_ros_DW.Delay3_DSTATE) -
    rtb_Sum1 * look2_iflf_binlxpw(DOB_ros_B.In1_i.Vx, DOB_ros_B.In1_i.Dtheta,
    DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.a2,
    DOB_ros_P.uDLookupTable3_maxIndex, 191U);

  /* Update for UnitDelay: '<S12>/Delay3' incorporates:
   *  Product: '<S12>/Product6'
   *  Product: '<S12>/Product7'
   *  Sum: '<S12>/Sum4'
   *  UnitDelay: '<S12>/Delay4'
   */
  DOB_ros_DW.Delay3_DSTATE = (rtb_Sum3_o * rtb_uDLookupTable5 +
    DOB_ros_DW.Delay4_DSTATE) - rtb_Sum1 * rtb_uDLookupTable7;

  /* Update for UnitDelay: '<S12>/Delay4' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Lookup_n-D: '<S5>/2-D Lookup Table6'
   *  Product: '<S12>/Product8'
   *  Product: '<S12>/Product9'
   *  Sum: '<S12>/Sum5'
   *  UnitDelay: '<S12>/Delay5'
   */
  DOB_ros_DW.Delay4_DSTATE = (rtb_Sum3_o * look2_iflf_binlxpw(DOB_ros_B.In1_i.Vx,
    DOB_ros_B.In1_i.Dtheta, DOB_ros_P.vx_list, DOB_ros_P.dphi_list, DOB_ros_P.b4,
    DOB_ros_P.uDLookupTable6_maxIndex, 191U) + DOB_ros_DW.Delay5_DSTATE) -
    rtb_Sum1 * DOB_ros_P.Constant1_Value;

  /* Update for UnitDelay: '<S12>/Delay5' incorporates:
   *  Constant: '<S5>/Constant'
   *  Product: '<S12>/Product10'
   *  Product: '<S12>/Product11'
   *  Sum: '<S12>/Sum6'
   */
  DOB_ros_DW.Delay5_DSTATE = rtb_Sum3_o * rtb_uDLookupTable8 - rtb_Sum1 *
    DOB_ros_P.Constant_Value_o;
}

/* Model initialize function */
void DOB_ros_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(DOB_ros_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &DOB_ros_B), 0,
                sizeof(B_DOB_ros_T));

  /* states (dwork) */
  (void) memset((void *)&DOB_ros_DW, 0,
                sizeof(DW_DOB_ros_T));

  {
    static const char_T tmp[21] = { '/', 'v', 'e', 'h', 'i', 'c', 'l', 'e', '/',
      's', 't', 'e', 'e', 'r', 'i', 'n', 'g', '_', 'c', 'm', 'd' };

    static const char_T tmp_0[24] = { '/', 'v', 'e', 'h', 'i', 'c', 'l', 'e',
      '/', 's', 't', 'e', 'e', 'r', 'i', 'n', 'g', '_', 'r', 'e', 'p', 'o', 'r',
      't' };

    static const char_T tmp_1[9] = { '/', 'd', 'o', 'b', '_', 'i', 'n', 'f', 'o'
    };

    static const char_T tmp_2[14] = { '/', 't', 'r', 'a', 'c', 'k', 'i', 'n',
      'g', '_', 'i', 'n', 'f', 'o' };

    char_T tmp_3[22];
    char_T tmp_4[10];
    char_T tmp_5[15];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Subscribe1' */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    DOB_ros_DW.obj_a.isInitialized = 0;
    DOB_ros_DW.objisempty = true;
    DOB_ros_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 14; i++) {
      tmp_5[i] = tmp_2[i];
    }

    tmp_5[14] = '\x00';
    Sub_DOB_ros_174.createSubscriber(tmp_5, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Enabled SubSystem: '<Root>/DOB Info' */
    /* Start for Atomic SubSystem: '<S1>/Publish' */
    /* Start for MATLABSystem: '<S7>/SinkBlock' */
    DOB_ros_DW.obj_f.isInitialized = 0;
    DOB_ros_DW.objisempty_f = true;
    DOB_ros_DW.obj_f.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      tmp_4[i] = tmp_1[i];
    }

    tmp_4[9] = '\x00';
    Pub_DOB_ros_209.createPublisher(tmp_4, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S7>/SinkBlock' */
    /* End of Start for SubSystem: '<S1>/Publish' */
    /* End of Start for SubSystem: '<Root>/DOB Info' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    DOB_ros_DW.obj_ax.isInitialized = 0;
    DOB_ros_DW.objisempty_n = true;
    DOB_ros_DW.obj_ax.isInitialized = 1;
    for (i = 0; i < 24; i++) {
      DOB_ros_B.cv0[i] = tmp_0[i];
    }

    DOB_ros_B.cv0[24] = '\x00';
    Sub_DOB_ros_191.createSubscriber(DOB_ros_B.cv0, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
    /* Start for Atomic SubSystem: '<S2>/Publish' */
    /* Start for MATLABSystem: '<S9>/SinkBlock' */
    DOB_ros_DW.obj.isInitialized = 0;
    DOB_ros_DW.objisempty_k = true;
    DOB_ros_DW.obj.isInitialized = 1;
    for (i = 0; i < 21; i++) {
      tmp_3[i] = tmp[i];
    }

    tmp_3[21] = '\x00';
    Pub_DOB_ros_152.createPublisher(tmp_3, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S9>/SinkBlock' */
    /* End of Start for SubSystem: '<S2>/Publish' */
    /* End of Start for SubSystem: '<Root>/Enabled Subsystem1' */
  }

  /* InitializeConditions for UnitDelay: '<S12>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE = DOB_ros_P.Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE_a[0] = DOB_ros_P.Delay1_InitialCondition_p;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Q1' */
  DOB_ros_DW.Q1_states[0] = DOB_ros_P.Q1_InitialStates;

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE_a[1] = DOB_ros_P.Delay1_InitialCondition_p;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Q1' */
  DOB_ros_DW.Q1_states[1] = DOB_ros_P.Q1_InitialStates;

  /* InitializeConditions for UnitDelay: '<S12>/Delay2' */
  DOB_ros_DW.Delay2_DSTATE = DOB_ros_P.Delay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S12>/Delay3' */
  DOB_ros_DW.Delay3_DSTATE = DOB_ros_P.Delay3_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S12>/Delay4' */
  DOB_ros_DW.Delay4_DSTATE = DOB_ros_P.Delay4_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S12>/Delay5' */
  DOB_ros_DW.Delay5_DSTATE = DOB_ros_P.Delay5_InitialCondition;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S11>/Out1' */
  DOB_ros_B.In1_i = DOB_ros_P.Out1_Y0_n;

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S10>/Out1' */
  DOB_ros_B.In1 = DOB_ros_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */
}

/* Model terminate function */
void DOB_ros_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Terminate for MATLABSystem: '<S4>/SourceBlock' */
  if (DOB_ros_DW.obj_a.isInitialized == 1) {
    DOB_ros_DW.obj_a.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S4>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Enabled SubSystem: '<Root>/DOB Info' */
  /* Terminate for Atomic SubSystem: '<S1>/Publish' */
  /* Terminate for MATLABSystem: '<S7>/SinkBlock' */
  if (DOB_ros_DW.obj_f.isInitialized == 1) {
    DOB_ros_DW.obj_f.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S7>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S1>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/DOB Info' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S3>/SourceBlock' */
  if (DOB_ros_DW.obj_ax.isInitialized == 1) {
    DOB_ros_DW.obj_ax.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S3>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
  /* Terminate for Atomic SubSystem: '<S2>/Publish' */
  /* Terminate for MATLABSystem: '<S9>/SinkBlock' */
  if (DOB_ros_DW.obj.isInitialized == 1) {
    DOB_ros_DW.obj.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S9>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S2>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/Enabled Subsystem1' */
}
