/*
 * ldgmsigtype.h
 *
 *  Created on: Mar 25, 2016
 *      Author: Bibo
 */

#ifndef BITPUNCH_CRYPTO_SIGNATURE_LDGM_LDGMSIGTYPE_H_
#define BITPUNCH_CRYPTO_SIGNATURE_LDGM_LDGMSIGTYPE_H_

typedef struct _BPU_T_LDGM_Signature {
  BPU_T_GF2_Vector *signature;
  uint16_t counter;
} BPU_T_LDGM_Signature;

#endif /* BITPUNCH_CRYPTO_SIGNATURE_LDGM_LDGMSIGTYPE_H_ */
