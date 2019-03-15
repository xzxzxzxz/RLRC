/*
 * DOB_ros_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.244
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Fri Mar 15 13:42:33 2019
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_DOB_ros_private_h_
#define RTW_HEADER_DOB_ros_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

extern uint32_T plook_u32ff_binxp(real32_T u, const real32_T bp[], uint32_T
  maxIndex, real32_T *fraction, uint32_T *prevIndex);
extern real32_T intrp4d_fu32fl_pw(const uint32_T bpIndex[], const real32_T frac[],
  const real32_T table[], const uint32_T stride[]);
extern uint32_T binsearch_u32f_prevIdx(real32_T u, const real32_T bp[], uint32_T
  startIndex, uint32_T maxIndex);

#endif                                 /* RTW_HEADER_DOB_ros_private_h_ */
