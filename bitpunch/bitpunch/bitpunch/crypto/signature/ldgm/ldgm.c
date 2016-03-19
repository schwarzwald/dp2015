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

int BPU_ldgmEncode(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx) {
  //out = ctx->code_spec->ldgm->h_mat * in 
  return 0;
}

int BPU_ldgmDecode(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx) {
  /*s1 = ctx->code_spec->ldgm->q_mat * in
   e = [0, trans(s1)];
   c = pickWord();
   e1 = (e+c)*trans(ctx->code_spec->ldgm->s_mat);*/
  return 0;
}

int BPU_ldgmGenKeys(BPU_T_Code_Ctx *ctx) {
  BPU_T_LDGM_Spec *specs = &ctx->code_spec->ldgm;
  BPU_ldgmGenerateGenMatrix(specs);
  BPU_ldgmGenerateQMatrix(specs);
  BPU_ldgmGenerateSMatrix(specs);
  BPU_ldgmBuildParityCheckMatrix(specs);
  return 0;
}

int BPU_ldgmGenerateGenMatrix(BPU_T_LDGM_Spec *specs) {

  return 0;
}

int BPU_ldgmGenerateQMatrix(BPU_T_LDGM_Spec *specs) {
  BPU_T_GF2_Matrix *a, *a_t, *b, *product;
  BPU_T_GF2_Vector *rand1, *rand2;
  BPU_T_GF2_QC_Matrix matR, matT;
  BPU_T_GF2_Poly ones;

  int i, j, r0 = specs->n0 - specs->k0;

  BPU_gf2MatMalloc(&a, specs->z, r0);
  BPU_gf2MatMalloc(&a_t, r0, specs->z);
  BPU_gf2MatMalloc(&b, specs->z, r0);
  BPU_gf2VecMalloc(&rand1, r0);
  BPU_gf2VecMalloc(&rand2, r0);
  BPU_gf2PolyMalloc(&ones, specs->p);

  for (i = 0; i < ones.elements_in_row; i++) {
    ones.elements[i] = -1;
  }

  for (i = 0; i < specs->z; i++) {
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

  BPU_gf2QcMultirowMatrixMalloc(specs->b_mat, r0, 1, specs->p);

  for (i = 0; i < specs->z; i++) {
    for (j = 0; j < b->elements_in_row; j++) {
      if (BPU_gf2MatGetBit(b, i, j)) {
        BPU_gf2PolyCopy(&b->elements[i * r0 + j], &ones);
      }
    }
  }

  BPU_gf2QcMultirowMatrixMalloc(&matR, specs->p * r0, specs->p * r0, specs->p);

  for (i = 0; i < matR.column_element_count; i++) {
    for (j = 0; j < matR.row_element_count; j++) {
      if (BPU_gf2MatGetBit(product, i, j)) {
        BPU_gf2PolyCopy(&matR.matrices[i * matR.row_element_count + j], &ones);
      }
    }
  }

  BPU_ldgmGenerateConstantWeightQcMatrix(&matT, matR.column_element_count, matR.element_size, specs->w_t);
  BPU_gf2QcMatrixAdd(&matT, &matR);
  BPU_gf2QcMatrixCopy(specs->q_mat, &matT);

  BPU_gf2MatFree(&a);
  BPU_gf2MatFree(&b);
  BPU_gf2MatFree(&a_t);
  BPU_gf2MatFree(&product);
  BPU_gf2PolyFree(&ones, 0);
  BPU_gf2QcMatrixFree(matR, 0);
  BPU_gf2QcMatrixFree(matT, 0);

  return 0;
}

int BPU_ldgmGenerateConstantWeightQcMatrix(BPU_T_GF2_QC_Matrix *out, int blocks_count, int block_size, int weight) {
  int i = weight - 1, j, rand_block;
  int blocks[blocks_count];
  BPU_T_GF2_Poly block_poly, temp;
  BPU_T_Perm_Vector *permutation;

  blocks[0] = 1;

  while (i > 0) {
    rand_block = rand() % blocks_count;
    if (blocks[rand_block] <= block_size - 2) {
      blocks[rand_block] += 2;
      i = i - 2;
    }
  }

  BPU_gf2QcMultirowMatrixMalloc(out, blocks_count, blocks_count, block_size);

  for (i = 0; i < blocks_count; i++) {
    BPU_gf2PolyInitRand(&block_poly, block_size, blocks[i], 0);
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
}

int BPU_ldgmGenerateSMatrix(BPU_T_LDGM_Spec *specs) {
  return 0;
}

int BPU_ldgmBuildParityCheckMatrix(BPU_T_LDGM_Spec *specs) {
  return 0;
}
