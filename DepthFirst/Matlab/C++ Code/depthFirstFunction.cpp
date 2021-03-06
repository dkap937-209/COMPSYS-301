/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * depthFirstFunction.cpp
 *
 * Code generation for function 'depthFirstFunction'
 *
 */

/* Include files */
#include "depthFirstFunction.h"
#include "depthFirstFunction_emxutil.h"
#include <stdio.h>

/* Function Declarations */
static boolean_T b_depthFirstFunction(emxArray_real32_T *maze, float startingRow,
  float startingCol, float endRow, float endCol);
static boolean_T c_depthFirstFunction(emxArray_real32_T *maze, float startingRow,
  float startingCol, float endRow, float endCol);

/* Function Definitions */
static boolean_T b_depthFirstFunction(emxArray_real32_T *maze, float startingRow,
  float startingCol, float endRow, float endCol)
{
  boolean_T finished;
  unsigned int mazeSize_idx_0;
  unsigned int mazeSize_idx_1;
  boolean_T east;
  boolean_T west;
  boolean_T south;
  int directionsToMoveIn;
  emxArray_real32_T *b_maze;
  int loop_ub;
  finished = false;
  mazeSize_idx_0 = static_cast<unsigned int>(maze->size[0]);
  mazeSize_idx_1 = static_cast<unsigned int>(maze->size[1]);

  /* Check in each direction we can go */
  east = false;
  west = false;
  south = false;
  directionsToMoveIn = 0;

  /* North */
  if (startingRow - 1.0F < 0.0F) {
    abort();
  }

  /* East */
  if ((static_cast<double>((startingCol + 1.0F)) <= mazeSize_idx_1) &&
      (maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
         int>((startingCol + 1.0F)) - 1)) - 1] == 0.0F)) {
    east = true;
    directionsToMoveIn = 1;
  }

  /* South */
  if ((static_cast<double>((startingRow + 1.0F)) <= mazeSize_idx_0) &&
      (maze->data[(static_cast<int>((startingRow + 1.0F)) + maze->size[0] *
                   (static_cast<int>(startingCol) - 1)) - 1] == 0.0F)) {
    south = true;
    directionsToMoveIn++;
  }

  /* West  */
  if ((startingCol - 1.0F > 0.0F) && (maze->data[(static_cast<int>(startingRow)
        + maze->size[0] * (static_cast<int>((startingCol - 1.0F)) - 1)) - 1] ==
       0.0F)) {
    west = true;
    directionsToMoveIn++;
  }

  /* If we can only move in one direction */
  emxInit_real32_T(&b_maze, 2);
  if ((startingRow == endRow) && (startingCol == endCol)) {
    printf("%s\n", "Finished");
    fflush(stdout);
    finished = true;
  } else if (directionsToMoveIn == 1) {
    if (east) {
      printf("%s\n", "move east");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow, startingCol + 1.0F,
        endRow, endCol);
    }

    if (south && (!finished)) {
      printf("%s\n", "move south");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow + 1.0F, startingCol,
        endRow, endCol);
    }

    if (west && (!finished)) {
      printf("%s\n", "move east");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow, startingCol - 1.0F,
        endRow, endCol);
    }

    /* If we can move in multiple directions     */
  } else if (directionsToMoveIn > 1) {
    maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<int>
      (startingCol) - 1)) - 1] = -1.0F;
    if (east) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = c_depthFirstFunction(b_maze, startingRow, startingCol + 1.0F,
        endRow, endCol);
    }

    if (south && (!finished)) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = c_depthFirstFunction(b_maze, startingRow + 1.0F, startingCol,
        endRow, endCol);
    }

    if (west && (!finished)) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = c_depthFirstFunction(b_maze, startingRow, startingCol - 1.0F,
        endRow, endCol);
    }
  } else {
    printf("%s\n", "Can\'t move");
    fflush(stdout);
  }

  emxFree_real32_T(&b_maze);
  return finished;
}

