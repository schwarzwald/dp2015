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
#ifndef LDGMSIG_H
#define LDGMSIG_H

#include <bitpunch/config.h>
#include <bitpunch/math/gf2.h>
#include <bitpunch/code/codectx.h>

#include <bitpunch/crypto/signature/sigctx.h>
#include <bitpunch/code/ldgm/ldgm.h>
#include <bitpunch/math/constwt.h>

int BPU_ldgmSign(BPU_T_UN_Signature *signature, const BPU_T_GF2_Vector *message, const struct _BPU_T_Signature_Ctx *ctx);

int BPU_gf2ToConstantWeight(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, int len, int weight);

int BPU_ldgmVerify(BPU_T_EN_Signature_Verification_Result_Type* result, BPU_T_GF2_Vector *message, const BPU_T_UN_Signature *signature,
    const struct _BPU_T_Signature_Ctx *ctx);

int BPU_ldgmGenKeyPair(struct _BPU_T_Signature_Ctx *sig_ctx);

#endif // LDGMSIG_H 
