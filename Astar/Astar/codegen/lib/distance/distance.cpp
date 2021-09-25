/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * distance.cpp
 *
 * Code generation for function 'distance'
 *
 */

/* Include files */
#include <cmath>
#include "distance.h"

/* Function Definitions */
float distance(float x1, float b_y1, float x2, float y2)
{
  float a;
  float b_a;

  /* This function calculates the distance between any two cartesian  */
  /* coordinates. */
  /*    Copyright 2009-2010 The MathWorks, Inc. */
  a = x1 - x2;
  b_a = b_y1 - y2;
  return std::sqrt(a * a + b_a * b_a);
}

/* End of code generation (distance.cpp) */
