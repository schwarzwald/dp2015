/*
 * ldgmtypes.c
 *
 *  Created on: Mar 20, 2016
 *      Author: Bibo
 */
#include "ldgmtypes.h"
#include <stdlib.h>
#include <bitpunch/debugio.h>

void BPU_ldgmFreeSpec(BPU_T_LDGM_Spec *spec) {
  BPU_gf2QcMatrixFree(spec->g_mat, 0);
  BPU_gf2QcMatrixFree(spec->h_mat, 0);
  BPU_gf2QcMatrixFree(spec->q_mat, 0);
  BPU_gf2QcMatrixFree(spec->s_mat, 0);
  BPU_gf2MatFree(&spec->b_mat);
}

int BPU_ldgmInitParams(BPU_T_LDGM_Params **params, const uint16_t n0, const uint16_t k0, const uint16_t p, const uint16_t z, const uint16_t w_t,
    const uint16_t w_s, const uint16_t w_g, const uint16_t t, const uint16_t c) {
  *params = (BPU_T_LDGM_Params*) calloc(sizeof(BPU_T_LDGM_Params), 1);

  if (!params) {
    BPU_printError("Can't init Code params");
    return -1;
  }

  (*params)->n0 = n0;
  (*params)->k0 = k0;
  (*params)->p = p;
  (*params)->z = z;
  (*params)->w_t = w_t;
  (*params)->w_s = w_s;
  (*params)->w_g = w_g;
  (*params)->t = t;
  (*params)->c = c;

  return 0;
}

void BPU_ldgmFreeParams(BPU_T_LDGM_Params **params) {
  if (*params) {
    free(*params);
  }

  *params = NULL;
}

