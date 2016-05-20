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
#ifndef DEMO_BITPUNCHFILE_H_
#define DEMO_BITPUNCHFILE_H_

#include <bitpunch/math/gf2.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_IO_SUCCESS 0
#define FILE_IO_ERROR -1

#define FILE_IO_CHECK(actual, expected) if ((actual) != (expected)) return FILE_IO_ERROR

int writeGf2Vector(FILE* file, BPU_T_GF2_Vector* vec);

int readGf2Vector(FILE* file, BPU_T_GF2_Vector* vec);

int writeGf2QcMatrix(FILE* file, BPU_T_GF2_QC_Matrix* mat);

int readGf2QcMatrix(FILE* file, BPU_T_GF2_QC_Matrix* mat);

int writeGf2Matrix(FILE* file, BPU_T_GF2_Matrix* mat);

int readGf2Matrix(FILE* file, BPU_T_GF2_Matrix* mat);

#endif /* DEMO_BITPUNCHFILE_H_ */
