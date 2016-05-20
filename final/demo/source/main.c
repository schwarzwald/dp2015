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
#include "bitpunchfile.h"
#include "ldgmdemo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeKeygen(BPU_T_Signature_Ctx *ctx) {
  fprintf(stdout, "Generating keys. This might take a minute...\n");
  BPU_signatureKeyGen(&ctx);
  if (writePrivateKey(LDGM_DEMO_FILE_PRIKEY, ctx->code_ctx->code_spec->ldgm) == FILE_IO_ERROR) {
    fprintf(stdout, "Could not write the private key!\n");
    return;
  }

  if (writePublicKey(LDGM_DEMO_FILE_PUBKEY, ctx->code_ctx->code_spec->ldgm) == FILE_IO_ERROR) {
    fprintf(stdout, "Could not write the public key!\n");
    return;
  }

  fprintf(stdout, "Key pair was successfully generated.\n");
}

char* getSignatureFilename(char* filename) {
  char* sigfilename = (char*) calloc(sizeof(char), strlen(filename) + 4);
  strcpy(sigfilename, filename);
  strcat(sigfilename, ".sig");
  return sigfilename;
}

void executeSignature(BPU_T_Signature_Ctx *ctx, char* filename) {
  BPU_T_UN_Signature signature;
  BPU_T_GF2_Vector *hash;
  BPU_gf2VecMalloc(&hash, 512);
  char* sigfilename = getSignatureFilename(filename);

  if (sha512ToVec(filename, hash) == FILE_IO_ERROR) {
    fprintf(stdout, "Cannot read the input file!\n");
    return;
  }

  if (readPrivateKey(LDGM_DEMO_FILE_PRIKEY, ctx->code_ctx->code_spec->ldgm) == FILE_IO_ERROR) {
    fprintf(stdout, "Cannot read the private key!\n");
    return;
  }

  BPU_signatureSign(&ctx, &signature, hash);

  if (writeSignature(sigfilename, signature.ldgm) == FILE_IO_ERROR) {
    fprintf(stdout, "Could not write the signature!\n");
    return;
  }

  fprintf(stdout, "File %s was successfully signed!\n", filename);
}

void executeVerify(BPU_T_Signature_Ctx *ctx, char* filename) {
  BPU_T_UN_Signature signature;
  BPU_T_EN_Signature_Verification_Result_Type sigresult = BPU_EN_SIG_DISCARD;
  BPU_T_GF2_Vector *hash;

  BPU_gf2VecMalloc(&hash, 512);
  signature.ldgm = (BPU_T_LDGM_Signature*) calloc(sizeof(BPU_T_LDGM_Signature), 1);
  char* sigfilename = getSignatureFilename(filename);

  if (sha512ToVec(filename, hash) == FILE_IO_ERROR) {
    fprintf(stdout, "Cannot read the input file!\n");
    return;
  }

  if (readPublicKey(LDGM_DEMO_FILE_PUBKEY, ctx->code_ctx->code_spec->ldgm) == FILE_IO_ERROR) {
    fprintf(stdout, "Cannot read the public key!\n");
    return;
  }

  if (readSignature(sigfilename, signature.ldgm) == FILE_IO_ERROR) {
    fprintf(stdout, "Cannot read the signature!\n");
    return;
  }

  BPU_signatureVerify(&ctx, &sigresult, hash, &signature);

  if (sigresult == BPU_EN_SIG_ACCEPT) {
    fprintf(stdout, "Signature for the file %s accepted\n", filename);
  } else {
    fprintf(stdout, "Signature for the file %s discarded\n", filename);
  }
}

int main(int argc, char**argv) {
  char* command, *filename;
  BPU_T_Signature_Ctx *ctx = NULL;
  BPU_T_UN_Signature_Params params;
  srand (time(NULL));

  if(argc < 2) {
    fprintf(stderr, "Command not specified\n");
    return -1;
  }

  command = argv[1];

  BPU_ldgmInitParams(&params.ldgm, 153, 77, 64, 2, 1, 9, 20, 18, 8);
  BPU_signatureInitCtx(&ctx, &params, BPU_EN_SIGN_LDGM);

  if (strcmp(command, LDGM_DEMO_KEYGEN) == 0) {
    executeKeygen(ctx);
  }

  if (strcmp(command, LDGM_DEMO_SIGN) == 0) {
    if (argc < 3) {
      fprintf(stderr, "Filename not specified\n");
      return -1;
    }

    filename = argv[2];
    executeSignature(ctx, filename);
  }

  if (strcmp(command, LDGM_DEMO_VERIFY) == 0) {
    if (argc < 3) {
      fprintf(stderr, "Filename not specified\n");
      return -1;
    }

    filename = argv[2];
    executeVerify(ctx, filename);
  }

  return 0;
}
