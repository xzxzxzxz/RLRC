/*
 * DOB_ros.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DOB_ros".
 *
 * Model version              : 1.244
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Sat Jul 27 16:30:35 2019
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_DOB_ros_h_
#define RTW_HEADER_DOB_ros_h_
#include <stddef.h>
#include <string.h>
#ifndef DOB_ros_COMMON_INCLUDES_
# define DOB_ros_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* DOB_ros_COMMON_INCLUDES_ */

#include "DOB_ros_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport In1;/* '<S10>/In1' */
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport b_varargout_2;
  char_T cv0[25];
  SL_Bus_DOB_ros_controller_TrackingInfo In1_i;/* '<S11>/In1' */
  SL_Bus_DOB_ros_controller_TrackingInfo b_varargout_2_m;
  uint32_T bpIndices[4];
  uint32_T bpIndices_c[4];
  uint32_T bpIndices_k[4];
  uint32_T bpIndices_cx[4];
  uint32_T bpIndices_b[4];
  uint32_T bpIndices_p[4];
  uint32_T bpIndices_cv[4];
  uint32_T bpIndices_f[4];
  uint32_T bpIndices_g[4];
  real32_T fractions[4];
  real32_T fractions_g[4];
  real32_T fractions_m[4];
  real32_T fractions_n[4];
  real32_T fractions_p[4];
  real32_T fractions_l[4];
  real32_T fractions_j[4];
  real32_T fractions_d[4];
  real32_T fractions_gu[4];
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd BusAssignment;/* '<S2>/Bus Assignment' */
} B_DOB_ros_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T Delay1_DSTATE;              /* '<S12>/Delay1' */
  real32_T Delay1_DSTATE_a[2];         /* '<Root>/Delay1' */
  real32_T Q1_states[2];               /* '<Root>/Q1' */
  real32_T Delay2_DSTATE;              /* '<S12>/Delay2' */
  real32_T Delay3_DSTATE;              /* '<S12>/Delay3' */
  real32_T Delay4_DSTATE;              /* '<S12>/Delay4' */
  real32_T Delay5_DSTATE;              /* '<S12>/Delay5' */
  real32_T m_bpLambda[4];              /* '<S5>/2-D Lookup Table' */
  real32_T m_bpLambda_m[4];            /* '<S5>/2-D Lookup Table1' */
  real32_T m_bpLambda_b[4];            /* '<S5>/2-D Lookup Table2' */
  real32_T m_bpLambda_l[4];            /* '<S5>/2-D Lookup Table3' */
  real32_T m_bpLambda_ln[4];           /* '<S5>/2-D Lookup Table4' */
  real32_T m_bpLambda_k[4];            /* '<S5>/2-D Lookup Table5' */
  real32_T m_bpLambda_j[4];            /* '<S5>/2-D Lookup Table6' */
  real32_T m_bpLambda_p[4];            /* '<S5>/2-D Lookup Table7' */
  real32_T m_bpLambda_p5[4];           /* '<S5>/2-D Lookup Table8' */
  uint32_T m_bpIndex[4];               /* '<S5>/2-D Lookup Table' */
  uint32_T m_bpIndex_l[4];             /* '<S5>/2-D Lookup Table1' */
  uint32_T m_bpIndex_n[4];             /* '<S5>/2-D Lookup Table2' */
  uint32_T m_bpIndex_k[4];             /* '<S5>/2-D Lookup Table3' */
  uint32_T m_bpIndex_j[4];             /* '<S5>/2-D Lookup Table4' */
  uint32_T m_bpIndex_h[4];             /* '<S5>/2-D Lookup Table5' */
  uint32_T m_bpIndex_j5[4];            /* '<S5>/2-D Lookup Table6' */
  uint32_T m_bpIndex_b[4];             /* '<S5>/2-D Lookup Table7' */
  uint32_T m_bpIndex_l0[4];            /* '<S5>/2-D Lookup Table8' */
  robotics_slros_internal_block_T obj; /* '<S9>/SinkBlock' */
  robotics_slros_internal_block_T obj_f;/* '<S7>/SinkBlock' */
  robotics_slros_internal_blo_k_T obj_a;/* '<S4>/SourceBlock' */
  robotics_slros_internal_blo_k_T obj_ax;/* '<S3>/SourceBlock' */
  boolean_T objisempty;                /* '<S4>/SourceBlock' */
  boolean_T objisempty_n;              /* '<S3>/SourceBlock' */
  boolean_T objisempty_k;              /* '<S9>/SinkBlock' */
  boolean_T objisempty_f;              /* '<S7>/SinkBlock' */
} DW_DOB_ros_T;

