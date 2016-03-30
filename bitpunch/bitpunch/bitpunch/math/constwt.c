/*
 * constwt.c
 *
 *  Created on: Mar 22, 2016
 *      Author: Bibo
 */

#include "constwt.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int read(BPU_T_GF2_Vector *in, int l) {
  //fprintf(stderr, "%d ", l);
  int ret = 0;
  int i = 0;
  while (i < l) { //l-- > 0) {
    ret |= BPU_gf2VecShiftLeft(in) << i;
    i++;
  }

  return ret;
}

int decode(BPU_T_GF2_Vector *in, int d) {
  int u = 2;
  int delta = 0;
  int pow = 1;

  if (d <= 1) {
    u = 2;
  } else {
    u = ceil(log2(d));
    if (u < 2) {
      u = 2;
    }
  }

  pow = 1 << u;
  delta = read(in, u - 1);
  if (delta >= pow - d) {
    delta = 2 * delta + read(in, 1) - pow + d;
  }

  return delta;
}

double best_d(int n, int t) {
  double t1_2 = ((double) (t - 1)) / 2;
  double t1_2pow = 1.0 / pow(2, (1.0 / t));
  double ret = ceil((n - t1_2) * (1 - t1_2pow));

  if (ret < 1) {
    return 1;
  } else if (ret > n - t) {
    return n - t;
  } else {
    return ret;
  }

}

int bToCw(BPU_T_GF2_Vector *in, int *out, int i, int n, int t, int delta) {
  int c, d;
  if (t == 0) {
    return 0;
  } else if (n <= t) {
    out[i] = delta;
    bToCw(in, out, i + 1, n - 1, t - 1, 0);
  } else {
    d = (int) best_d(n, t);
    if (read(in, 1) == 1) {
      bToCw(in, out, i, n - d, t, delta + d);
    } else {
      c = decode(in, d);
      out[i] = delta + c;
      bToCw(in, out, i + 1, n - i - 1, t - 1, 0);
    }
  }

  return 0;
}

int BPU_gf2VecToConstantWeight(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, int n, int wt) {
  int i, j = 0, *array;

  array = (int*) calloc(sizeof(int), wt);

  bToCw(in, array, 0, n, wt, 0);

  for (i = 0; i < wt; i++) {
    BPU_gf2VecSetBit(out, j + array[i], 1);
    j += array[i] + 1;
  }

  for (i = 0; i < wt; i++) {
    //sum += arr[i];
    //fprintf(stderr, "%d ", array[i]);
  }

  return 0;
}

