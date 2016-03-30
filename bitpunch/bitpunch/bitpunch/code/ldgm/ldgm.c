/*
 This file is part of BitPunch
 Copyright (C) 2015 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>
 Copyright (C) 2015 Andrej Gulyas <andrej.guly[what here]gmail.com>

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

#include <bitpunch/code/ldgm/ldgm.h>

int BPU_ldgmEncode(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx) {
  BPU_gf2QcMatrixVectorMultiply(out, ctx->code_spec->ldgm->h_mat, in);
  return 0;
}

int BPU_ldgmDecode(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx) {
  BPU_T_GF2_Vector *s1, *e;
  int i, k = ctx->code_spec->ldgm->g_mat->k;

  BPU_gf2VecMalloc(&s1, in->len);
  BPU_gf2QcMatrixVectorMultiply(s1, ctx->code_spec->ldgm->q_mat, in);
  BPU_gf2VecMalloc(&e, ctx->code_spec->ldgm->g_mat->n);

  for (i = 0; i < in->len; i++) {
    BPU_gf2VecSetBit(e, (k + i), BPU_gf2VecGetBit(s1, i));
  }

  BPU_ldgmAddCodeWord(e, in, ctx);
  BPU_gf2QcMatrixVectorMultiply(out, ctx->code_spec->ldgm->s_mat, e);

  BPU_gf2VecFree(&s1);
  BPU_gf2VecFree(&e);

  return 0;
}

void BPU_ldgmAddCodeWord(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx) {
  BPU_T_GF2_Vector *hash, *word;
  int word_count, rows, i, index, bits_to_read;
  BPU_gf2VecMalloc(&hash, 512);
  BPU_gf2VecHash(hash, in);

  word_count = ctx->code_spec->ldgm->c;
  rows = ctx->code_spec->ldgm->g_mat->k;
  bits_to_read = (int) log2((double) rows);

  for (i = 0; i < word_count; i++) {
    word = (BPU_T_GF2_Vector*) calloc(sizeof(BPU_T_GF2_Vector), 1);
    index = read(hash, bits_to_read);
    BPU_gf2QcMatrixGetRow(word, ctx->code_spec->ldgm->g_mat, index < rows ? index : rows - 1);
    BPU_gf2VecXor(out, word);
    BPU_gf2VecFree(&word);
  }
}

int BPU_ldgmGenKeys(BPU_T_Code_Ctx *ctx, BPU_T_LDGM_Params *params) {
  int found = 0;
  BPU_T_LDGM_Spec *specs = ctx->code_spec->ldgm;
  BPU_T_GF2_QC_Matrix g_mat, h_mat, q_mat, q_mat_inv, s_mat, s_mat_inv;
  BPU_T_GF2_Matrix *b_mat;

  BPU_ldgmGenerateGenMatrix(params, &g_mat);

  while (!found) {
    BPU_gf2MatMalloc(&b_mat, params->z, (params->n0 - params->k0) * params->p);
    BPU_ldgmGenerateQMatrix(params, &q_mat, b_mat);
    if (BPU_gf2QcInvMatrix(&q_mat_inv, &q_mat)) {
      found = 1;
    } else {
      BPU_gf2MatFree(&b_mat);
      BPU_gf2QcMatrixFree(&q_mat, 0);
    }
  }

  found = 0;

  while (!found) {
    BPU_ldgmGenerateSMatrix(params, &s_mat);

    if (BPU_gf2QcInvMatrix(&s_mat_inv, &s_mat)) {
      found = 1;
    } else {
      BPU_gf2QcMatrixFree(&s_mat, 0);
    }
  }

  BPU_ldgmBuildParityCheckMatrix(&h_mat, &g_mat, &q_mat_inv, &s_mat_inv);

  BPU_gf2QcMatrixFree(&q_mat_inv, 0);
  BPU_gf2QcMatrixFree(&s_mat_inv, 0);

  specs->q_mat = (BPU_T_GF2_QC_Matrix*) calloc(sizeof(BPU_T_GF2_QC_Matrix), 1);
  BPU_gf2QcMatrixCopy(specs->q_mat, &q_mat);
  BPU_gf2QcMatrixFree(&q_mat, 0);

  specs->s_mat = (BPU_T_GF2_QC_Matrix*) calloc(sizeof(BPU_T_GF2_QC_Matrix), 1);
  BPU_gf2QcMatrixCopy(specs->s_mat, &s_mat);
  BPU_gf2QcMatrixFree(&s_mat, 0);

  specs->g_mat = (BPU_T_GF2_QC_Matrix*) calloc(sizeof(BPU_T_GF2_QC_Matrix), 1);
  BPU_gf2QcMatrixCopy(specs->g_mat, &g_mat);
  BPU_gf2QcMatrixFree(&g_mat, 0);

  specs->h_mat = (BPU_T_GF2_QC_Matrix*) calloc(sizeof(BPU_T_GF2_QC_Matrix), 1);
  BPU_gf2QcMatrixCopy(specs->h_mat, &h_mat);
  BPU_gf2QcMatrixFree(&h_mat, 0);

  BPU_gf2MatMalloc(&specs->b_mat, b_mat->k, b_mat->n);
  BPU_gf2MatCopy(specs->b_mat, b_mat);
  BPU_gf2MatFree(&b_mat);

  return 0;
}

int BPU_ldgmGenerateGenMatrix(BPU_T_LDGM_Params *params, BPU_T_GF2_QC_Matrix *g_mat) {
  int i, j, r0 = params->n0 - params->k0, rand_block;
  int *blocks = (int*) calloc(sizeof(int), r0);
  BPU_T_GF2_QC_Matrix eye, random_matrix;

  BPU_gf2QcMultirowMatrixMalloc(&random_matrix, r0, params->k0, params->p);

  for (i = 0; i < params->k0; i++) {
    j = params->w_g - 1;
    while (j > 0) {
      rand_block = rand() % r0; //TODO: change to BPU_prngGetRand
      if (blocks[rand_block] < params->p) {
        blocks[rand_block]++;
        j--;
      }
    }

    for (j = 0; j < r0; j++) {
      BPU_gf2PolyInitRand(&random_matrix.matrices[i * r0 + j], params->p, blocks[j], 0);
      blocks[j] = 0;
    }
  }

  BPU_gf2QcEyeMatrix(&eye, params->p, params->k0);
  BPU_gf2QcAppendMatrix(g_mat, &eye, &random_matrix, 0);
  BPU_gf2QcMatrixFree(&eye, 0);
  BPU_gf2QcMatrixFree(&random_matrix, 0);

  return 0;
}

int BPU_ldgmGenerateQMatrix(BPU_T_LDGM_Params *params, BPU_T_GF2_QC_Matrix *q_mat, BPU_T_GF2_Matrix *b_mat) {
  BPU_T_GF2_Matrix *a, *a_t, *b, *product;
  BPU_T_GF2_Vector *rand1, *rand2;
  BPU_T_GF2_QC_Matrix matR, matT;
  BPU_T_GF2_Poly ones;

  int i, j, k, r0 = params->n0 - params->k0;

  BPU_gf2MatMalloc(&a, params->z, r0);
  BPU_gf2MatMalloc(&a_t, r0, params->z);
  BPU_gf2MatMalloc(&b, params->z, r0);
  BPU_gf2VecMalloc(&rand1, r0);
  BPU_gf2VecMalloc(&rand2, r0);
  BPU_gf2PolyMalloc(&ones, params->p);

  for (i = 0; i < ones.len; i++) {
    BPU_gf2VecSetBit(&ones, i, 1);
  }

  for (i = 0; i < params->z; i++) {
    BPU_gf2VecRand(rand1, 0);
    BPU_gf2VecRand(rand2, 0);
    for (j = 0; j < a->elements_in_row; j++) {
      a->elements[i][j] = rand1->elements[j];
      b->elements[i][j] = rand2->elements[j];
    }
  }

  BPU_gf2MatTransp(a_t, a);
  BPU_gf2MulMat(&product, a_t, b);

  BPU_gf2VecFree(&rand1);
  BPU_gf2VecFree(&rand2);

  for (i = 0; i < b->k; i++) {
    for (j = 0; j < b->n; j++) {
      if (BPU_gf2MatGetBit(b, i, j)) {
        for (k = 0; k < params->p; k++) {
          BPU_gf2MatSetBit(b_mat, i, (params->p * j + k), 1);
        }
      }
    }
  }

  BPU_gf2QcMultirowMatrixMalloc(&matR, r0, r0, params->p);

  for (i = 0; i < matR.column_element_count; i++) {
    for (j = 0; j < matR.row_element_count; j++) {
      if (BPU_gf2MatGetBit(product, i, j)) {
        BPU_gf2PolyCopy(&matR.matrices[i * matR.row_element_count + j], &ones);
      } else {
        BPU_gf2PolyMalloc(&matR.matrices[i * matR.row_element_count + j], params->p);
      }
    }
  }

  BPU_ldgmGenerateConstantWeightQcMatrix(&matT, matR.column_element_count, matR.element_size, params->w_t);
  BPU_gf2QcMatrixAdd(&matT, &matR);
  BPU_gf2QcMatrixCopy(q_mat, &matT);

  BPU_gf2MatFree(&a);
  BPU_gf2MatFree(&b);
  BPU_gf2MatFree(&a_t);
  BPU_gf2MatFree(&product);
  BPU_gf2PolyFree(&ones, 0);
  BPU_gf2QcMatrixFree(&matR, 0);
  BPU_gf2QcMatrixFree(&matT, 0);

  return 0;
}

int BPU_ldgmGenerateConstantWeightQcMatrix(BPU_T_GF2_QC_Matrix *out, int blocks_count, int block_size, int weight) {
  int i = weight - 1, j, rand_block;
  int *blocks = (int*) calloc(sizeof(int), blocks_count);
  BPU_T_GF2_Poly block_poly;
  BPU_T_Perm_Vector *permutation;

  blocks[0] = 1;

  while (i > 0) { //TODO: adjust to even weight too
    rand_block = rand() % blocks_count; //TODO: change to BPU_prngGetRand
    if (blocks[rand_block] <= block_size - 2) {
      blocks[rand_block] += 2;
      i -= 2;
    }
  }

  BPU_gf2QcMultirowMatrixMalloc(out, blocks_count, blocks_count, block_size);

  for (i = 0; i < blocks_count; i++) {
    if (blocks[i] > 0) {
      BPU_gf2PolyInitRand(&block_poly, block_size, blocks[i], 0);
    } else {
      BPU_gf2PolyMalloc(&block_poly, block_size);
    }
    for (j = 0; j < blocks_count; j++) {
      BPU_gf2PolyCopy(&out->matrices[j * blocks_count + ((j + i) % blocks_count)], &block_poly);
    }

    BPU_gf2PolyFree(&block_poly, 0);
  }

  BPU_permMalloc(&permutation, blocks_count);
  BPU_permRandomize(permutation);

  BPU_gf2QcPermuteMatrixColumns(out, permutation);
  BPU_permRandomize(permutation);
  BPU_gf2QcPermuteMatrixRows(out, permutation);

  BPU_permFree(&permutation);

  return 0;
}

int BPU_ldgmGenerateSMatrix(BPU_T_LDGM_Params *params, BPU_T_GF2_QC_Matrix *s_mat) {
  BPU_ldgmGenerateConstantWeightQcMatrix(s_mat, params->n0, params->p, params->w_s);
  return 0;
}

int BPU_ldgmBuildParityCheckMatrix(BPU_T_GF2_QC_Matrix *h_mat, BPU_T_GF2_QC_Matrix *g_mat, BPU_T_GF2_QC_Matrix *q_mat_inv, BPU_T_GF2_QC_Matrix *s_mat_inv) {
  BPU_T_GF2_QC_Matrix eye, temp1, temp2;

  BPU_gf2QcSelectMatrix(&temp1, g_mat, g_mat->column_element_count, g_mat->row_element_count, 0, g_mat->column_element_count);
  BPU_gf2QcMultirowMatrixTransp(&temp2, &temp1);
  BPU_gf2QcMatrixFree(&temp1, 0);
  BPU_gf2QcEyeMatrix(&eye, temp2.element_size, temp2.column_element_count);
  BPU_gf2QcAppendMatrix(&temp1, &temp2, &eye, 0);
  BPU_gf2QcMatrixFree(&temp2, 0);
  BPU_gf2QcMatrixFree(&eye, 0);

  BPU_gf2QcMatrixMultiply(&temp2, &temp1, s_mat_inv);
  BPU_gf2QcMatrixFree(&temp1, 0);
  BPU_gf2QcMatrixMultiply(h_mat, q_mat_inv, &temp2);
  BPU_gf2QcMatrixFree(&temp2, 0);

  return 0;
}
