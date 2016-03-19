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

#ifndef BPU_LDGM_H
#define BPU_LDGM_H

#include <bitpunch/config.h>
#include <bitpunch/code/codectx.h>
#include <bitpunch/math/gf2.h>
#include <bitpunch/debugio.h>

/**
 * McEliece QC-MDPC encode
 * @param  out         	cipher text
 * @param  in     	   	message
 * @param  ctx 			QC-MDPC McEliece context
 * @return             	0 if OK, else error
 */
int BPU_ldgmEncode(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx);

/**
 * McEliece QC-MDPC decrypt
 * @param  out         	message
 * @param  in     	   	cipher text
 * @param  ctx 			QC-MDPC McEliece context
 * @return              0 if OK, else error
 */
int BPU_ldgmDecode(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *in, const struct _BPU_T_Code_Ctx *ctx);

#ifdef BPU_CONF_KEY_GEN
/**
 * Generate key pair of QC-MDPC code for McEliece cryptosystem.
 * Generator matrix G is not sparse. Its public key.
 * Parity-check matrix H is in sparse form. Its private key.
 * Params of code are set as global constants in crypto.h header file.
 * @param ctx 		QC-MDPC McEliece context
 * @return          0 if OK, else error
 */
int BPU_ldgmGenKeys(BPU_T_Code_Ctx *ctx);
#endif

#endif // BPU_LDGM_H
