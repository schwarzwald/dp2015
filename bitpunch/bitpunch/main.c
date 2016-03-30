/*
 This file is part of BitPunch
 Copyright (C) 2014-2015 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>

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

#include <bitpunch/code/codectx.h>
#include <bitpunch/crypto/signature/sigctx.h>
#include <bitpunch/code/goppa/goppatypes.h>
#include <bitpunch/crypto/mecsctx.h>
#include <bitpunch/debugio.h>
#include <bitpunch/math/gf2.h>
#include <bitpunch/math/gf2types.h>
#include <bitpunch/math/gf2x.h>
#include <bitpunch/math/gf2xtypes.h>
#include <bitpunch/math/permtypes.h>
#include <bitpunch/math/constwt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int testCmpMecsCtx(const BPU_T_Mecs_Ctx *ctx1, const BPU_T_Mecs_Ctx *ctx2) {
  int i, j, rc = 0;
  if (ctx1->type != ctx2->type) {
    BPU_printError("type");
  }
  if (ctx1->ct_len != ctx2->ct_len) {
    BPU_printError("ct_len");
  }
  if (ctx1->pt_len != ctx2->pt_len) {
    BPU_printError("pt_len");
  }
  if (ctx1->_decrypt != ctx2->_decrypt) {
    BPU_printError("_decrypt");
  }
  if (ctx1->_encrypt != ctx2->_encrypt) {
    BPU_printError("_encrypt");
  }
  if (ctx1->code_ctx->code_len != ctx2->code_ctx->code_len) {
    BPU_printError("code_len");
  }
  if (ctx1->code_ctx->msg_len != ctx2->code_ctx->msg_len) {
    BPU_printError("msg_len");
  }
  if (ctx1->code_ctx->t != ctx2->code_ctx->t) {
    BPU_printError("t");
  }
  if (ctx1->code_ctx->type != ctx2->code_ctx->type) {
    BPU_printError("code type");
  }
  if (ctx1->code_ctx->_decode != ctx2->code_ctx->_decode) {
    BPU_printError("_decode");
  }
  if (ctx1->code_ctx->_encode != ctx2->code_ctx->_encode) {
    BPU_printError("_encode");
  }
  if (ctx1->code_ctx->e->len != ctx2->code_ctx->e->len) {
    BPU_printError("e.len");
  }
  if (BPU_gf2xPolyCmp(ctx1->code_ctx->code_spec->goppa->g, ctx2->code_ctx->code_spec->goppa->g)) {
    BPU_printError("g poly");
  }
  if (ctx1->code_ctx->code_spec->goppa->support_len != ctx2->code_ctx->code_spec->goppa->support_len) {
    BPU_printError("support len");
  }
  if (ctx1->code_ctx->code_spec->goppa->permutation->size != ctx2->code_ctx->code_spec->goppa->permutation->size) {
    BPU_printError("perm size");
  }
  if (ctx1->code_ctx->code_spec->goppa->g_mat->elements_in_row != ctx2->code_ctx->code_spec->goppa->g_mat->elements_in_row) {
    BPU_printError("g_mat elements_in_row");
  }
  if (ctx1->code_ctx->code_spec->goppa->g_mat->element_bit_size != ctx2->code_ctx->code_spec->goppa->g_mat->element_bit_size) {
    BPU_printError("g_mat element_bit_size");
  }
  if (ctx1->code_ctx->code_spec->goppa->g_mat->k != ctx2->code_ctx->code_spec->goppa->g_mat->k) {
    BPU_printError("g_mat k");
  }
  if (ctx1->code_ctx->code_spec->goppa->g_mat->n != ctx2->code_ctx->code_spec->goppa->g_mat->n) {
    BPU_printError("g_mat n");
  }
  for (i = 0; i < ctx1->code_ctx->code_spec->goppa->permutation->size; i++) {
    if (ctx1->code_ctx->code_spec->goppa->permutation->elements[i] != ctx2->code_ctx->code_spec->goppa->permutation->elements[i]) {
      BPU_printError("perm diff");
      break;
    }
  }
  if (ctx1->code_ctx->code_spec->goppa->h_mat->k != ctx2->code_ctx->code_spec->goppa->h_mat->k) {
    BPU_printError("h_mat k");
  }
  if (ctx1->code_ctx->code_spec->goppa->h_mat->n != ctx2->code_ctx->code_spec->goppa->h_mat->n) {
    BPU_printError("h_mat n");
  }
  for (i = 0; i < ctx1->code_ctx->code_spec->goppa->g_mat->elements_in_row; i++) {
    for (j = 0; j < ctx1->code_ctx->code_spec->goppa->g_mat->k; j++) {
      if (ctx1->code_ctx->code_spec->goppa->g_mat->elements[j][i] != ctx2->code_ctx->code_spec->goppa->g_mat->elements[j][i]) {
        BPU_printError("g_mat diff");
        j = -1;
        break;
      }
    }
    if (j == -1) {
      break;
    }
  }
  for (i = 0; i < ctx1->code_ctx->code_spec->goppa->h_mat->n; i++) {
    for (j = 0; j < ctx1->code_ctx->code_spec->goppa->h_mat->k; j++) {
      if (ctx1->code_ctx->code_spec->goppa->h_mat->elements[j][i] != ctx2->code_ctx->code_spec->goppa->h_mat->elements[j][i]) {
        BPU_printError("h_mat diff");
        j = -1;
        break;
      }
    }
    if (j == -1) {
      break;
    }
  }
  return rc;
}

int testKeyGenEncDec(BPU_T_Mecs_Ctx *ctx) {
//    BPU_T_Mecs_Ctx *ctx = NULL;
  BPU_T_GF2_Vector *ct, *pt_in, *pt_out;
  int rc = 0;

  /***************************************/
  fprintf(stderr, "Key generation...\n");
  // key pair generation
  if (BPU_mecsGenKeyPair(ctx)) {
//    if (BPU_asn1LoadKeyPair(&ctx, "prikey.der", "pubkey.der")) {
    BPU_printError("Key generation error");

    return 1;
  }
  /***************************************/
  // prepare plain text, allocate memory and init random plaintext
  if (BPU_gf2VecMalloc(&pt_in, ctx->pt_len)) {
    BPU_printError("PT initialisation error");

    return 1;
  }
  BPU_gf2VecRand(pt_in, 0);

  // alocate cipher text vector
  if (BPU_gf2VecMalloc(&ct, ctx->ct_len)) {
    BPU_printError("CT vector allocation error");

    BPU_gf2VecFree(&pt_in);
    return 1;
  }
  // prepare plain text, allocate memory and init random plaintext
  if (BPU_gf2VecMalloc(&pt_out, ctx->pt_len)) {
    BPU_printError("PT out initialisation error");

    return 1;
  }
  BPU_gf2VecRand(pt_out, 0);
  /***************************************/
  fprintf(stderr, "Encryption...\n");
  // BPU_encrypt plain text
  if (BPU_mecsEncrypt(ct, pt_in, ctx)) {
    BPU_printError("Encryption error");

    BPU_gf2VecFree(&ct);
    BPU_gf2VecFree(&pt_in);
    BPU_gf2VecFree(&pt_out);
    return 1;
  }
  // exit(0);
  /***************************************/
  fprintf(stderr, "Decryption...\n");
  // decrypt cipher text
  if (BPU_mecsDecrypt(pt_out, ct, ctx)) {
    BPU_printError("Decryption error");

    BPU_gf2VecFree(&ct);
    BPU_gf2VecFree(&pt_in);
    BPU_gf2VecFree(&pt_out);
    return 1;
  }
  /***************************************/

  // check for correct decryption
  if (BPU_gf2VecCmp(pt_in, pt_out)) {
    BPU_printError("\nOutput plain text differs from input");

    rc = 2;
  } else {
    fprintf(stderr, "\nSUCCESS: Input plain text is equal to output plain text.\n");
  }
  // clean up
  /***************************************/
  fprintf(stderr, "\nCleaning up...\n");
  BPU_gf2VecFree(&pt_in);
  BPU_gf2VecFree(&pt_out);
  BPU_gf2VecFree(&ct);
  return rc;
}

