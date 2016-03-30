/*
 This file is part of BitPunch
 Copyright (C) 2015 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>

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
 Internal Goppa code structure.
 */
typedef struct _BPU_T_LDGM_Spec {
  BPU_T_GF2_QC_Matrix *g_mat; ///< Generator matrix
  BPU_T_GF2_QC_Matrix *h_mat; ///< Control matrix H
  BPU_T_GF2_QC_Matrix *q_mat; ///< Weight controlling matrix Q
  BPU_T_GF2_QC_Matrix *s_mat; ///< Scrambler matrix S
  BPU_T_GF2_Matrix *b_mat;
  uint16_t c;

} BPU_T_LDGM_Spec;

/**
 Goppa code params.
 */
typedef struct _BPU_T_LDGM_Params {
  uint16_t n0; ///< root length of the code (n = n0*p)
  uint16_t k0; ///< root dimension of the code (k = k0*p)
  uint16_t p; ///< size of the cyclic blocks
  uint16_t z; ///< security parameter z
  uint16_t w_t;
  uint16_t w_s;
  uint16_t w_g;
  uint16_t c;
  uint16_t t;
} BPU_T_LDGM_Params;

/**
 * @brief BPU_goppaFreeSpec Free Goppa code internal structure.
 * @param spec
 */
void BPU_ldgmFreeSpec(BPU_T_LDGM_Spec *spec);

/**
 * @brief BPU_goppaInitParams Initi Goppa code params.
 * @param params
 * @param m
 * @param t
 * @param mod
 * @return
 */
int BPU_ldgmInitParams(BPU_T_LDGM_Params **params, const uint16_t n0, const uint16_t k0, const uint16_t p, const uint16_t z, const uint16_t w_t,
    const uint16_t w_s, const uint16_t w_g, const uint16_t t, const uint16_t c);

/**
 * @brief BPU_goppaFreeParams Free goppa code params.
 * @param params
 */
void BPU_ldgmFreeParams(BPU_T_LDGM_Params **params);

#endif // LDGMTYPES_H
