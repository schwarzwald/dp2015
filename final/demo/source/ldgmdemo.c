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
#include "ldgmdemo.h"

int _writePrivateKey(FILE* file, BPU_T_LDGM_Spec* spec) {
  int result;

  result = writeGf2QcMatrix(file, spec->g_mat);
  result += writeGf2QcMatrix(file, spec->q_mat);
  result += writeGf2QcMatrix(file, spec->s_mat);
  result += writeGf2Matrix(file, spec->b_mat);

  return result;
}

int writePrivateKey(char* filename, BPU_T_LDGM_Spec* spec) {
  FILE* f = fopen(filename, "wb");
  int result = (f == NULL) ? FILE_IO_ERROR : _writePrivateKey(f, spec);
  fclose(f);
  return result;
}

int _readPrivateKey(FILE* file, BPU_T_LDGM_Spec* spec) {
  int result;

  spec->q_mat = (BPU_T_GF2_QC_Matrix*) calloc(sizeof(BPU_T_GF2_QC_Matrix), 1);
  spec->s_mat = (BPU_T_GF2_QC_Matrix*) calloc(sizeof(BPU_T_GF2_QC_Matrix), 1);
  spec->g_mat = (BPU_T_GF2_QC_Matrix*) calloc(sizeof(BPU_T_GF2_QC_Matrix), 1);
  spec->b_mat = (BPU_T_GF2_Matrix*) calloc(sizeof(BPU_T_GF2_Matrix), 1);

  result = readGf2QcMatrix(file, spec->g_mat);
  result += readGf2QcMatrix(file, spec->q_mat);
  result += readGf2QcMatrix(file, spec->s_mat);
  result += readGf2Matrix(file, spec->b_mat);

  return result;
}

int readPrivateKey(char* filename, BPU_T_LDGM_Spec* spec) {
  FILE* f = fopen(filename, "rb");
  int result = (f == NULL) ? FILE_IO_ERROR : _readPrivateKey(f, spec);
  fclose(f);
  return result;
}

int _writePublicKey(FILE* file, BPU_T_LDGM_Spec* spec) {
  return writeGf2QcMatrix(file, spec->h_mat);
}

int writePublicKey(char* filename, BPU_T_LDGM_Spec* spec) {
  FILE* f = fopen(filename, "wb");
  int result = (f == NULL) ? FILE_IO_ERROR : _writePublicKey(f, spec);
  fclose(f);
  return result;
}

int _readPublicKey(FILE* file, BPU_T_LDGM_Spec* spec) {
  spec->h_mat = (BPU_T_GF2_QC_Matrix*) calloc(sizeof(BPU_T_GF2_QC_Matrix), 1);
  return readGf2QcMatrix(file, spec->h_mat);
}

int readPublicKey(char* filename, BPU_T_LDGM_Spec* spec) {
  FILE* f = fopen(filename, "rb");
  int result = (f == NULL) ? FILE_IO_ERROR : _readPublicKey(f, spec);
  fclose(f);
  return result;
}

int _writeSignature(FILE* file, BPU_T_LDGM_Signature* signature) {
  BPU_T_LDGM_Signature scopy = *signature;
  scopy.signature = NULL;
  FILE_IO_CHECK(fwrite(&scopy, sizeof(BPU_T_LDGM_Signature), 1, file), 1);
  return writeGf2Vector(file, signature->signature);
}

int writeSignature(char* filename, BPU_T_LDGM_Signature* signature) {
  FILE* f = fopen(filename, "wb");
  int result = (f == NULL) ? FILE_IO_ERROR : _writeSignature(f, signature);
  fclose(f);
  return result;
}

int _readSignature(FILE* file, BPU_T_LDGM_Signature* signature) {
  FILE_IO_CHECK(fread(signature, sizeof(BPU_T_LDGM_Signature), 1, file), 1);
  signature->signature = (BPU_T_GF2_Vector*) calloc(sizeof(BPU_T_GF2_Vector), 1);
  return readGf2Vector(file, signature->signature);
}

int readSignature(char* filename, BPU_T_LDGM_Signature* signature) {
  FILE* f = fopen(filename, "rb");
  int result = (f == NULL) ? FILE_IO_ERROR : _readSignature(f, signature);
  fclose(f);
  return result;
}

int sha512ToVec(char* filename, BPU_T_GF2_Vector* vec) {
  uint8_t md[64];
  if (sha512_file(filename, md, 0) != 0) {
    return FILE_IO_ERROR;
  }
  memcpy(vec->elements, md, 64);
  return FILE_IO_SUCCESS;
}