#ifdef BPU_CONF_ASN1
int testKeyGenAsn1() {
  int rc = 0;
  // MUST BE NULL
  BPU_T_Mecs_Ctx *ctx = NULL;
  BPU_T_Mecs_Ctx *ctx_2 = NULL;
  BPU_T_UN_Mecs_Params params;

  /***************************************/
  // mce initialisation t = 50, m = 11
  fprintf(stderr, "Basic GOPPA Initialisation...\n");
  if (BPU_mecsInitParamsGoppa(&params, 11, 50, 0)) {
    return 1;
  }

  if (BPU_mecsInitCtx(&ctx, &params, BPU_EN_MECS_BASIC_GOPPA)) {
//    if (BPU_mecsInitCtx(&ctx, 11, 50, BPU_EN_MECS_CCA2_POINTCHEVAL_GOPPA)) {
    return 1;
  }
  /***************************************/
  fprintf(stderr, "Key generation...\n");
  // key pair generation
  if (BPU_mecsGenKeyPair(ctx)) {
    BPU_printError("Key generation error");

    return 1;
  }
  fprintf(stderr, "ABC");
  rc = BPU_asn1SaveKeyPair(ctx, "prikey.der", "pubkey.der");
  if (rc) {
    asn1_perror(rc);
  }
  rc = BPU_asn1LoadKeyPair(&ctx_2, "prikey.der", "pubkey.der");
  if (rc) {
    asn1_perror(rc);
  }
  testCmpMecsCtx(ctx, ctx_2);

  BPU_mecsFreeCtx(&ctx);
  BPU_mecsFreeCtx(&ctx_2);
  BPU_mecsFreeParamsGoppa(&params);
  return rc;
}
#endif

