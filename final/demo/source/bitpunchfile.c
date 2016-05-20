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

int writeGf2Vector(FILE* file, BPU_T_GF2_Vector* vec) {
  BPU_T_GF2_Vector vcopy = *vec;
  vcopy.elements = NULL;

  FILE_IO_CHECK(fwrite(&vcopy, sizeof(BPU_T_GF2_Vector), 1, file), 1);
  FILE_IO_CHECK(fwrite(vec->elements, sizeof(BPU_T_GF2), vec->elements_in_row, file), vec->elements_in_row);

  return FILE_IO_SUCCESS;
}

int readGf2Vector(FILE* file, BPU_T_GF2_Vector* vec) {
  FILE_IO_CHECK(fread(vec, sizeof(BPU_T_GF2_Vector), 1, file), 1);
  vec->elements = (BPU_T_GF2*) calloc(sizeof(BPU_T_GF2), vec->elements_in_row);
  FILE_IO_CHECK(fread(vec->elements, sizeof(BPU_T_GF2), vec->elements_in_row, file), vec->elements_in_row);

  return FILE_IO_SUCCESS;
}

int writeGf2QcMatrix(FILE* file, BPU_T_GF2_QC_Matrix* mat) {
  BPU_T_GF2_QC_Matrix mcopy = *mat;
  mcopy.matrices = NULL;
  int i;

  FILE_IO_CHECK(fwrite(&mcopy, sizeof(BPU_T_GF2_QC_Matrix), 1, file), 1);

  for (i = 0; i < mat->column_element_count * mat->row_element_count; i++) {
    if (writeGf2Vector(file, &mat->matrices[i]) == FILE_IO_ERROR) {
      return FILE_IO_ERROR;
    }
  }

  return FILE_IO_SUCCESS;
}

int readGf2QcMatrix(FILE* file, BPU_T_GF2_QC_Matrix* mat) {
  int i;

  FILE_IO_CHECK(fread(mat, sizeof(BPU_T_GF2_QC_Matrix), 1, file), 1);
  mat->matrices = (BPU_T_GF2_Poly*) calloc(sizeof(BPU_T_GF2_Poly), mat->column_element_count * mat->row_element_count);

  for (i = 0; i < mat->column_element_count * mat->row_element_count; i++) {
    if (readGf2Vector(file, &mat->matrices[i]) == FILE_IO_ERROR) {
      return FILE_IO_ERROR;
    }
  }

  return FILE_IO_SUCCESS;
}

int writeGf2Matrix(FILE* file, BPU_T_GF2_Matrix* mat) {
  BPU_T_GF2_Matrix mcopy = *mat;
  mcopy.elements = NULL;
  int i;

  FILE_IO_CHECK(fwrite(&mcopy, sizeof(BPU_T_GF2_Matrix), 1, file), 1);

  for (i = 0; i < mat->k; i++) {
    FILE_IO_CHECK(fwrite(mat->elements[i], sizeof(BPU_T_GF2), mat->elements_in_row, file), mat->elements_in_row);
  }

  return FILE_IO_SUCCESS;
}

int readGf2Matrix(FILE* file, BPU_T_GF2_Matrix* mat) {
  int i;
  FILE_IO_CHECK(fread(mat, sizeof(BPU_T_GF2_Matrix), 1, file), 1);
  mat->elements = (BPU_T_GF2**) calloc(sizeof(BPU_T_GF2*), mat->k);

  for (i = 0; i < mat->k; i++) {
    mat->elements[i] = (BPU_T_GF2*) calloc(sizeof(BPU_T_GF2), mat->elements_in_row);
    FILE_IO_CHECK(fread(mat->elements[i], sizeof(BPU_T_GF2), mat->elements_in_row, file), mat->elements_in_row);
  }

  return FILE_IO_SUCCESS;
}
