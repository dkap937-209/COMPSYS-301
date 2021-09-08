/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * depthFirstFunction_emxutil.h
 *
 * Code generation for function 'depthFirstFunction_emxutil'
 *
 */

#ifndef DEPTHFIRSTFUNCTION_EMXUTIL_H
#define DEPTHFIRSTFUNCTION_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "depthFirstFunction_types.h"

/* Function Declarations */
extern void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray, int oldNumel);
extern void emxFree_real32_T(emxArray_real32_T **pEmxArray);
extern void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (depthFirstFunction_emxutil.h) */
