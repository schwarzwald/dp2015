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
#include "sigctx.h"

#include <stdlib.h>

#include <bitpunch/debugio.h>
#include <bitpunch/errorcodes.h>
#include <bitpunch/math/gf2types.h>

// additional codes
#include <bitpunch/crypto/signature/ldgm/ldgmsig.h>

int BPU_signatureInitCtx(BPU_T_Signature_Ctx **ctx, const BPU_T_UN_Signature_Params *params, const BPU_T_EN_Signature_Types type) {
  BPU_T_Signature_Ctx *ctx_p;
  *ctx = (BPU_T_Signature_Ctx *) calloc(1, sizeof(BPU_T_Signature_Ctx));
  if (!*ctx) {
    BPU_printError("Cannot malloc BPU_T_Signature_Ctx");
    return BPU_EC_MALLOC_ERROR;
  }

  ctx_p = *ctx;
  ctx_p->code_ctx = (BPU_T_Code_Ctx *) calloc(1, sizeof(BPU_T_Code_Ctx));

  if (!ctx_p->code_ctx) {
    BPU_printError("Cannot malloc BPU_T_Code_Ctx");
    return BPU_EC_MALLOC_ERROR;
  }

  ctx_p->type = type;

  ctx_p->code_ctx->code_spec = (BPU_T_UN_Code_Spec *) calloc(1, sizeof(BPU_T_UN_Code_Spec));
  if (!ctx_p->code_ctx->code_spec) {
    BPU_printError("Can not malloc BPU_T_UN_Code_Spec");
    return BPU_EC_MALLOC_ERROR;
  }

  ctx_p->params = params;

  switch (type) {
  case BPU_EN_SIGN_LDGM:
    ctx_p->code_ctx->type = BPU_EN_CODE_LDGM;
    ctx_p->code_ctx->t = params->ldgm->t;
    ctx_p->code_ctx->code_spec->ldgm = (BPU_T_LDGM_Spec*) calloc(sizeof(BPU_T_LDGM_Spec), 1);
    ctx_p->code_ctx->code_spec->ldgm->c = params->ldgm->c;
    ctx_p->_genKeyPair = BPU_ldgmGenKeyPair;
    ctx_p->_sign = BPU_ldgmSign;
    ctx_p->_verify = BPU_ldgmVerify;
    break;
  }

  return 0;
}

void BPU_signatureFreeCtx(BPU_T_Signature_Ctx **ctx) {
  BPU_T_Signature_Ctx *ctx_p = *ctx;

  if (!ctx_p) {
    return;
  }
  BPU_codeFreeCtx(&ctx_p->code_ctx);
  free(ctx_p->code_ctx);
  free(ctx_p->params->ldgm);
  free(ctx_p->params);
  free(ctx_p);
  *ctx = NULL;
}

int BPU_signatureKeyGen(BPU_T_Signature_Ctx **ctx) {
  return (*ctx)->_genKeyPair(*ctx);
}

int BPU_signatureSign(BPU_T_Signature_Ctx **ctx, BPU_T_UN_Signature *signature, const BPU_T_GF2_Vector *message) {
  return (*ctx)->_sign(signature, message, *ctx);
}

int BPU_signatureVerify(BPU_T_Signature_Ctx **ctx, BPU_T_EN_Signature_Verification_Result_Type* result, BPU_T_GF2_Vector *message,
    const BPU_T_UN_Signature *signature) {
  return (*ctx)->_verify(result, message, signature, *ctx);
}

