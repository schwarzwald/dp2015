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
#ifndef BPU_CONSTWT_H
#define BPU_CONSTWT_H

#include <bitpunch/math/gf2types.h>
#include <bitpunch/math/gf2.h>
#include <stdint.h>

/**
 * Function to map input vector to a vector of given length and weight.
 * The weight might be less than wt
 *
 * @param out     output of the mapping
 * @param in      input of the mapping
 * @param wt      weight limit of the output
 */
int BPU_gf2VecToConstantWeight(BPU_T_GF2_Vector *out, BPU_T_GF2_Vector *in, int n, int wt);

#endif // BPU_CONSTWT_H
