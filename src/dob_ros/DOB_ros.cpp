/*
 * DOB_ros.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.254
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Thu Nov  7 19:06:59 2019
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
uint32_T plook_u32ff_binxp(real32_T u, const real32_T bp[], uint32_T maxIndex,
  real32_T *fraction, uint32_T *prevIndex)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0U]) {
    bpIndex = 0U;
    *fraction = (u - bp[0U]) / (bp[1U] - bp[0U]);
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32f_prevIdx(u, bp, *prevIndex, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = (u - bp[maxIndex - 1U]) / (bp[maxIndex] - bp[maxIndex - 1U]);
  }

  *prevIndex = bpIndex;
  return bpIndex;
}

real32_T intrp4d_fu32fl_pw(const uint32_T bpIndex[], const real32_T frac[],
  const real32_T table[], const uint32_T stride[])
{
  real32_T yL_3d;
  uint32_T offset_3d;
  real32_T yL_2d;
  real32_T yL_1d;
  uint32_T offset_0d;
  uint32_T offset_1d;

  /* Interpolation 4-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  offset_3d = ((bpIndex[3U] * stride[3U] + bpIndex[2U] * stride[2U]) + bpIndex
               [1U] * stride[1U]) + bpIndex[0U];
  yL_1d = (table[offset_3d + 1U] - table[offset_3d]) * frac[0U] +
    table[offset_3d];
  offset_0d = offset_3d + stride[1U];
  yL_2d = (((table[offset_0d + 1U] - table[offset_0d]) * frac[0U] +
            table[offset_0d]) - yL_1d) * frac[1U] + yL_1d;
  offset_1d = offset_3d + stride[2U];
  yL_1d = (table[offset_1d + 1U] - table[offset_1d]) * frac[0U] +
    table[offset_1d];
  offset_0d = offset_1d + stride[1U];
  yL_3d = (((((table[offset_0d + 1U] - table[offset_0d]) * frac[0U] +
              table[offset_0d]) - yL_1d) * frac[1U] + yL_1d) - yL_2d) * frac[2U]
    + yL_2d;
  offset_1d = offset_3d + stride[3U];
  yL_1d = (table[offset_1d + 1U] - table[offset_1d]) * frac[0U] +
    table[offset_1d];
  offset_0d = offset_1d + stride[1U];
  yL_2d = (((table[offset_0d + 1U] - table[offset_0d]) * frac[0U] +
            table[offset_0d]) - yL_1d) * frac[1U] + yL_1d;
  offset_1d += stride[2U];
  yL_1d = (table[offset_1d + 1U] - table[offset_1d]) * frac[0U] +
    table[offset_1d];
  offset_0d = offset_1d + stride[1U];
  return (((((((table[offset_0d + 1U] - table[offset_0d]) * frac[0U] +
               table[offset_0d]) - yL_1d) * frac[1U] + yL_1d) - yL_2d) * frac[2U]
           + yL_2d) - yL_3d) * frac[3U] + yL_3d;
}

uint32_T binsearch_u32f_prevIdx(real32_T u, const real32_T bp[], uint32_T
  startIndex, uint32_T maxIndex)
{
  uint32_T bpIndex;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T found;

  /* Binary Search using Previous Index */
  bpIndex = startIndex;
  iLeft = 0U;
  iRght = maxIndex;
  found = 0U;
  while (found == 0U) {
    if (u < bp[bpIndex]) {
      iRght = bpIndex - 1U;
      bpIndex = (iRght + iLeft) >> 1U;
    } else if (u < bp[bpIndex + 1U]) {
      found = 1U;
    } else {
      iLeft = bpIndex + 1U;
      bpIndex = (iRght + iLeft) >> 1U;
    }
  }

  return bpIndex;
}