static boolean_T c_depthFirstFunction(emxArray_real32_T *maze, float startingRow,
  float startingCol, float endRow, float endCol)
{
  boolean_T finished;
  unsigned int mazeSize_idx_0;
  unsigned int mazeSize_idx_1;
  boolean_T east;
  boolean_T west;
  boolean_T south;
  int directionsToMoveIn;
  emxArray_real32_T *b_maze;
  int loop_ub;
  finished = false;
  mazeSize_idx_0 = static_cast<unsigned int>(maze->size[0]);
  mazeSize_idx_1 = static_cast<unsigned int>(maze->size[1]);

  /* Check in each direction we can go */
  east = false;
  west = false;
  south = false;
  directionsToMoveIn = 0;

  /* North */
  if (startingRow - 1.0F < 0.0F) {
    abort();
  }

  /* East */
  if ((static_cast<double>((startingCol + 1.0F)) <= mazeSize_idx_1) &&
      (maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
         int>((startingCol + 1.0F)) - 1)) - 1] == 0.0F)) {
    east = true;
    directionsToMoveIn = 1;
  }

  /* South */
  if ((static_cast<double>((startingRow + 1.0F)) <= mazeSize_idx_0) &&
      (maze->data[(static_cast<int>((startingRow + 1.0F)) + maze->size[0] *
                   (static_cast<int>(startingCol) - 1)) - 1] == 0.0F)) {
    south = true;
    directionsToMoveIn++;
  }

  /* West  */
  if ((startingCol - 1.0F > 0.0F) && (maze->data[(static_cast<int>(startingRow)
        + maze->size[0] * (static_cast<int>((startingCol - 1.0F)) - 1)) - 1] ==
       0.0F)) {
    west = true;
    directionsToMoveIn++;
  }

  /* If we can only move in one direction */
  emxInit_real32_T(&b_maze, 2);
  if ((startingRow == endRow) && (startingCol == endCol)) {
    printf("%s\n", "Finished");
    fflush(stdout);
    finished = true;
  } else if (directionsToMoveIn == 1) {
    if (east) {
      printf("%s\n", "move east");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow, startingCol + 1.0F,
        endRow, endCol);
    }

    if (south && (!finished)) {
      printf("%s\n", "move south");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow + 1.0F, startingCol,
        endRow, endCol);
    }

    if (west && (!finished)) {
      printf("%s\n", "move east");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow, startingCol - 1.0F,
        endRow, endCol);
    }

    /* If we can move in multiple directions     */
  } else if (directionsToMoveIn > 1) {
    maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<int>
      (startingCol) - 1)) - 1] = -1.0F;
    if (east) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = c_depthFirstFunction(b_maze, startingRow, startingCol + 1.0F,
        endRow, endCol);
    }

    if (south && (!finished)) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = c_depthFirstFunction(b_maze, startingRow + 1.0F, startingCol,
        endRow, endCol);
    }

    if (west && (!finished)) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = c_depthFirstFunction(b_maze, startingRow, startingCol - 1.0F,
        endRow, endCol);
    }
  } else {
    printf("%s\n", "Can\'t move");
    fflush(stdout);
  }

  emxFree_real32_T(&b_maze);
  return finished;
}

