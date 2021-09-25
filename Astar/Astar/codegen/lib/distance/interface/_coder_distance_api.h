/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_distance_api.h
 *
 * Code generation for function '_coder_distance_api'
 *
 */

#ifndef _CODER_DISTANCE_API_H
#define _CODER_DISTANCE_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_distance_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real32_T distance(real32_T x1, real32_T b_y1, real32_T x2, real32_T y2);
extern void distance_api(const mxArray * const prhs[4], int32_T nlhs, const
  mxArray *plhs[1]);
extern void distance_atexit(void);
extern void distance_initialize(void);
extern void distance_terminate(void);
extern void distance_xil_shutdown(void);
extern void distance_xil_terminate(void);

#endif

/* End of code generation (_coder_distance_api.h) */
