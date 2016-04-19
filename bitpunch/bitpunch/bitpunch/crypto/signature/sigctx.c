/*
 * sigctx.c
 *
 *  Created on: Mar 20, 2016
 *      Author: Bibo
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