boolean_T depthFirstFunction(emxArray_real32_T *maze, float startingRow, float
  startingCol, float endRow, float endCol, float intersectionRow, float
  intersectionCol)
{
  boolean_T finished;
  unsigned int mazeSize_idx_0;
  unsigned int mazeSize_idx_1;
  boolean_T east;
  boolean_T west;
  boolean_T south;
  int directionsToMoveIn;
  emxArray_real32_T *b_maze;
  emxArray_real32_T *c_maze;
  int loop_ub;
  boolean_T b_finished;
  finished = false;
  mazeSize_idx_0 = static_cast<unsigned int>(maze->size[0]);
  mazeSize_idx_1 = static_cast<unsigned int>(maze->size[1]);

  /* Check in each direction we can go */
  east = false;
  west = false;
  south = false;
  directionsToMoveIn = 0;

  /* North */
  if (startingRow - 1.0F < 0.0F) {
    abort();
  }

  /* East */
  if ((static_cast<double>((startingCol + 1.0F)) <= mazeSize_idx_1) &&
      (maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
         int>((startingCol + 1.0F)) - 1)) - 1] == 0.0F)) {
    east = true;
    directionsToMoveIn = 1;
  }

  /* South */
  if ((static_cast<double>((startingRow + 1.0F)) <= mazeSize_idx_0) &&
      (maze->data[(static_cast<int>((startingRow + 1.0F)) + maze->size[0] *
                   (static_cast<int>(startingCol) - 1)) - 1] == 0.0F)) {
    south = true;
    directionsToMoveIn++;
  }

  /* West  */
  if ((startingCol - 1.0F > 0.0F) && (maze->data[(static_cast<int>(startingRow)
        + maze->size[0] * (static_cast<int>((startingCol - 1.0F)) - 1)) - 1] ==
       0.0F)) {
    west = true;
    directionsToMoveIn++;
  }

  /* If we can only move in one direction */
  emxInit_real32_T(&b_maze, 2);
  emxInit_real32_T(&c_maze, 2);
  if ((startingRow == endRow) && (startingCol == endCol)) {
    printf("%s\n", "Finished");
    fflush(stdout);
    finished = true;
  } else if (directionsToMoveIn == 1) {
    if (east) {
      printf("%s\n", "move east");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow, startingCol + 1.0F,
        endRow, endCol);
    }

    if (south && (!finished)) {
      printf("%s\n", "move south");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow + 1.0F, startingCol,
        endRow, endCol);
    }

    if (west && (!finished)) {
      printf("%s\n", "move east");
      fflush(stdout);
      maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<
        int>(startingCol) - 1)) - 1] = -1.0F;
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = b_depthFirstFunction(b_maze, startingRow, startingCol - 1.0F,
        endRow, endCol);
    }

    /* If we can move in multiple directions     */
  } else if (directionsToMoveIn > 1) {
    maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<int>
      (startingCol) - 1)) - 1] = -1.0F;
    if (east) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = depthFirstFunction(b_maze, startingRow, startingCol + 1.0F,
        endRow, endCol, intersectionRow, intersectionCol);
    }

    if (south && (!finished)) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = depthFirstFunction(b_maze, startingRow + 1.0F, startingCol,
        endRow, endCol, intersectionRow, intersectionCol);
    }

    if (west && (!finished)) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      finished = depthFirstFunction(b_maze, startingRow, startingCol - 1.0F,
        endRow, endCol, intersectionRow, intersectionCol);
    }
  } else {
    maze->data[(static_cast<int>(startingRow) + maze->size[0] * (static_cast<int>
      (startingCol) - 1)) - 1] = -1.0F;
    printf("%s\n", "Can\'t move");
    fflush(stdout);
    if ((intersectionRow != 0.0F) && (intersectionCol != 0.0F)) {
      directionsToMoveIn = b_maze->size[0] * b_maze->size[1];
      b_maze->size[0] = maze->size[0];
      b_maze->size[1] = maze->size[1];
      emxEnsureCapacity_real32_T(b_maze, directionsToMoveIn);
      loop_ub = maze->size[0] * maze->size[1];
      for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
           directionsToMoveIn++) {
        b_maze->data[directionsToMoveIn] = maze->data[directionsToMoveIn];
      }

      b_finished = false;
      mazeSize_idx_0 = static_cast<unsigned int>(maze->size[0]);
      mazeSize_idx_1 = static_cast<unsigned int>(maze->size[1]);

      /* Check in each direction we can go */
      east = false;
      west = false;
      south = false;
      directionsToMoveIn = 0;

      /* North */
      if (intersectionRow - 1.0F < 0.0F) {
        abort();
      }

      /* East */
      if ((static_cast<double>((intersectionCol + 1.0F)) <= mazeSize_idx_1) &&
          (maze->data[(static_cast<int>(intersectionRow) + maze->size[0] *
                       (static_cast<int>((intersectionCol + 1.0F)) - 1)) - 1] ==
           0.0F)) {
        east = true;
        directionsToMoveIn = 1;
      }

      /* South */
      if ((static_cast<double>((intersectionRow + 1.0F)) <= mazeSize_idx_0) &&
          (maze->data[(static_cast<int>((intersectionRow + 1.0F)) + maze->size[0]
                       * (static_cast<int>(intersectionCol) - 1)) - 1] == 0.0F))
      {
        south = true;
        directionsToMoveIn++;
      }

      /* West  */
      if ((intersectionCol - 1.0F > 0.0F) && (maze->data[(static_cast<int>
            (intersectionRow) + maze->size[0] * (static_cast<int>
             ((intersectionCol - 1.0F)) - 1)) - 1] == 0.0F)) {
        west = true;
        directionsToMoveIn++;
      }

      /* If we can only move in one direction */
      if ((intersectionRow == endRow) && (intersectionCol == endCol)) {
        printf("%s\n", "Finished");
        fflush(stdout);
      } else if (directionsToMoveIn == 1) {
        if (east) {
          printf("%s\n", "move east");
          fflush(stdout);
          b_maze->data[(static_cast<int>(intersectionRow) + b_maze->size[0] *
                        (static_cast<int>(intersectionCol) - 1)) - 1] = -1.0F;
          directionsToMoveIn = c_maze->size[0] * c_maze->size[1];
          c_maze->size[0] = b_maze->size[0];
          c_maze->size[1] = b_maze->size[1];
          emxEnsureCapacity_real32_T(c_maze, directionsToMoveIn);
          loop_ub = b_maze->size[0] * b_maze->size[1];
          for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
               directionsToMoveIn++) {
            c_maze->data[directionsToMoveIn] = b_maze->data[directionsToMoveIn];
          }

          b_finished = b_depthFirstFunction(c_maze, intersectionRow,
            intersectionCol + 1.0F, endRow, endCol);
        }

        if (south && (!b_finished)) {
          printf("%s\n", "move south");
          fflush(stdout);
          b_maze->data[(static_cast<int>(intersectionRow) + b_maze->size[0] *
                        (static_cast<int>(intersectionCol) - 1)) - 1] = -1.0F;
          directionsToMoveIn = c_maze->size[0] * c_maze->size[1];
          c_maze->size[0] = b_maze->size[0];
          c_maze->size[1] = b_maze->size[1];
          emxEnsureCapacity_real32_T(c_maze, directionsToMoveIn);
          loop_ub = b_maze->size[0] * b_maze->size[1];
          for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
               directionsToMoveIn++) {
            c_maze->data[directionsToMoveIn] = b_maze->data[directionsToMoveIn];
          }

          b_finished = b_depthFirstFunction(c_maze, intersectionRow + 1.0F,
            intersectionCol, endRow, endCol);
        }

        if (west && (!b_finished)) {
          printf("%s\n", "move east");
          fflush(stdout);
          b_maze->data[(static_cast<int>(intersectionRow) + b_maze->size[0] *
                        (static_cast<int>(intersectionCol) - 1)) - 1] = -1.0F;
          b_depthFirstFunction(b_maze, intersectionRow, intersectionCol - 1.0F,
                               endRow, endCol);
        }

        /* If we can move in multiple directions     */
      } else if (directionsToMoveIn > 1) {
        b_maze->data[(static_cast<int>(intersectionRow) + b_maze->size[0] *
                      (static_cast<int>(intersectionCol) - 1)) - 1] = -1.0F;
        if (east) {
          directionsToMoveIn = c_maze->size[0] * c_maze->size[1];
          c_maze->size[0] = b_maze->size[0];
          c_maze->size[1] = b_maze->size[1];
          emxEnsureCapacity_real32_T(c_maze, directionsToMoveIn);
          loop_ub = b_maze->size[0] * b_maze->size[1];
          for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
               directionsToMoveIn++) {
            c_maze->data[directionsToMoveIn] = b_maze->data[directionsToMoveIn];
          }

          b_finished = c_depthFirstFunction(c_maze, intersectionRow,
            intersectionCol + 1.0F, endRow, endCol);
        }

        if (south && (!b_finished)) {
          directionsToMoveIn = c_maze->size[0] * c_maze->size[1];
          c_maze->size[0] = b_maze->size[0];
          c_maze->size[1] = b_maze->size[1];
          emxEnsureCapacity_real32_T(c_maze, directionsToMoveIn);
          loop_ub = b_maze->size[0] * b_maze->size[1];
          for (directionsToMoveIn = 0; directionsToMoveIn < loop_ub;
               directionsToMoveIn++) {
            c_maze->data[directionsToMoveIn] = b_maze->data[directionsToMoveIn];
          }

          b_finished = c_depthFirstFunction(c_maze, intersectionRow + 1.0F,
            intersectionCol, endRow, endCol);
        }

        if (west && (!b_finished)) {
          c_depthFirstFunction(b_maze, intersectionRow, intersectionCol - 1.0F,
                               endRow, endCol);
        }
      } else {
        printf("%s\n", "Can\'t move");
        fflush(stdout);
      }
    }
  }

  emxFree_real32_T(&c_maze);
  emxFree_real32_T(&b_maze);
  return finished;
}

/* End of code generation (depthFirstFunction.cpp) */
