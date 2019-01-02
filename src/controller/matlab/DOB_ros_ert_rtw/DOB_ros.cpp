/*
 * DOB_ros.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.207
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Tue Jan  1 19:50:07 2019
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
  SL_Bus_DOB_ros_controller_TrackingInfo b_varargout_2;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd rtb_BusAssignment;
  SL_Bus_DOB_ros_controller_DobInfo rtb_BusAssignment_o;
  real32_T rtb_Sum4;
  real32_T rtb_Sum3;
  real32_T rtb_Q1;
  real32_T rtb_D1;
  real32_T D1_tmp;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Start for MATLABSystem: '<S4>/SourceBlock' incorporates:
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
  rtb_Sum3 = DOB_ros_P.kc12 * DOB_ros_B.In1_i.Dy + DOB_ros_P.kc11 *
    DOB_ros_B.In1_i.Dtheta;

  /* DiscreteTransferFcn: '<Root>/D1' */
  D1_tmp = ((((rtb_Sum3 - DOB_ros_P.Dd[1] * DOB_ros_DW.D1_states[0]) -
              DOB_ros_P.Dd[2] * DOB_ros_DW.D1_states[1]) - DOB_ros_P.Dd[3] *
             DOB_ros_DW.D1_states[2]) - DOB_ros_P.Dd[4] * DOB_ros_DW.D1_states[3])
    / DOB_ros_P.Dd[0];

  /* Sum: '<Root>/Sum4' incorporates:
   *  Delay: '<Root>/Delay1'
   *  DiscreteTransferFcn: '<Root>/D1'
   */
  rtb_Sum4 = DOB_ros_DW.Delay1_DSTATE[0] - ((((DOB_ros_P.Dn[0] * D1_tmp +
    DOB_ros_P.Dn[1] * DOB_ros_DW.D1_states[0]) + DOB_ros_P.Dn[2] *
    DOB_ros_DW.D1_states[1]) + DOB_ros_P.Dn[3] * DOB_ros_DW.D1_states[2]) +
    DOB_ros_P.Dn[4] * DOB_ros_DW.D1_states[3]);

  /* DiscreteTransferFcn: '<Root>/Q1' */
  rtb_D1 = ((rtb_Sum4 - DOB_ros_P.Q1_DenCoef[1] * DOB_ros_DW.Q1_states[0]) -
            DOB_ros_P.Q1_DenCoef[2] * DOB_ros_DW.Q1_states[1]) /
    DOB_ros_P.Q1_DenCoef[0];
  rtb_Q1 = (DOB_ros_P.Q1_NumCoef[0] * rtb_D1 + DOB_ros_P.Q1_NumCoef[1] *
            DOB_ros_DW.Q1_states[0]) + DOB_ros_P.Q1_NumCoef[2] *
    DOB_ros_DW.Q1_states[1];

  /* Outputs for Enabled SubSystem: '<Root>/DOB Info' incorporates:
   *  EnablePort: '<S1>/Enable'
   */
  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Start for MATLABSystem: '<S4>/SourceBlock' */
  if (b_varargout_1) {
    /* BusAssignment: '<S1>/Bus Assignment' */
    rtb_BusAssignment_o.DEst = rtb_Sum4;
    rtb_BusAssignment_o.DCancel = rtb_Q1;

    /* Outputs for Atomic SubSystem: '<S1>/Publish' */
    /* Start for MATLABSystem: '<S7>/SinkBlock' */
    Pub_DOB_ros_209.publish(&rtb_BusAssignment_o);

    /* End of Outputs for SubSystem: '<S1>/Publish' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */
  /* End of Outputs for SubSystem: '<Root>/DOB Info' */

  /* Sum: '<Root>/subtract3' incorporates:
   *  Gain: '<Root>/Gain5'
   */
  rtb_Sum3 = rtb_Q1 - DOB_ros_P.kc2 * rtb_Sum3;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  Inport: '<S10>/In1'
   */
  b_varargout_1_0 = Sub_DOB_ros_191.getLatestMessage(&DOB_ros_B.b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (b_varargout_1_0) {
    DOB_ros_B.In1 = DOB_ros_B.b_varargout_2;
  }

  /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe' */

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Start for MATLABSystem: '<S4>/SourceBlock' */
  if (b_varargout_1) {
    /* Gain: '<S2>/Gain1' */
    rtb_Q1 = DOB_ros_P.steering_ratio * rtb_Sum3;

    /* BusAssignment: '<S2>/Bus Assignment' incorporates:
     *  Constant: '<S2>/Constant'
     *  Constant: '<S8>/Constant'
     *  Gain: '<S2>/Gain'
     *  Sum: '<S2>/Subtract'
     */
    rtb_BusAssignment = DOB_ros_P.Constant_Value_j;
    rtb_BusAssignment.SteeringWheelAngleCmd = rtb_Q1;
    rtb_BusAssignment.SteeringWheelAngleVelocity = 1.0F /
      DOB_ros_P.dt_ros_single * (rtb_Q1 - DOB_ros_B.In1.SteeringWheelAngle);
    rtb_BusAssignment.Enable = DOB_ros_P.Constant_Value_i;

    /* Outputs for Atomic SubSystem: '<S2>/Publish' */
    /* Start for MATLABSystem: '<S9>/SinkBlock' */
    Pub_DOB_ros_152.publish(&rtb_BusAssignment);

    /* End of Outputs for SubSystem: '<S2>/Publish' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */
  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem1' */

  /* Update for DiscreteTransferFcn: '<Root>/D1' */
  DOB_ros_DW.D1_states[3] = DOB_ros_DW.D1_states[2];
  DOB_ros_DW.D1_states[2] = DOB_ros_DW.D1_states[1];
  DOB_ros_DW.D1_states[1] = DOB_ros_DW.D1_states[0];
  DOB_ros_DW.D1_states[0] = D1_tmp;

  /* Update for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE[0] = DOB_ros_DW.Delay1_DSTATE[1];
  DOB_ros_DW.Delay1_DSTATE[1] = rtb_Sum3;

  /* Update for DiscreteTransferFcn: '<Root>/Q1' */
  DOB_ros_DW.Q1_states[1] = DOB_ros_DW.Q1_states[0];
  DOB_ros_DW.Q1_states[0] = rtb_D1;
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

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/D1' */
  DOB_ros_DW.D1_states[0] = DOB_ros_P.D1_InitialStates;
  DOB_ros_DW.D1_states[1] = DOB_ros_P.D1_InitialStates;
  DOB_ros_DW.D1_states[2] = DOB_ros_P.D1_InitialStates;
  DOB_ros_DW.D1_states[3] = DOB_ros_P.D1_InitialStates;

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE[0] = DOB_ros_P.Delay1_InitialCondition;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Q1' */
  DOB_ros_DW.Q1_states[0] = DOB_ros_P.Q1_InitialStates;

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  DOB_ros_DW.Delay1_DSTATE[1] = DOB_ros_P.Delay1_InitialCondition;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Q1' */
  DOB_ros_DW.Q1_states[1] = DOB_ros_P.Q1_InitialStates;

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
  /* Start for MATLABSystem: '<S4>/SourceBlock' */
  if (DOB_ros_DW.obj_a.isInitialized == 1) {
    DOB_ros_DW.obj_a.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Enabled SubSystem: '<Root>/DOB Info' */
  /* Terminate for Atomic SubSystem: '<S1>/Publish' */
  /* Start for MATLABSystem: '<S7>/SinkBlock' */
  if (DOB_ros_DW.obj_f.isInitialized == 1) {
    DOB_ros_DW.obj_f.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S7>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S1>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/DOB Info' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' */
  if (DOB_ros_DW.obj_ax.isInitialized == 1) {
    DOB_ros_DW.obj_ax.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Enabled SubSystem: '<Root>/Enabled Subsystem1' */
  /* Terminate for Atomic SubSystem: '<S2>/Publish' */
  /* Start for MATLABSystem: '<S9>/SinkBlock' */
  if (DOB_ros_DW.obj.isInitialized == 1) {
    DOB_ros_DW.obj.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S9>/SinkBlock' */
  /* End of Terminate for SubSystem: '<S2>/Publish' */
  /* End of Terminate for SubSystem: '<Root>/Enabled Subsystem1' */
}