/* Parameters (auto storage) */
struct P_DOB_ros_T_ {
  real32_T a1[308448];                 /* Variable: a1
                                        * Referenced by: '<S5>/2-D Lookup Table1'
                                        */
  real32_T a2[308448];                 /* Variable: a2
                                        * Referenced by: '<S5>/2-D Lookup Table3'
                                        */
  real32_T a3[308448];                 /* Variable: a3
                                        * Referenced by: '<S5>/2-D Lookup Table5'
                                        */
  real32_T b0[308448];                 /* Variable: b0
                                        * Referenced by: '<S5>/2-D Lookup Table'
                                        */
  real32_T b1[308448];                 /* Variable: b1
                                        * Referenced by: '<S5>/2-D Lookup Table2'
                                        */
  real32_T b2[308448];                 /* Variable: b2
                                        * Referenced by: '<S5>/2-D Lookup Table4'
                                        */
  real32_T b3[308448];                 /* Variable: b3
                                        * Referenced by: '<S5>/2-D Lookup Table6'
                                        */
  real32_T b4[308448];                 /* Variable: b4
                                        * Referenced by: '<S5>/2-D Lookup Table7'
                                        */
  real32_T b5[308448];                 /* Variable: b5
                                        * Referenced by: '<S5>/2-D Lookup Table8'
                                        */
  real32_T dphi_list[21];              /* Variable: dphi_list
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
  real32_T dt_ros_single;              /* Variable: dt_ros_single
                                        * Referenced by: '<S2>/Gain'
                                        */
  real32_T dy_list[17];                /* Variable: dy_list
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
  real32_T kappa_list[9];              /* Variable: kappa_list
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
  real32_T kc11;                       /* Variable: kc11
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real32_T kc12;                       /* Variable: kc12
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T kc2;                        /* Variable: kc2
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real32_T steering_ratio;             /* Variable: steering_ratio
                                        * Referenced by: '<S2>/Gain1'
                                        */
  real32_T v_list[96];                 /* Variable: v_list
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
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport Out1_Y0;/* Computed Parameter: Out1_Y0
                                                      * Referenced by: '<S10>/Out1'
                                                      */
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringReport Constant_Value;/* Computed Parameter: Constant_Value
                                                             * Referenced by: '<S3>/Constant'
                                                             */
  SL_Bus_DOB_ros_dbw_mkz_msgs_SteeringCmd Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                            * Referenced by: '<S8>/Constant'
                                                            */
  SL_Bus_DOB_ros_controller_TrackingInfo Out1_Y0_n;/* Computed Parameter: Out1_Y0_n
                                                    * Referenced by: '<S11>/Out1'
                                                    */
  SL_Bus_DOB_ros_controller_TrackingInfo Constant_Value_j1;/* Computed Parameter: Constant_Value_j1
                                                            * Referenced by: '<S4>/Constant'
                                                            */
  SL_Bus_DOB_ros_controller_DobInfo Constant_Value_k;/* Computed Parameter: Constant_Value_k
                                                      * Referenced by: '<S6>/Constant'
                                                      */
  real32_T Delay1_InitialCondition;    /* Computed Parameter: Delay1_InitialCondition
                                        * Referenced by: '<S12>/Delay1'
                                        */
  real32_T Delay1_InitialCondition_p;  /* Computed Parameter: Delay1_InitialCondition_p
                                        * Referenced by: '<Root>/Delay1'
                                        */
  real32_T Q1_NumCoef[3];              /* Expression: NQ{1}
                                        * Referenced by: '<Root>/Q1'
                                        */
  real32_T Q1_DenCoef[3];              /* Expression: DQ{1}
                                        * Referenced by: '<Root>/Q1'
                                        */
  real32_T Q1_InitialStates;           /* Computed Parameter: Q1_InitialStates
                                        * Referenced by: '<Root>/Q1'
                                        */
  real32_T Constant_Value_o;           /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S5>/Constant'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real32_T Delay2_InitialCondition;    /* Computed Parameter: Delay2_InitialCondition
                                        * Referenced by: '<S12>/Delay2'
                                        */
  real32_T Delay3_InitialCondition;    /* Computed Parameter: Delay3_InitialCondition
                                        * Referenced by: '<S12>/Delay3'
                                        */
  real32_T Delay4_InitialCondition;    /* Computed Parameter: Delay4_InitialCondition
                                        * Referenced by: '<S12>/Delay4'
                                        */
  real32_T Delay5_InitialCondition;    /* Computed Parameter: Delay5_InitialCondition
                                        * Referenced by: '<S12>/Delay5'
                                        */
  uint32_T uDLookupTable_maxIndex[4];  /* Computed Parameter: uDLookupTable_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table'
                                        */
  uint32_T uDLookupTable_dimSizes[4];  /* Computed Parameter: uDLookupTable_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table'
                                        */
  uint32_T Delay1_DelayLength;         /* Computed Parameter: Delay1_DelayLength
                                        * Referenced by: '<Root>/Delay1'
                                        */
  uint32_T uDLookupTable1_maxIndex[4]; /* Computed Parameter: uDLookupTable1_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table1'
                                        */
  uint32_T uDLookupTable1_dimSizes[4]; /* Computed Parameter: uDLookupTable1_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table1'
                                        */
  uint32_T uDLookupTable2_maxIndex[4]; /* Computed Parameter: uDLookupTable2_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table2'
                                        */
  uint32_T uDLookupTable2_dimSizes[4]; /* Computed Parameter: uDLookupTable2_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table2'
                                        */
  uint32_T uDLookupTable3_maxIndex[4]; /* Computed Parameter: uDLookupTable3_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table3'
                                        */
  uint32_T uDLookupTable3_dimSizes[4]; /* Computed Parameter: uDLookupTable3_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table3'
                                        */
  uint32_T uDLookupTable4_maxIndex[4]; /* Computed Parameter: uDLookupTable4_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table4'
                                        */
  uint32_T uDLookupTable4_dimSizes[4]; /* Computed Parameter: uDLookupTable4_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table4'
                                        */
  uint32_T uDLookupTable5_maxIndex[4]; /* Computed Parameter: uDLookupTable5_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table5'
                                        */
  uint32_T uDLookupTable5_dimSizes[4]; /* Computed Parameter: uDLookupTable5_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table5'
                                        */
  uint32_T uDLookupTable6_maxIndex[4]; /* Computed Parameter: uDLookupTable6_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table6'
                                        */
  uint32_T uDLookupTable6_dimSizes[4]; /* Computed Parameter: uDLookupTable6_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table6'
                                        */
  uint32_T uDLookupTable7_maxIndex[4]; /* Computed Parameter: uDLookupTable7_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table7'
                                        */
  uint32_T uDLookupTable7_dimSizes[4]; /* Computed Parameter: uDLookupTable7_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table7'
                                        */
  uint32_T uDLookupTable8_maxIndex[4]; /* Computed Parameter: uDLookupTable8_maxIndex
                                        * Referenced by: '<S5>/2-D Lookup Table8'
                                        */
  uint32_T uDLookupTable8_dimSizes[4]; /* Computed Parameter: uDLookupTable8_dimSizes
                                        * Referenced by: '<S5>/2-D Lookup Table8'
                                        */
  boolean_T Constant_Value_i;          /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S2>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_DOB_ros_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_DOB_ros_T DOB_ros_P;

#ifdef __cplusplus

}
#endif

