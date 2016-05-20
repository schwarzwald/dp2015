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
#ifndef BITPUNCH_CRYPTO_SIGNATURE_LDGM_LDGMSIGTYPE_H_
#define BITPUNCH_CRYPTO_SIGNATURE_LDGM_LDGMSIGTYPE_H_

typedef struct _BPU_T_LDGM_Signature {
  BPU_T_GF2_Vector *signature;
  uint16_t counter;
} BPU_T_LDGM_Signature;

#endif /* BITPUNCH_CRYPTO_SIGNATURE_LDGM_LDGMSIGTYPE_H_ */