/* Model step function */
void DOB_ros_step(void)
{
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  uint32_T bpIdx;
  real32_T rtb_uDLookupTable8;
  real32_T rtb_uDLookupTable7;
  real32_T rtb_uDLookupTable6;
  real32_T rtb_uDLookupTable5;
  real32_T rtb_uDLookupTable4;
  real32_T rtb_uDLookupTable3;
  real32_T rtb_uDLookupTable2;
  real32_T rtb_Sum1_e;
  real32_T rtb_subtract3;
  real32_T rtb_Sum1;
  real32_T rtb_Sum4;
  real32_T rtb_Gain1;
  real32_T rtb_Gain3;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S5>/SourceBlock' incorporates:
   *  Inport: '<S12>/In1'
   */
  b_varargout_1 = Sub_DOB_ros_262.getLatestMessage(&DOB_ros_B.b_varargout_2_m);

  /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  if (b_varargout_1) {
    DOB_ros_B.In1_l = DOB_ros_B.b_varargout_2_m;
  }

  /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

  /* Gain: '<Root>/Gain3' */
  rtb_Gain3 = DOB_ros_P.kc11 * DOB_ros_B.In1_l.Dtheta;

  /* Lookup_n-D: '<S6>/2-D Lookup Table' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex[0U]);
  DOB_ros_B.fractions[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex[1U]);
  DOB_ros_B.fractions[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex[2U]);
  DOB_ros_B.fractions[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex[3U]);
  DOB_ros_B.fractions[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices[3U] = bpIdx;
  rtb_Sum1_e = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices, DOB_ros_B.fractions,
    DOB_ros_P.b0, DOB_ros_P.uDLookupTable_dimSizes);

  /* Sum: '<S13>/Sum1' incorporates:
   *  Product: '<S13>/Product1'
   *  UnitDelay: '<S13>/Delay1'
   */
  rtb_Sum1_e = rtb_Gain3 * rtb_Sum1_e + DOB_ros_DW.Delay1_DSTATE;

  /* Sum: '<Root>/Sum4' incorporates:
   *  Delay: '<Root>/Delay1'
   */
  rtb_Sum4 = DOB_ros_DW.Delay1_DSTATE_a[0] - rtb_Sum1_e;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Product: '<S2>/Product1'
   *  UnitDelay: '<S2>/Delay1'
   */
  rtb_Sum1 = rtb_Sum4 * DOB_ros_B.In1_l.Q + DOB_ros_DW.Delay1_DSTATE_k;

  /* Outputs for Enabled SubSystem: '<Root>/DOB Info' incorporates:
   *  EnablePort: '<S1>/Enable'
   */
  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S5>/SourceBlock' */
  if (b_varargout_1) {
    /* BusAssignment: '<S1>/Bus Assignment' */
    DOB_ros_B.BusAssignment_o.DEst = rtb_Sum4;
    DOB_ros_B.BusAssignment_o.DCancel = rtb_Sum1;

    /* Outputs for Atomic SubSystem: '<S1>/Publish' */
    /* MATLABSystem: '<S8>/SinkBlock' */
    Pub_DOB_ros_209.publish(&DOB_ros_B.BusAssignment_o);

    /* End of Outputs for SubSystem: '<S1>/Publish' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */
  /* End of Outputs for SubSystem: '<Root>/DOB Info' */

  /* Sum: '<Root>/subtract3' incorporates:
   *  Product: '<Root>/Product'
   *  Product: '<Root>/Product1'
   *  Sum: '<Root>/Sum3'
   */
  rtb_subtract3 = rtb_Sum1 - (DOB_ros_B.In1_l.K12 * DOB_ros_B.In1_l.Dy +
    rtb_Gain3) * DOB_ros_B.In1_l.K;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
  /* MATLABSystem: '<S4>/SourceBlock' incorporates:
   *  Inport: '<S11>/In1'
   */
  b_varargout_1_0 = Sub_DOB_ros_191.getLatestMessage(&DOB_ros_B.b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S11>/Enable'
   */
  if (b_varargout_1_0) {
    DOB_ros_B.In1 = DOB_ros_B.b_varargout_2;
  }

  /* End of MATLABSystem: '<S4>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe' */

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S5>/SourceBlock' */
  if (b_varargout_1) {
    /* Gain: '<S3>/Gain1' */
    rtb_Gain1 = DOB_ros_P.steering_ratio * rtb_subtract3;

    /* BusAssignment: '<S3>/Bus Assignment' incorporates:
     *  Constant: '<S3>/Constant'
     *  Constant: '<S9>/Constant'
     *  Gain: '<S3>/Gain'
     *  Sum: '<S3>/Subtract'
     */
    DOB_ros_B.BusAssignment = DOB_ros_P.Constant_Value_j;
    DOB_ros_B.BusAssignment.SteeringWheelAngleCmd = rtb_Gain1;
    DOB_ros_B.BusAssignment.SteeringWheelAngleVelocity = 1.0F /
      DOB_ros_P.dt_ros_single * (rtb_Gain1 - DOB_ros_B.In1.SteeringWheelAngle);
    DOB_ros_B.BusAssignment.Enable = DOB_ros_P.Constant_Value_i;

    /* Outputs for Atomic SubSystem: '<S3>/Publish' */
    /* MATLABSystem: '<S10>/SinkBlock' */
    Pub_DOB_ros_152.publish(&DOB_ros_B.BusAssignment);

    /* End of Outputs for SubSystem: '<S3>/Publish' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */
  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem1' */

  /* Lookup_n-D: '<S6>/2-D Lookup Table1' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_l[0U]);
  DOB_ros_B.fractions_g[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_c[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_l[1U]);
  DOB_ros_B.fractions_g[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_c[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_l[2U]);
  DOB_ros_B.fractions_g[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_c[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_l[3U]);
  DOB_ros_B.fractions_g[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_c[3U] = bpIdx;
  rtb_Gain1 = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices_c, DOB_ros_B.fractions_g,
    DOB_ros_P.a1, DOB_ros_P.uDLookupTable1_dimSizes);

  /* Lookup_n-D: '<S6>/2-D Lookup Table2' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_n[0U]);
  DOB_ros_B.fractions_m[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_k[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_n[1U]);
  DOB_ros_B.fractions_m[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_k[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_n[2U]);
  DOB_ros_B.fractions_m[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_k[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_n[3U]);
  DOB_ros_B.fractions_m[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_k[3U] = bpIdx;
  rtb_uDLookupTable2 = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices_k,
    DOB_ros_B.fractions_m, DOB_ros_P.b1, DOB_ros_P.uDLookupTable2_dimSizes);

  /* Lookup_n-D: '<S6>/2-D Lookup Table3' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_k[0U]);
  DOB_ros_B.fractions_n[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_cx[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_k[1U]);
  DOB_ros_B.fractions_n[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_cx[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_k[2U]);
  DOB_ros_B.fractions_n[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_cx[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_k[3U]);
  DOB_ros_B.fractions_n[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_cx[3U] = bpIdx;
  rtb_uDLookupTable3 = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices_cx,
    DOB_ros_B.fractions_n, DOB_ros_P.a2, DOB_ros_P.uDLookupTable3_dimSizes);

  /* Lookup_n-D: '<S6>/2-D Lookup Table4' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_j[0U]);
  DOB_ros_B.fractions_p[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_b[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_j[1U]);
  DOB_ros_B.fractions_p[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_b[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_j[2U]);
  DOB_ros_B.fractions_p[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_b[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_j[3U]);
  DOB_ros_B.fractions_p[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_b[3U] = bpIdx;
  rtb_uDLookupTable4 = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices_b,
    DOB_ros_B.fractions_p, DOB_ros_P.b2, DOB_ros_P.uDLookupTable4_dimSizes);

  /* Lookup_n-D: '<S6>/2-D Lookup Table5' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_h[0U]);
  DOB_ros_B.fractions_l[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_p[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_h[1U]);
  DOB_ros_B.fractions_l[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_p[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_h[2U]);
  DOB_ros_B.fractions_l[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_p[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_h[3U]);
  DOB_ros_B.fractions_l[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_p[3U] = bpIdx;
  rtb_uDLookupTable5 = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices_p,
    DOB_ros_B.fractions_l, DOB_ros_P.a3, DOB_ros_P.uDLookupTable5_dimSizes);

  /* Lookup_n-D: '<S6>/2-D Lookup Table6' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_j5[0U]);
  DOB_ros_B.fractions_j[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_cv[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_j5[1U]);
  DOB_ros_B.fractions_j[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_cv[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_j5[2U]);
  DOB_ros_B.fractions_j[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_cv[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_j5[3U]);
  DOB_ros_B.fractions_j[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_cv[3U] = bpIdx;
  rtb_uDLookupTable6 = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices_cv,
    DOB_ros_B.fractions_j, DOB_ros_P.b3, DOB_ros_P.uDLookupTable6_dimSizes);

  /* Lookup_n-D: '<S6>/2-D Lookup Table7' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_b[0U]);
  DOB_ros_B.fractions_d[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_f[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_b[1U]);
  DOB_ros_B.fractions_d[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_f[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_b[2U]);
  DOB_ros_B.fractions_d[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_f[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_b[3U]);
  DOB_ros_B.fractions_d[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_f[3U] = bpIdx;
  rtb_uDLookupTable7 = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices_f,
    DOB_ros_B.fractions_d, DOB_ros_P.b4, DOB_ros_P.uDLookupTable7_dimSizes);

  /* Lookup_n-D: '<S6>/2-D Lookup Table8' */
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.V, DOB_ros_P.v_list, 95U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_l0[0U]);
  DOB_ros_B.fractions_gu[0U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_g[0U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dtheta, DOB_ros_P.dphi_list, 20U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_l0[1U]);
  DOB_ros_B.fractions_gu[1U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_g[1U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Kappa, DOB_ros_P.kappa_list, 8U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_l0[2U]);
  DOB_ros_B.fractions_gu[2U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_g[2U] = bpIdx;
  bpIdx = plook_u32ff_binxp(DOB_ros_B.In1_l.Dy, DOB_ros_P.dy_list, 16U,
    &rtb_uDLookupTable8, &DOB_ros_DW.m_bpIndex_l0[3U]);
  DOB_ros_B.fractions_gu[3U] = rtb_uDLookupTable8;
  DOB_ros_B.bpIndices_g[3U] = bpIdx;
  rtb_uDLookupTable8 = intrp4d_fu32fl_pw(DOB_ros_B.bpIndices_g,
    DOB_ros_B.fractions_gu, DOB_ros_P.b5, DOB_ros_P.uDLookupTable8_dimSizes);

  /* Update for UnitDelay: '<S13>/Delay1' incorporates:
   *  Product: '<S13>/Product2'
   *  Product: '<S13>/Product3'
   *  Sum: '<S13>/Sum2'
   *  UnitDelay: '<S13>/Delay2'
   */
  DOB_ros_DW.Delay1_DSTATE = (rtb_Gain3 * rtb_uDLookupTable2 +
    DOB_ros_DW.Delay2_DSTATE_m) - rtb_Sum1_e * rtb_Gain1;

  /* Update for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE_a[0] = DOB_ros_DW.Delay1_DSTATE_a[1];
  DOB_ros_DW.Delay1_DSTATE_a[1] = rtb_subtract3;

  /* Update for UnitDelay: '<S2>/Delay1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Product: '<S2>/Product2'
   *  Product: '<S2>/Product3'
   *  Sum: '<S2>/Sum2'
   *  UnitDelay: '<S2>/Delay2'
   */
  DOB_ros_DW.Delay1_DSTATE_k = (rtb_Sum4 * DOB_ros_P.Constant1_Value +
    DOB_ros_DW.Delay2_DSTATE) - rtb_Sum1 * DOB_ros_P.Constant_Value_o;

  /* Update for UnitDelay: '<S2>/Delay2' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Product: '<S2>/Product4'
   *  Product: '<S2>/Product5'
   *  Sum: '<S2>/Sum3'
   */
  DOB_ros_DW.Delay2_DSTATE = rtb_Sum4 * DOB_ros_P.Constant1_Value - rtb_Sum1 *
    DOB_ros_B.In1_l.Q;

  /* Update for UnitDelay: '<S13>/Delay2' incorporates:
   *  Product: '<S13>/Product4'
   *  Product: '<S13>/Product5'
   *  Sum: '<S13>/Sum3'
   *  UnitDelay: '<S13>/Delay3'
   */
  DOB_ros_DW.Delay2_DSTATE_m = (rtb_Gain3 * rtb_uDLookupTable4 +
    DOB_ros_DW.Delay3_DSTATE) - rtb_Sum1_e * rtb_uDLookupTable3;

  /* Update for UnitDelay: '<S13>/Delay3' incorporates:
   *  Product: '<S13>/Product6'
   *  Product: '<S13>/Product7'
   *  Sum: '<S13>/Sum4'
   *  UnitDelay: '<S13>/Delay4'
   */
  DOB_ros_DW.Delay3_DSTATE = (rtb_Gain3 * rtb_uDLookupTable6 +
    DOB_ros_DW.Delay4_DSTATE) - rtb_Sum1_e * rtb_uDLookupTable5;

  /* Update for UnitDelay: '<S13>/Delay4' incorporates:
   *  Constant: '<S6>/Constant1'
   *  Product: '<S13>/Product8'
   *  Product: '<S13>/Product9'
   *  Sum: '<S13>/Sum5'
   *  UnitDelay: '<S13>/Delay5'
   */
  DOB_ros_DW.Delay4_DSTATE = (rtb_Gain3 * rtb_uDLookupTable7 +
    DOB_ros_DW.Delay5_DSTATE) - rtb_Sum1_e * DOB_ros_P.Constant1_Value_e;

  /* Update for UnitDelay: '<S13>/Delay5' incorporates:
   *  Constant: '<S6>/Constant'
   *  Product: '<S13>/Product10'
   *  Product: '<S13>/Product11'
   *  Sum: '<S13>/Sum6'
   */
  DOB_ros_DW.Delay5_DSTATE = rtb_Gain3 * rtb_uDLookupTable8 - rtb_Sum1_e *
    DOB_ros_P.Constant_Value_o2;
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
    /* Start for MATLABSystem: '<S5>/SourceBlock' */
    DOB_ros_DW.obj_n.isInitialized = 0;
    DOB_ros_DW.objisempty = true;
    DOB_ros_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 14; i++) {
      tmp_5[i] = tmp_2[i];
    }

    tmp_5[14] = '\x00';
    Sub_DOB_ros_262.createSubscriber(tmp_5, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Enabled SubSystem: '<Root>/DOB Info' */
    /* Start for Atomic SubSystem: '<S1>/Publish' */
    /* Start for MATLABSystem: '<S8>/SinkBlock' */
    DOB_ros_DW.obj_f.isInitialized = 0;
    DOB_ros_DW.objisempty_f = true;
    DOB_ros_DW.obj_f.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      tmp_4[i] = tmp_1[i];
    }

    tmp_4[9] = '\x00';
    Pub_DOB_ros_209.createPublisher(tmp_4, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S8>/SinkBlock' */
    /* End of Start for SubSystem: '<S1>/Publish' */
    /* End of Start for SubSystem: '<Root>/DOB Info' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    DOB_ros_DW.obj_a.isInitialized = 0;
    DOB_ros_DW.objisempty_n = true;
    DOB_ros_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 24; i++) {
      DOB_ros_B.cv0[i] = tmp_0[i];
    }

    DOB_ros_B.cv0[24] = '\x00';
    Sub_DOB_ros_191.createSubscriber(DOB_ros_B.cv0, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
    /* Start for Atomic SubSystem: '<S3>/Publish' */
    /* Start for MATLABSystem: '<S10>/SinkBlock' */
    DOB_ros_DW.obj.isInitialized = 0;
    DOB_ros_DW.objisempty_k = true;
    DOB_ros_DW.obj.isInitialized = 1;
    for (i = 0; i < 21; i++) {
      tmp_3[i] = tmp[i];
    }

    tmp_3[21] = '\x00';
    Pub_DOB_ros_152.createPublisher(tmp_3, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S10>/SinkBlock' */
    /* End of Start for SubSystem: '<S3>/Publish' */
    /* End of Start for SubSystem: '<Root>/Enabled Subsystem1' */
  }

  /* InitializeConditions for UnitDelay: '<S13>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE = DOB_ros_P.Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE_a[0] = DOB_ros_P.Delay1_InitialCondition_p;
  DOB_ros_DW.Delay1_DSTATE_a[1] = DOB_ros_P.Delay1_InitialCondition_p;

  /* InitializeConditions for UnitDelay: '<S2>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE_k = DOB_ros_P.Delay1_InitialCondition_n;

  /* InitializeConditions for UnitDelay: '<S2>/Delay2' */
  DOB_ros_DW.Delay2_DSTATE = DOB_ros_P.Delay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S13>/Delay2' */
  DOB_ros_DW.Delay2_DSTATE_m = DOB_ros_P.Delay2_InitialCondition_p;

  /* InitializeConditions for UnitDelay: '<S13>/Delay3' */
  DOB_ros_DW.Delay3_DSTATE = DOB_ros_P.Delay3_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S13>/Delay4' */
  DOB_ros_DW.Delay4_DSTATE = DOB_ros_P.Delay4_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S13>/Delay5' */
  DOB_ros_DW.Delay5_DSTATE = DOB_ros_P.Delay5_InitialCondition;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
  /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S12>/Out1' */
  DOB_ros_B.In1_l = DOB_ros_P.Out1_Y0_k;

  /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S11>/Out1' */
  DOB_ros_B.In1 = DOB_ros_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */
}

/* Model terminate function */
void DOB_ros_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Terminate for MATLABSystem: '<S5>/SourceBlock' */
  if (DOB_ros_DW.obj_n.isInitialized == 1) {
    DOB_ros_DW.obj_n.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S5>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Enabled SubSystem: '<Root>/DOB Info' */
  /* Terminate for Atomic SubSystem: '<S1>/Publish' */
  /* Terminate for MATLABSystem: '<S8>/SinkBlock' */
  if (DOB_ros_DW.obj_f.isInitialized == 1) {
    DOB_ros_DW.obj_f.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S8>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S1>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/DOB Info' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S4>/SourceBlock' */
  if (DOB_ros_DW.obj_a.isInitialized == 1) {
    DOB_ros_DW.obj_a.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S4>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
  /* Terminate for Atomic SubSystem: '<S3>/Publish' */
  /* Terminate for MATLABSystem: '<S10>/SinkBlock' */
  if (DOB_ros_DW.obj.isInitialized == 1) {
    DOB_ros_DW.obj.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S10>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S3>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/Enabled Subsystem1' */
}