/* Block signals (auto storage) */
extern B_DOB_ros_T DOB_ros_B;

/* Block states (auto storage) */
extern DW_DOB_ros_T DOB_ros_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void DOB_ros_initialize(void);
  extern void DOB_ros_step(void);
  extern void DOB_ros_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_DOB_ros_T *const DOB_ros_M;

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'DOB_ros'
 * '<S1>'   : 'DOB_ros/DOB Info'
 * '<S2>'   : 'DOB_ros/Enabled Subsystem1'
 * '<S3>'   : 'DOB_ros/Subscribe'
 * '<S4>'   : 'DOB_ros/Subscribe1'
 * '<S5>'   : 'DOB_ros/Subsystem'
 * '<S6>'   : 'DOB_ros/DOB Info/Blank Message'
 * '<S7>'   : 'DOB_ros/DOB Info/Publish'
 * '<S8>'   : 'DOB_ros/Enabled Subsystem1/Blank Message'
 * '<S9>'   : 'DOB_ros/Enabled Subsystem1/Publish'
 * '<S10>'  : 'DOB_ros/Subscribe/Enabled Subsystem'
 * '<S11>'  : 'DOB_ros/Subscribe1/Enabled Subsystem'
 * '<S12>'  : 'DOB_ros/Subsystem/Discrete Varying Transfer Function'
 */
#endif                                 /* RTW_HEADER_DOB_ros_h_ */
