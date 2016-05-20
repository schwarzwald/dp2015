/*
 This file is part of BitPunch
 Copyright (C) 2016 Pavol Dobrocka <pavol.dobrocka[what here]gmail.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LDGMTYPES_H
#define LDGMTYPES_H
#include <bitpunch/math/gf2types.h>
#include <bitpunch/math/permtypes.h>

/**
 Internal LDGM code structure.
 */
typedef struct _BPU_T_LDGM_Spec {
  BPU_T_GF2_QC_Matrix *g_mat;
  BPU_T_GF2_QC_Matrix *h_mat;
  BPU_T_GF2_QC_Matrix *q_mat;
  BPU_T_GF2_QC_Matrix *s_mat;
  BPU_T_GF2_Matrix *b_mat;
  uint16_t c;

} BPU_T_LDGM_Spec;

/**
 LDGM code params.
 */
typedef struct _BPU_T_LDGM_Params {
  uint16_t n0;
  uint16_t k0;
  uint16_t p;
  uint16_t z;
  uint16_t w_t;
  uint16_t w_s;
  uint16_t w_g;
  uint16_t c;
  uint16_t t;
} BPU_T_LDGM_Params;

/**
 * Free the memory which holds the code spec
 *
 * @param spec specification of the code
 */
void BPU_ldgmFreeSpec(BPU_T_LDGM_Spec *spec);

/**
 * Initializes the parameters structure with the given values
 *
 * @param params output of the initialization
 * @param n0  number of circulant blocks in row
 * @param k0  number of circulant blocks in column
 * @param p   size of the circulant blocks
 * @param z   security parameter z
 * @param w_t weight of rows and columns of matrix T
 * @param w_s weight of rows and columns of matrix S
 * @param w_g weight of rows of the matrix G
 * @param t   weight of the syndrome
 * @param c   number of word which are added to the error word
 * @return 0 on success, error code on failure
 */
int BPU_ldgmInitParams(BPU_T_LDGM_Params **params, const uint16_t n0, const uint16_t k0, const uint16_t p, const uint16_t z, const uint16_t w_t,
    const uint16_t w_s, const uint16_t w_g, const uint16_t t, const uint16_t c);

/**
 * Free the memory which holds the code params
 *
 * @param spec specification of the code
 */
void BPU_ldgmFreeParams(BPU_T_LDGM_Params **params);

#endif // LDGMTYPES_H
