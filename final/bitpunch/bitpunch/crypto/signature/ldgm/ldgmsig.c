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

#include "ldgmsig.h"

int BPU_ldgmSign(BPU_T_UN_Signature *signature, const BPU_T_GF2_Vector *message, const struct _BPU_T_Signature_Ctx *ctx) {
  BPU_T_GF2_Matrix *b = ctx->code_ctx->code_spec->ldgm->b_mat, *b_t;
  BPU_T_GF2_Vector *hash, *counter, *message_with_counter, *s, *bxs;
  uint32_t i = 0;
  int is_decodable = 0, wt = ctx->code_ctx->t;

  signature->ldgm = (BPU_T_LDGM_Signature*) calloc(sizeof(BPU_T_LDGM_Signature), 1);

  BPU_gf2MatMalloc(&b_t, b->n, b->k);
  BPU_gf2MatTransp(b_t, b);

  while (!is_decodable) {
    BPU_gf2VecMalloc(&counter, 32);
    BPU_gf2VecMalloc(&message_with_counter, 512 + 32);
    BPU_gf2VecMalloc(&hash, 512);
    BPU_gf2VecMalloc(&s, b->n);

    counter->elements[0] = i;

    BPU_gf2VecConcat(message_with_counter, message, counter);
    BPU_gf2VecHash(hash, message_with_counter);
    BPU_gf2VecToConstantWeight(s, hash, b->n, wt);

    BPU_gf2VecFree(&hash);
    BPU_gf2VecFree(&counter);
    BPU_gf2VecFree(&message_with_counter);

    BPU_gf2VecMalloc(&bxs, b_t->n);
    BPU_gf2VecMulMat(bxs, s, b_t);

    if (BPU_gf2VecIsZero(bxs)) {
      is_decodable = 1;
    } else {
      BPU_gf2VecFree(&s);
      i++;
    }

    BPU_gf2VecFree(&bxs);
  }

  BPU_gf2MatFree(&b_t);

  BPU_gf2VecMalloc(&signature->ldgm->signature, ctx->code_ctx->code_spec->ldgm->s_mat->n);
  BPU_ldgmDecode(signature->ldgm->signature, s, ctx->code_ctx);
  signature->ldgm->counter = i;

  BPU_gf2VecFree(&s);

  return 0;
}

int BPU_ldgmVerify(BPU_T_EN_Signature_Verification_Result_Type* result, BPU_T_GF2_Vector *message, const BPU_T_UN_Signature *signature,
    const struct _BPU_T_Signature_Ctx *ctx) {
  BPU_T_GF2_Vector *hash, *counter, *message_with_counter, *s, *s1;
  int r = ctx->code_ctx->code_spec->ldgm->h_mat->k;
  int wt = ctx->code_ctx->t;
  int sig_wt = BPU_gf2VecGetWeight(signature->ldgm->signature);
  BPU_T_LDGM_Params *params = ctx->params->ldgm;
  int wt_limit = (params->w_t * params->t + params->c * params->w_g) * params->w_s;

  if (sig_wt > wt_limit) {
    *result = BPU_EN_SIG_DISCARD;
    return 0;
  }

  BPU_gf2VecMalloc(&counter, 32);
  BPU_gf2VecMalloc(&message_with_counter, 512 + 32);
  BPU_gf2VecMalloc(&hash, 512);
  BPU_gf2VecMalloc(&s, r);
  BPU_gf2VecMalloc(&s1, r);

  counter->elements[0] = signature->ldgm->counter;

  BPU_gf2VecConcat(message_with_counter, message, counter);
  BPU_gf2VecHash(hash, message_with_counter);
  BPU_gf2VecToConstantWeight(s, hash, r, wt);
  BPU_ldgmEncode(s1, signature->ldgm->signature, ctx->code_ctx);
  *result = BPU_gf2VecCmp(s1, s) == 0 ? BPU_EN_SIG_ACCEPT : BPU_EN_SIG_DISCARD;

  return 0;
}

int BPU_ldgmGenKeyPair(struct _BPU_T_Signature_Ctx *sig_ctx) {
  BPU_ldgmGenKeys(sig_ctx->code_ctx, sig_ctx->params->ldgm);
  return 0;
}
