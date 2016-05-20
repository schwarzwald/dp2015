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

#ifndef BPU_LDGM_H
#define BPU_LDGM_H

#include <math.h>
#include <bitpunch/config.h>
#include <bitpunch/code/codectx.h>
#include <bitpunch/math/gf2.h>
#include <bitpunch/debugio.h>
#include <bitpunch/math/perm.h>

#include <bitpunch/crypto/hash/sha512.h>

/**
 * Encoding function of the LDGM code. Encodes the {@code in} vector into an {@code out}
 * vector using the given configuration of the code.
 *
 * @param out encoded vector
 * @param in  input to encode
 * @param ctx context of the code
 * @return 0 on success, error value on failure
 */
int BPU_ldgmEncode(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx);

/**
 * Decoding function of the LDGM code. Decodes the {@code in} vector into an {@code out}
 * vector using the given configuration of the code.
 *
 * @param out decoded vector
 * @param in  input to decode
 * @param ctx context of the code
 * @return 0 on success, error value on failure
 */
int BPU_ldgmDecode(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx);

/**
 * Adds a code word from the code to the output vector depending on the input.
 * This is so called psi function of the LDGM code. out = out + psi(in)
 *
 * @param out output vector
 * @param in  input i.e. the message
 * @param ctx context of the code
 */
void BPU_ldgmAddCodeWord(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx);

/**
 * Generates the key pair according to the parameters
 *
 * @param ctx context in which the keys will be set
 * @param params parameters of the code
 * @return 0 on success, error value on failure
 */
int BPU_ldgmGenKeys(BPU_T_Code_Ctx *ctx, BPU_T_LDGM_Params *params);

/**
 * Function to generate the generating matrix according to the parameters.
 * This is a part of the @link{BPU_ldgmGenKeys} function.
 *
 * @param params parameters of the code
 * @param g_mat output of the generation
 * @return 0 on success, error value on failure
 */
int BPU_ldgmGenerateGenMatrix(BPU_T_LDGM_Params *params, BPU_T_GF2_QC_Matrix *g_mat);

/**
 * Function to build the public parity check matrix.
 *
 * @param h_mat private parity check matrix H
 * @param q_mat private generating matrix G
 * @param q_mat_inv inverse of the Q matrix
 * @param s_mat_inv inverse of the S matrix
 * @return 0 on success, error value on failure
 */
int BPU_ldgmBuildParityCheckMatrix(BPU_T_GF2_QC_Matrix *h_mat, BPU_T_GF2_QC_Matrix *g_mat, BPU_T_GF2_QC_Matrix *q_mat_inv, BPU_T_GF2_QC_Matrix *s_mat_inv);

/**
 * Function to generate a random QC matrix of the given size where each column and row
 * has the given weight.
 *
 * @param out           output of the generation
 * @param block_count   number of circulant blocks
 * @param block_size    size of the circulant block
 * @param weight        weight of each column and row
 * @return 0 on success, error value on failure
 */
int BPU_ldgmGenerateConstantWeightQcMatrix(BPU_T_GF2_QC_Matrix *out, int blocks_count, int block_size, int weight);

/**
 * Generates the Q matrix and its weight controlling determinant b
 * according to the parameters
 *
 * @param params      parameters of the code
 * @param q_mat       output of the Q matrix generation
 * @param b_mat       output of the b matrix generation
 * @return 0 on success, error value on failure
 */
int BPU_ldgmGenerateQMatrix(BPU_T_LDGM_Params *params, BPU_T_GF2_QC_Matrix *q_mat, BPU_T_GF2_Matrix *b_mat);

/**
 * Generates the scrambling matrix S according to the parameters.
 *
 * @param params      input to encode
 * @param s_mat       output of the generation
 * @return 0 on success, error value on failure
 */
int BPU_ldgmGenerateSMatrix(BPU_T_LDGM_Params *params, BPU_T_GF2_QC_Matrix *s_mat);

#endif // BPU_LDGM_H
