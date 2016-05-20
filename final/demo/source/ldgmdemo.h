/*
 This file is part of BitPunch LDGM Demo
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
#ifndef DEMO_LDGMDEMO_H_
#define DEMO_LDGMDEMO_H_

#include "bitpunchfile.h"

#include <bitpunch/code/ldgm/ldgmtypes.h>
#include <bitpunch/crypto/signature/sigctx.h>
#include <bitpunch/crypto/hash/polarssl/polarssl/sha512.h>

#define LDGM_DEMO_KEYGEN  "keygen"
#define LDGM_DEMO_SIGN    "sign"
#define LDGM_DEMO_VERIFY  "verify"

#define LDGM_DEMO_FILE_PUBKEY "ldgm80key.pub"
#define LDGM_DEMO_FILE_PRIKEY "ldgm80key.pri"

int writePrivateKey(char* filename, BPU_T_LDGM_Spec* spec);

int readPrivateKey(char* filename, BPU_T_LDGM_Spec* spec);

int writePublicKey(char* filename, BPU_T_LDGM_Spec* spec);

int readPublicKey(char* filename, BPU_T_LDGM_Spec* spec);

int writeSignature(char* filename, BPU_T_LDGM_Signature* signature);

int readSignature(char* filename, BPU_T_LDGM_Signature* signature);

int sha512ToVec(char* filename, BPU_T_GF2_Vector* hash);

#endif /* DEMO_LDGMDEMO_H_ */
