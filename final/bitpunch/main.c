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
#include <bitpunch/math/gf2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void testLdgm() {
  BPU_T_Signature_Ctx *ctx = NULL;
  BPU_T_UN_Signature_Params params;
  BPU_T_UN_Signature signature;
  BPU_T_GF2_Vector *message;
  BPU_T_EN_Signature_Verification_Result_Type sigresult;
  BPU_gf2VecMalloc(&message, 100);
  BPU_gf2VecRand(message, 0);
  BPU_ldgmInitParams(&params.ldgm, 312, 125, 80, 2, 1, 14, 25, 23, 13);
  BPU_signatureInitCtx(&ctx, &params, BPU_EN_SIGN_LDGM);

  LARGE_INTEGER frequency;
  LARGE_INTEGER start;
  LARGE_INTEGER end;
  double interval;

  //Generating
  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&start);
  BPU_signatureKeyGen(&ctx);
  QueryPerformanceCounter(&end);
  interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
  fprintf(stderr, "%f, ", interval);

  //Signing
  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&start);
  BPU_signatureSign(&ctx, &signature, message);
  QueryPerformanceCounter(&end);
  interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
  fprintf(stderr, "%f, ", interval);

  //Verifying
  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&start);
  BPU_signatureVerify(&ctx, &sigresult, message, &signature);
  QueryPerformanceCounter(&end);
  interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
  fprintf(stderr, "%f, ", interval);

  if (sigresult == BPU_EN_SIG_ACCEPT) {
    fprintf(stderr, "ACCEPT\n");
  } else {
    fprintf(stderr, "DISCARD\n");
  }

  fflush (stderr);

  BPU_gf2VecFree(&message);
  BPU_signatureFreeCtx(&ctx);
  free(signature.ldgm);
}

int testInv(int block_count, int block_size) {
  BPU_T_GF2_QC_Matrix mat, inv;
  int found = 0;
  int i = 0;

  BPU_gf2QcMultirowMatrixMalloc(&mat, block_count, block_count, block_size);

  for (i = 0; i < block_count * block_count; i++) {
    BPU_gf2PolyInitRand(&mat.matrices[i], block_size, 0, 0);
  }

  found = BPU_gf2QcInvMatrix(&inv, &mat);

  BPU_gf2QcMatrixFree(&mat, 0);
  if (found) {
    BPU_gf2QcMatrixFree(&inv, 0);
  }

  return found;
}

int main(int argc, char **argv) {
  int i = 0, j, k, total = 100, f = 0;
  int block_count = 5, block_size = 4;
  double interval = 0, found = 0;
  LARGE_INTEGER frequency;
  LARGE_INTEGER start;
  LARGE_INTEGER end;
  srand (time(NULL));QueryPerformanceFrequency
  (&frequency);
  fprintf(stderr, "size, block_size, success, time\n");
  for (j = 0; j < 100; j += 2) {
    for (k = 0; k < 50; k += 1) {
      found = 0;
      interval = 0;
      for (i = 0; i < total; i++) {
        QueryPerformanceCounter(&start);
        f = testInv(block_count + j, block_size + k);
        QueryPerformanceCounter(&end);

        if (f) {
          found += 1;
          interval += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
        }
      }

      fprintf(stderr, "%d, %d, %f, %f\n", block_count + j, block_size + k, found / total, interval / found);
      fflush (stderr);
    }
  }

  return 0;
}