void testLdgm() {
  BPU_T_Signature_Ctx *ctx = NULL;
  BPU_T_UN_Signature_Params params;
  BPU_T_UN_Signature signature;
  BPU_T_GF2_Vector *message;
  BPU_T_EN_Signature_Verification_Result_Type sigresult;

  BPU_gf2VecMalloc(&message, 100);
  BPU_gf2VecRand(message, 0);
  fprintf(stderr, "init\n");
  BPU_printGf2Vec(message);
  //BPU_ldgmInitParams(&params.ldgm, 15, 5, 3, 1, 3, 1, 5, 5);
  BPU_ldgmInitParams(&params.ldgm, 31, 10, 32, 2, 15, 15, 15, 21, 3);
  BPU_signatureInitCtx(&ctx, &params, BPU_EN_SIGN_LDGM);
  signature.ldgm = (BPU_T_LDGM_Signature*) calloc(sizeof(BPU_T_LDGM_Signature), 1);

  fprintf(stderr, "generating\n");
  ctx->_genKeyPair(ctx->code_ctx, &params);
  fprintf(stderr, "signing\n");
  ctx->_sign(&signature, message, ctx);
  fprintf(stderr, "verifying\n");
  ctx->_verify(&sigresult, message, &signature, ctx);

  if (sigresult == BPU_EN_SIG_ACCEPT) {
    fprintf(stderr, "ACCEPT");
  } else {
    fprintf(stderr, "DISCARD");
  }

  BPU_gf2VecFree(&message);
  //BPU_codeFreeCtx(&ctx->code_ctx);
}

void testSomething() {
  BPU_T_GF2_QC_Matrix mat, tmat, rref, eye, eye2, app, selection, inv, product;
  BPU_T_GF2_Poly *poly, module, *invp;
  BPU_T_GF2_Matrix *a, *b, *c;
  BPU_T_GF2_Vector *vec, *vec_in, vec1;
  int found = 0;
  int i = 0, j = 0;
  int *arr;
  BPU_T_GF2 d;
  BPU_T_Perm_Vector *perm;

  poly = (BPU_T_GF2_Poly*) calloc(sizeof(BPU_T_GF2_Poly), 1);
  invp = (BPU_T_GF2_Poly*) calloc(sizeof(BPU_T_GF2_Poly), 1);
  BPU_gf2PolyMalloc(poly, 3);

  BPU_gf2VecSetBit(poly, 1, 1);

  BPU_gf2PolyMalloc(&module, poly->len + 1);
  BPU_gf2VecSetBit(&module, 0, 1);
  BPU_gf2VecSetBit(&module, poly->len, 1);

  found = BPU_gf2PolyInv(invp, poly, &module);

  //fprintf(stderr, "found %d\n", found);
  //BPU_printGf2Poly(&poly);
  //BPU_printGf2Poly(&invp);

  // srand (time(NULL));
  //BPU_gf2QcMultirowMatrixMalloc(&mat, 3, 3, 3);
  /* BPU_gf2QcEyeMatrix(&eye, 3, 3);

   int block_size = 5;
   int weight_limit = 5;
   int block_count = 5;
   int count = 0;

   while (!found) {
   BPU_gf2QcMultirowMatrixMalloc(&mat, block_count, block_count, block_size);

   for (i = 0; i < block_count * block_count; i++) {
   BPU_gf2PolyInitRand(&mat.matrices[i], block_size, (rand() % weight_limit) + 1, 0);
   }

   found = BPU_gf2QcInvMatrix(&inv, &mat);

   if (!found) {
   BPU_gf2QcMatrixFree(&mat, 0);
   count++;
   }
   }

   //BPU_printGf2QcMatrix(&mat);
   BPU_permMalloc(&perm, block_count);
   BPU_permRandomize(perm);

   for (i = 0; i < block_count; i++) {
   // fprintf(stderr, "%d ", perm->elements[i]);
   }

   BPU_gf2QcPermuteMatrixRows(&mat, perm);
   //BPU_printGf2QcMatrix(&mat);
   //  BPU_printGf2QcMatrix(&eye);
   //fprintf(stderr, "counter %d", count);

   //BPU_gf2QcMatrixVectorMultiply(&vec1, &mat, vec);
   //BPU_gf2QcMatrixGetRow(&vec1, &mat, 7);
   //BPU_gf2VecShiftLeft(vec);
   //i = read(vec, 5);
   //  read(vec, 7);
   //bToCw(vec, arr, 0, 200, 10, 0);
   BPU_gf2VecMalloc(&vec_in, 20);

   BPU_gf2VecMalloc(&vec, 300);
   BPU_gf2VecRand(vec, 0);
   BPU_printGf2Vec(vec);

   BPU_gf2VecToConstantWeight(vec_in, vec, 20, 5);

   BPU_printGf2Vec(vec_in);

   int sum = 0;

   //fprintf(stderr, "\n sum: %d ", sum);

   //BPU_gf2QcMatrixMultiply(&product, &mat, &inv);

   //BPU_gf2VecMalloc(&vec, 33);
   //BPU_printGf2QcMatrix(&product);
   //BPU_gf2MatMalloc(&a, 33, 33);
   //BPU_gf2MatMalloc(&b, 33, 33);
   */
  /*for (i = 0; i < 33; i++) {
   BPU_gf2VecRand(vec, 0);
   for (j = 0; j < vec->elements_in_row; j++) {
   a->elements[i][j] = vec->elements[j];
   b->elements[i][j] = vec->elements[j];
   }
   //   a->elements[i][0] = 1;
   //   a->elements[i][1] = 1 << 31;
   }*/

  /*BPU_printBinaryMsb32(d);
   BPU_gf2MulMat(&c, a, b);

   BPU_printGf2Mat(a);
   BPU_printGf2Mat(b);
   BPU_printGf2Mat(c);*/

  fprintf(stderr, "\n");
}

