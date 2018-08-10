/*
 * DOB_ros.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.183
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Fri Aug 10 15:24:39 2018
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

/* Model step function */
void DOB_ros_step(void)
{
  int32_T denIdx;
  int32_T j;
  SL_Bus_DOB_ros_controller_TrackingInfo b_varargout_2;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd rtb_BusAssignment;
  real32_T rtb_Sum3;
  real32_T rtb_Q1;
  real32_T D1_tmp;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  Inport: '<S8>/In1'
   */
  b_varargout_1 = Sub_DOB_ros_174.getLatestMessage(&b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (b_varargout_1) {
    DOB_ros_B.In1_i = b_varargout_2;
  }

  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/Gain3'
   */
  rtb_Sum3 = DOB_ros_P.kc1 * DOB_ros_B.In1_i.Dtheta + DOB_ros_B.In1_i.Dy;

  /* DiscreteTransferFcn: '<Root>/D1' incorporates:
   *  DiscreteTransferFcn: '<Root>/Q1'
   *  DiscreteTransferFcn: '<Root>/Q1'
   */
  D1_tmp = rtb_Sum3 - DOB_ros_P.Dd[1] * DOB_ros_DW.D1_states[0];
  denIdx = 2;
  for (j = 0; j < 4; j++) {
    D1_tmp -= DOB_ros_P.Dd[denIdx] * DOB_ros_DW.D1_states[j + 1];
    denIdx++;
  }

  D1_tmp /= DOB_ros_P.Dd[0];
  rtb_Q1 = DOB_ros_P.Dn[0] * D1_tmp;
  rtb_Q1 += DOB_ros_P.Dn[1] * DOB_ros_DW.D1_states[0];
  denIdx = 2;
  for (j = 0; j < 4; j++) {
    rtb_Q1 += DOB_ros_P.Dn[denIdx] * DOB_ros_DW.D1_states[j + 1];
    denIdx++;
  }

  /* End of DiscreteTransferFcn: '<Root>/D1' */

  /* DiscreteTransferFcn: '<Root>/Q1' incorporates:
   *  Delay: '<Root>/Delay1'
   *  Sum: '<Root>/Sum4'
   */
  rtb_Q1 = (((DOB_ros_DW.Delay1_DSTATE[0] - rtb_Q1) - DOB_ros_P.Q1_DenCoef[1] *
             DOB_ros_DW.Q1_states[0]) - DOB_ros_P.Q1_DenCoef[2] *
            DOB_ros_DW.Q1_states[1]) / DOB_ros_P.Q1_DenCoef[0];

  /* Sum: '<Root>/subtract3' incorporates:
   *  DiscreteTransferFcn: '<Root>/Q1'
   *  Gain: '<Root>/Gain5'
   */
  rtb_Sum3 = ((DOB_ros_P.Q1_NumCoef[0] * rtb_Q1 + DOB_ros_P.Q1_NumCoef[1] *
               DOB_ros_DW.Q1_states[0]) + DOB_ros_P.Q1_NumCoef[2] *
              DOB_ros_DW.Q1_states[1]) - DOB_ros_P.kc2 * rtb_Sum3;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
  /* Start for MATLABSystem: '<S2>/SourceBlock' incorporates:
   *  Inport: '<S7>/In1'
   */
  b_varargout_1_0 = Sub_DOB_ros_191.getLatestMessage(&DOB_ros_B.b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S7>/Enable'
   */
  if (b_varargout_1_0) {
    DOB_ros_B.In1 = DOB_ros_B.b_varargout_2;
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
    /* BusAssignment: '<S1>/Bus Assignment' incorporates:
     *  Constant: '<S5>/Constant'
     *  Gain: '<S1>/Gain'
     *  Sum: '<S1>/Subtract'
     */
    rtb_BusAssignment = DOB_ros_P.Constant_Value_j;
    rtb_BusAssignment.SteeringWheelAngleCmd = rtb_Sum3;
    rtb_BusAssignment.SteeringWheelAngleVelocity = 1.0F /
      DOB_ros_P.dt_ros_single * (rtb_Sum3 - DOB_ros_B.In1.SteeringWheelAngle);

    /* Outputs for Atomic SubSystem: '<S1>/Publish' */
    /* MATLABSystem: '<S6>/SinkBlock' */
    Pub_DOB_ros_152.publish(&rtb_BusAssignment);

    /* End of Outputs for SubSystem: '<S1>/Publish' */

    /* Outputs for Atomic SubSystem: '<S4>/Publish' */
    /* Start for MATLABSystem: '<S10>/SinkBlock' incorporates:
     *  BusAssignment: '<S4>/Bus Assignment'
     */
    Pub_DOB_ros_158.publish(&DOB_ros_B.In1_i);

    /* End of Outputs for SubSystem: '<S4>/Publish' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */
  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem1' */
  /* End of Outputs for SubSystem: '<Root>/Tracking Received' */

  /* Update for DiscreteTransferFcn: '<Root>/D1' */
  DOB_ros_DW.D1_states[4] = DOB_ros_DW.D1_states[3];
  DOB_ros_DW.D1_states[3] = DOB_ros_DW.D1_states[2];
  DOB_ros_DW.D1_states[2] = DOB_ros_DW.D1_states[1];
  DOB_ros_DW.D1_states[1] = DOB_ros_DW.D1_states[0];
  DOB_ros_DW.D1_states[0] = D1_tmp;

  /* Update for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE[0] = DOB_ros_DW.Delay1_DSTATE[1];
  DOB_ros_DW.Delay1_DSTATE[1] = rtb_Sum3;

  /* Update for DiscreteTransferFcn: '<Root>/Q1' */
  DOB_ros_DW.Q1_states[1] = DOB_ros_DW.Q1_states[0];
  DOB_ros_DW.Q1_states[0] = rtb_Q1;
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
    DOB_ros_DW.obj_a.isInitialized = 0;
    DOB_ros_DW.objisempty_d = true;
    DOB_ros_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 14; i++) {
      tmp_4[i] = tmp_2[i];
    }

    tmp_4[14] = '\x00';
    Sub_DOB_ros_174.createSubscriber(tmp_4, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S2>/SourceBlock' */
    DOB_ros_DW.obj_ax.isInitialized = 0;
    DOB_ros_DW.objisempty_n = true;
    DOB_ros_DW.obj_ax.isInitialized = 1;
    for (i = 0; i < 24; i++) {
      DOB_ros_B.cv0[i] = tmp_1[i];
    }

    DOB_ros_B.cv0[24] = '\x00';
    Sub_DOB_ros_191.createSubscriber(DOB_ros_B.cv0, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S2>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
    /* Start for Atomic SubSystem: '<S1>/Publish' */
    /* Start for MATLABSystem: '<S6>/SinkBlock' */
    DOB_ros_DW.obj_e.isInitialized = 0;
    DOB_ros_DW.objisempty_k = true;
    DOB_ros_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 21; i++) {
      tmp_3[i] = tmp_0[i];
    }

    tmp_3[21] = '\x00';
    Pub_DOB_ros_152.createPublisher(tmp_3, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S6>/SinkBlock' */
    /* End of Start for SubSystem: '<S1>/Publish' */
    /* End of Start for SubSystem: '<Root>/Enabled Subsystem1' */

    /* Start for Enabled SubSystem: '<Root>/Tracking Received' */
    /* Start for Atomic SubSystem: '<S4>/Publish' */
    /* Start for MATLABSystem: '<S10>/SinkBlock' */
    DOB_ros_DW.obj.isInitialized = 0;
    DOB_ros_DW.objisempty = true;
    DOB_ros_DW.obj.isInitialized = 1;
    for (i = 0; i < 24; i++) {
      DOB_ros_B.cv0[i] = tmp[i];
    }

    DOB_ros_B.cv0[24] = '\x00';
    Pub_DOB_ros_158.createPublisher(DOB_ros_B.cv0, DOB_ros_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S10>/SinkBlock' */
    /* End of Start for SubSystem: '<S4>/Publish' */
    /* End of Start for SubSystem: '<Root>/Tracking Received' */
  }

  {
    int32_T i;

    /* InitializeConditions for DiscreteTransferFcn: '<Root>/D1' */
    for (i = 0; i < 5; i++) {
      DOB_ros_DW.D1_states[i] = DOB_ros_P.D1_InitialStates;
    }

    /* End of InitializeConditions for DiscreteTransferFcn: '<Root>/D1' */

    /* InitializeConditions for Delay: '<Root>/Delay1' */
    DOB_ros_DW.Delay1_DSTATE[0] = DOB_ros_P.Delay1_InitialCondition;

    /* InitializeConditions for DiscreteTransferFcn: '<Root>/Q1' */
    DOB_ros_DW.Q1_states[0] = DOB_ros_P.Q1_InitialStates;

    /* InitializeConditions for Delay: '<Root>/Delay1' */
    DOB_ros_DW.Delay1_DSTATE[1] = DOB_ros_P.Delay1_InitialCondition;

    /* InitializeConditions for DiscreteTransferFcn: '<Root>/Q1' */
    DOB_ros_DW.Q1_states[1] = DOB_ros_P.Q1_InitialStates;

    /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
    /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
    /* SystemInitialize for Outport: '<S8>/Out1' */
    DOB_ros_B.In1_i = DOB_ros_P.Out1_Y0_n;

    /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */

    /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
    /* SystemInitialize for Enabled SubSystem: '<S2>/Enabled Subsystem' */
    /* SystemInitialize for Outport: '<S7>/Out1' */
    DOB_ros_B.In1 = DOB_ros_P.Out1_Y0;

    /* End of SystemInitialize for SubSystem: '<S2>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */
  }
}

/* Model terminate function */
void DOB_ros_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' */
  if (DOB_ros_DW.obj_a.isInitialized == 1) {
    DOB_ros_DW.obj_a.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Start for MATLABSystem: '<S2>/SourceBlock' */
  if (DOB_ros_DW.obj_ax.isInitialized == 1) {
    DOB_ros_DW.obj_ax.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S2>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
  /* Terminate for Atomic SubSystem: '<S1>/Publish' */
  /* Terminate for MATLABSystem: '<S6>/SinkBlock' */
  if (DOB_ros_DW.obj_e.isInitialized == 1) {
    DOB_ros_DW.obj_e.isInitialized = 2;
  }

  /* End of Terminate for MATLABSystem: '<S6>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S1>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/Enabled Subsystem1' */

  /* Terminate for Enabled SubSystem: '<Root>/Tracking Received' */
  /* Terminate for Atomic SubSystem: '<S4>/Publish' */
  /* Start for MATLABSystem: '<S10>/SinkBlock' */
  if (DOB_ros_DW.obj.isInitialized == 1) {
    DOB_ros_DW.obj.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S10>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S4>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/Tracking Received' */
}
