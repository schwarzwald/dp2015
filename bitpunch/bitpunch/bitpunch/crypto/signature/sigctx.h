/*This file is part of BitPunchCopyright (C) 2015 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>Copyright (C) 2015 Andrej Gulyas <andrej.guly[what here]gmail.com>This program is free software: you can redistribute it and/or modifyit under the terms of the GNU General Public License as published bythe Free Software Foundation, either version 3 of the License, or(at your option) any later version.This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See theGNU General Public License for more details.You should have received a copy of the GNU General Public Licensealong with this program.  If not, see <http://www.gnu.org/licenses/>.*/#ifndef SIGCTX_H#define SIGCTX_H#include <bitpunch/config.h>#include <bitpunch/math/gf2.h>#include <bitpunch/code/codectx.h>#include <bitpunch/crypto/signature/ldgm/ldgmsig.h>/// Possible types of MECStypedef enum _BPU_T_EN_Signature_Types {    BPU_EN_SIGN_LDGM ///< LDGM Digital signature algorithm}BPU_T_EN_Signature_Types;typedef enum _BPU_T_EN_Signature_Verification_Result_Type {	BPU_EN_SIG_ACCEPT,	BPU_EN_SIG_DISCARD}BPU_T_EN_Signature_Verification_Result_Type;typedef union _BPU_UN_Signature {	//BPU_T_LDGM_Signature *ldgm;}BPU_UN_Signature;typedef struct _BPU_T_Signature_Ctx {	BPU_T_EN_Signature_Types type;	int (* _sign)(BPU_UN_Signature *signature, const BPU_T_GF2_Vector *message, const struct _BPU_T_Signature_Ctx *ctx);	int (* _verify)(BPU_T_EN_Signature_Verification_Result_Type* result, BPU_T_GF2_Vector *message, const BPU_UN_Signature *signature, const struct _BPU_T_Signature_Ctx *ctx);	int (* _genKeyPair)(struct _BPU_T_Code_Ctx *ctx);	BPU_T_Code_Ctx *code_ctx;}BPU_T_Signature_Ctx;typedef union _BPU_T_UN_Code_Params BPU_T_UN_Signature_Params;/// Initialize (register) mecs functions for encryption, decryption and key gen based on type.int BPU_signatureInitCtx(BPU_T_Signature_Ctx **ctx, const BPU_T_UN_Signature_Params *params, const BPU_T_EN_Signature_Types type);int BPU_signatureFreeCtx(BPU_T_Signature_Ctx **ctx);// Available init params for all codes, it is only wrapper for code params init//int BPU_mecsInitParamsGoppa(BPU_T_UN_Mecs_Params *params, const uint16_t m, const uint16_t t, const BPU_T_GF2_16x mod);//void BPU_mecsFreeParamsGoppa(BPU_T_UN_Mecs_Params *params);#endif // SIGCTX_H