int main(int argc, char **argv) {
  int rc = 0;
  int i = 0;
  int *arr = (int*) calloc(sizeof(int), 5);
  testLdgm();
  // testSomething();

  return 0;
  // MUST BE NULL
  BPU_T_Mecs_Ctx *ctx = NULL;
  BPU_T_UN_Mecs_Params params;

  srand (time(NULL));
#if !defined(BPU_CONF_GOPPA_WO_H) && defined(BPU_CONF_ASN1)
  testKeyGenAsn1();
#endif

//  /***************************************/
//     // mce initialisation t = 50, m = 11
fprintf  (stderr, "Basic GOPPA Initialisation...\n");
  if (BPU_mecsInitParamsGoppa(&params, 11, 50, 0)) {
    return 1;
  }
  if (BPU_mecsInitCtx(&ctx, &params, BPU_EN_MECS_BASIC_GOPPA)) {
    return 1;
  }
  rc += testKeyGenEncDec(ctx);
  BPU_mecsFreeCtx(&ctx);

#ifdef BPU_CONF_MECS_CCA2_POINTCHEVAL_GOPPA
  fprintf(stderr, "\nCCA2 Pointcheval GOPPA Initialisation...\n");
  if (BPU_mecsInitCtx(&ctx, &params, BPU_EN_MECS_CCA2_POINTCHEVAL_GOPPA)) {
    return 1;
  }
  rc += testKeyGenEncDec(ctx);
  BPU_mecsFreeCtx(&ctx);
  BPU_mecsFreeParamsGoppa(&params);
#endif

// 	/***************************************/
//     mce initialisation of 80-bit security
  fprintf(stderr, "Basic QC-MDPC Initialisation...\n");
  if (BPU_mecsInitParamsQcmdpc(&params, 4801, 2, 90, 84)) {
    return 1;
  }
  if (BPU_mecsInitCtx(&ctx, &params, BPU_EN_MECS_BASIC_QCMDPC)) {
    return 1;
  }
  rc += testKeyGenEncDec(ctx);
  BPU_mecsFreeCtx(&ctx);
  BPU_mecsFreeParamsQcmdpc(&params);

#ifdef BPU_CONF_MECS_CCA2_POINTCHEVAL_GOPPA
  fprintf(stderr, "\nCCA2 Pointcheval QC-MDPC Initialisation...\n");
  if (BPU_mecsInitParamsQcmdpc(&params, 4801, 2, 90, 84)) {
    return 1;
  }
  if (BPU_mecsInitCtx(&ctx, &params, BPU_EN_MECS_CCA2_POINTCHEVAL_QCMDPC)) {
    return 1;
  }
  rc += testKeyGenEncDec(ctx);
  BPU_mecsFreeCtx(&ctx);
  BPU_mecsFreeParamsQcmdpc(&params);
#endif

  return rc;
}
