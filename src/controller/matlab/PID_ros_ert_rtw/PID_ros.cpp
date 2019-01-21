/*
 * PID_ros.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PID_ros".
 *
 * Model version              : 1.190
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Sun Jan 20 21:43:17 2019
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PID_ros.h"
#include "PID_ros_private.h"
#define PID_ros_MessageQueueLen        (1)

/* Block signals (auto storage) */
B_PID_ros_T PID_ros_B;

/* Block states (auto storage) */
DW_PID_ros_T PID_ros_DW;

/* Real-time model */
RT_MODEL_PID_ros_T PID_ros_M_;
RT_MODEL_PID_ros_T *const PID_ros_M = &PID_ros_M_;

/* Model step function */
void PID_ros_step(void)
{
  SL_Bus_PID_ros_controller_TrackingInfo b_varargout_2;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  SL_Bus_PID_ros_dbw_mkz_msgs_SteeringCmd rtb_BusAssignment;
  real32_T rtb_Gain1_e;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  Inport: '<S8>/In1'
   */
  b_varargout_1 = Sub_PID_ros_174.getLatestMessage(&b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (b_varargout_1) {
    PID_ros_B.In1_i = b_varargout_2;
  }

  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
  /* Start for MATLABSystem: '<S2>/SourceBlock' incorporates:
   *  Inport: '<S7>/In1'
   */
  b_varargout_1_0 = Sub_PID_ros_191.getLatestMessage(&PID_ros_B.b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S7>/Enable'
   */
  if (b_varargout_1_0) {
    PID_ros_B.In1 = PID_ros_B.b_varargout_2;
  }

  /* End of Start for MATLABSystem: '<S2>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S2>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe' */

  /* Outputs for Enabled SubSystem: '<Root>/Tracking Received' incorporates:
   *  EnablePort: '<S4>/Enable'
   */
  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S1>/Enable'
   */
  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' */
  if (b_varargout_1) {
    /* Gain: '<S1>/Gain1' incorporates:
     *  Gain: '<Root>/Gain1'
     *  Gain: '<Root>/Gain3'
     *  Gain: '<Root>/Gain5'
     *  Sum: '<Root>/Sum3'
     */
    rtb_Gain1_e = (PID_ros_P.kc12 * PID_ros_B.In1_i.Dy + PID_ros_P.kc11 *
                   PID_ros_B.In1_i.Dtheta) * -PID_ros_P.kc2 *
      PID_ros_P.steering_ratio;

    /* BusAssignment: '<S1>/Bus Assignment' incorporates:
     *  Constant: '<S1>/Constant'
     *  Constant: '<S5>/Constant'
     *  Gain: '<S1>/Gain'
     *  Sum: '<S1>/Subtract'
     */
    rtb_BusAssignment = PID_ros_P.Constant_Value_j;
    rtb_BusAssignment.SteeringWheelAngleCmd = rtb_Gain1_e;
    rtb_BusAssignment.SteeringWheelAngleVelocity = 1.0F /
      PID_ros_P.dt_ros_single * (rtb_Gain1_e - PID_ros_B.In1.SteeringWheelAngle);
    rtb_BusAssignment.Enable = PID_ros_P.Constant_Value_ij;

    /* Outputs for Atomic SubSystem: '<S1>/Publish' */
    /* Start for MATLABSystem: '<S6>/SinkBlock' */
    Pub_PID_ros_152.publish(&rtb_BusAssignment);

    /* End of Outputs for SubSystem: '<S1>/Publish' */

    /* Outputs for Atomic SubSystem: '<S4>/Publish' */
    /* Start for MATLABSystem: '<S10>/SinkBlock' incorporates:
     *  BusAssignment: '<S4>/Bus Assignment'
     */
    Pub_PID_ros_158.publish(&PID_ros_B.In1_i);

    /* End of Outputs for SubSystem: '<S4>/Publish' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */
  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem1' */
  /* End of Outputs for SubSystem: '<Root>/Tracking Received' */
}

/* Model initialize function */
void PID_ros_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(PID_ros_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &PID_ros_B), 0,
                sizeof(B_PID_ros_T));

  /* states (dwork) */
  (void) memset((void *)&PID_ros_DW, 0,
                sizeof(DW_PID_ros_T));

  {
    static const char_T tmp[24] = { '/', 't', 'r', 'a', 'c', 'k', 'i', 'n', 'g',
      '_', 'e', 'r', 'r', 'o', 'r', '_', 'r', 'e', 'c', 'e', 'i', 'v', 'e', 'd'
    };

    static const char_T tmp_0[21] = { '/', 'v', 'e', 'h', 'i', 'c', 'l', 'e',
      '/', 's', 't', 'e', 'e', 'r', 'i', 'n', 'g', '_', 'c', 'm', 'd' };

    static const char_T tmp_1[24] = { '/', 'v', 'e', 'h', 'i', 'c', 'l', 'e',
      '/', 's', 't', 'e', 'e', 'r', 'i', 'n', 'g', '_', 'r', 'e', 'p', 'o', 'r',
      't' };

    static const char_T tmp_2[14] = { '/', 't', 'r', 'a', 'c', 'k', 'i', 'n',
      'g', '_', 'i', 'n', 'f', 'o' };

    char_T tmp_3[22];
    char_T tmp_4[15];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Subscribe1' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    PID_ros_DW.obj_a.isInitialized = 0;
    PID_ros_DW.objisempty_d = true;
    PID_ros_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 14; i++) {
      tmp_4[i] = tmp_2[i];
    }

    tmp_4[14] = '\x00';
    Sub_PID_ros_174.createSubscriber(tmp_4, PID_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S2>/SourceBlock' */
    PID_ros_DW.obj_ax.isInitialized = 0;
    PID_ros_DW.objisempty_n = true;
    PID_ros_DW.obj_ax.isInitialized = 1;
    for (i = 0; i < 24; i++) {
      PID_ros_B.cv0[i] = tmp_1[i];
    }

    PID_ros_B.cv0[24] = '\x00';
    Sub_PID_ros_191.createSubscriber(PID_ros_B.cv0, PID_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S2>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
    /* Start for Atomic SubSystem: '<S1>/Publish' */
    /* Start for MATLABSystem: '<S6>/SinkBlock' */
    PID_ros_DW.obj_e.isInitialized = 0;
    PID_ros_DW.objisempty_k = true;
    PID_ros_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 21; i++) {
      tmp_3[i] = tmp_0[i];
    }

    tmp_3[21] = '\x00';
    Pub_PID_ros_152.createPublisher(tmp_3, PID_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S6>/SinkBlock' */
    /* End of Start for SubSystem: '<S1>/Publish' */
    /* End of Start for SubSystem: '<Root>/Enabled Subsystem1' */

    /* Start for Enabled SubSystem: '<Root>/Tracking Received' */
    /* Start for Atomic SubSystem: '<S4>/Publish' */
    /* Start for MATLABSystem: '<S10>/SinkBlock' */
    PID_ros_DW.obj.isInitialized = 0;
    PID_ros_DW.objisempty = true;
    PID_ros_DW.obj.isInitialized = 1;
    for (i = 0; i < 24; i++) {
      PID_ros_B.cv0[i] = tmp[i];
    }

    PID_ros_B.cv0[24] = '\x00';
    Pub_PID_ros_158.createPublisher(PID_ros_B.cv0, PID_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S10>/SinkBlock' */
    /* End of Start for SubSystem: '<S4>/Publish' */
    /* End of Start for SubSystem: '<Root>/Tracking Received' */
  }

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S8>/Out1' */
  PID_ros_B.In1_i = PID_ros_P.Out1_Y0_n;

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S2>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S7>/Out1' */
  PID_ros_B.In1 = PID_ros_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S2>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */
}

/* Model terminate function */
void PID_ros_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' */
  if (PID_ros_DW.obj_a.isInitialized == 1) {
    PID_ros_DW.obj_a.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Start for MATLABSystem: '<S2>/SourceBlock' */
  if (PID_ros_DW.obj_ax.isInitialized == 1) {
    PID_ros_DW.obj_ax.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S2>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
  /* Terminate for Atomic SubSystem: '<S1>/Publish' */
  /* Start for MATLABSystem: '<S6>/SinkBlock' */
  if (PID_ros_DW.obj_e.isInitialized == 1) {
    PID_ros_DW.obj_e.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S6>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S1>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/Enabled Subsystem1' */

  /* Terminate for Enabled SubSystem: '<Root>/Tracking Received' */
  /* Terminate for Atomic SubSystem: '<S4>/Publish' */
  /* Start for MATLABSystem: '<S10>/SinkBlock' */
  if (PID_ros_DW.obj.isInitialized == 1) {
    PID_ros_DW.obj.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S10>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S4>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/Tracking Received' */
}
