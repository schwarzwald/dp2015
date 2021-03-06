/*
 This file is part of BitPunch
 Copyright (C) 2013-2015 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>
 Copyright (C) 2013-2015 Andrej Gulyas <andrej.guly[what here]gmail.com>
 Copyright (C) 2013-2014 Marek Klein  <kleinmrk[what here]gmail.com>
 Copyright (C) 2013-2014 Filip Machovec  <filipmachovec[what here]yahoo.com>
 Copyright (C) 2013-2014 Jozef Kudlac <jozef[what here]kudlac.sk>

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
#ifndef BPU_GF2_H
#define BPU_GF2_H

#include <bitpunch/math/gf2types.h>
#include <bitpunch/math/permtypes.h>
#include <stdint.h>

//#ifdef BPU_CONF_PRINT
/* ==================================== Print functions ==================================== */
// TODO: Be enable to turn off print function, to not compile in in code
/**
 * Print number as binary string in big endian so msb is first printed. Do not print new line at the end.
 * Example: number 21 -> 0001 0101
 * @param in input of max 64 bits
 * @param len print len
 */
/// Print number as binary string in big endian so msb is first printed.
void BPU_printBinaryMsb(uint32_t in, int len);

/**
 * Print number as binary string in big endian so msb is first printed. Print also new line at the end.
 * Example: number 21 -> 0001 0101
 * @param in input of max 64 bits
 * @param len print len
 */
/// Print number as binary string in big endian so msb is first printed.
void BPU_printBinaryMsbLn(uint32_t in, int len);

/**
 * Print number as binary string in big endian so msb is first printed. Do not print new line at the end.
 * Example: number 21 -> 0001 0101
 * It will be padded to 64 bits.
 * @param in input of max 64 bits
 */
/// Print number as binary string in big endian so msb is first printed.
void BPU_printBinaryMsb32(uint32_t in);

/**
 * Print number as binary string in big endian so msb is first printed. Print also new line at the end.
 * Example: number 21 -> 0001 0101
 * It will be padded 64 bits.
 * @param in input of max 64 bits
 */
/// Print number as binary string in big endian so msb is first printed.
void BPU_printBinaryMsb32Ln(uint32_t in);

/**
 * Print number as binary string in little endian so lsb is first printed. Do not print new line at the end.
 * Example: number 21 -> 1010 1000
 * @param in input of max 64 bits
 * @param len print len
 */
/// Print number as binary string in little endian so lsb is first printed.
void BPU_printBinaryLsb(uint32_t in, int len);

/**
 * Print number as binary string in little endian so lsb is first printed. Print also new line at the end.
 * Example: number 21 -> 1010 1000
 * @param in input of max 64 bits
 * @param len print len
 */
/// Print number as binary string in little endian so lsb is first printed.
void BPU_printBinaryLsbLn(uint32_t in, int len);

/**
 * Print number as binary string in little endian so lsb is first printed. Do not print new line at the end.
 * Example: number 21 -> 1010 1000
 * It will be padded to 64 bits.
 * @param in input of max 64 bits
 */
/// Print number as binary string in little endian so lsb is first printed.
void BPU_printBinaryLsb32(uint32_t in);

/**
 * Print number as binary string in little endian so lsb is first printed. Print also new line at the end.
 * Example: number 21 -> 1010 1000
 * It will be padded 64 bits.
 * @param in input of max 64 bits
 */
/// Print number as binary string in little endian so lsb is first printed.
void BPU_printBinary32LsbLn(uint32_t in);

/**
 * Print matrix GF2 with new lines.
 * @param m matrix
 */
void BPU_printGf2Mat(const BPU_T_GF2_Matrix *m);

/**
 * Print vector GF2 with new line.
 * @param v vector
 */
void BPU_printGf2Vec(const BPU_T_GF2_Vector *v);

/**
 * @brief BPU_printGf2VecMsb Most significant bit is printed first.
 * @param v
 */
void BPU_printGf2VecMsb(const BPU_T_GF2_Vector* v);

/**
 * @brief BPU_printGf2VecOnes Print only ones.
 * @param vec
 */
void BPU_printGf2VecOnes(const BPU_T_GF2_Vector *vec);

/**
 * Print sparse polynomial.
 * @param v sparse polynomial to print
 */
void BPU_printGf2SparsePoly(const BPU_T_GF2_Sparse_Poly *v);

/**
 * Print polynomial over GF2 for matrix.
 * Without header and new line.
 * @param v polynomial to print
 */
void BPU_printGf2PolyForMatrix(const BPU_T_GF2_Poly* v);

/**
 * Print polynomial.
 * @param v polynomial to print
 */
void BPU_printGf2Poly(const BPU_T_GF2_Poly* v);

/**
 * Print quasi-cyclic matrix.
 * @param v quasi-cyclic matrix to print
 */
void BPU_printGf2QcMatrix(const BPU_T_GF2_QC_Matrix *v);

/**
 * Print sparse quasi-cyclic matrix.
 * @param v sparse quasi-cyclic matrix to print
 */
void BPU_printGf2SparseQcMatrix(const BPU_T_GF2_Sparse_Qc_Matrix *v);

/* ------------------------------------ Print functions ------------------------------------ */
//#endif // BPU_CONF_PRINT
/**
 * Check if is set bit at n-th index makro.
 * @param w bit word to check
 * @param n index of bit to check, starts from 0
 * @return 1 - is set, else zero
 */
/// Check if is set bit at n-th index.
#define BPU_getBit(w, n) ((int)((((uint32_t)w) >> (n)) & 1u))

/**
 * Check if is set bit at s, t position in matrix.
 * @param m_pointer GF2 matrix address
 * @param s is row
 * @param t is col
 * @return 1 - is set, else zero
 */
/// Check if is set bit at s, t position in matrix.
#define BPU_gf2MatGetBit(m_pointer, s, t) (BPU_getBit((m_pointer)->elements[s][(t) / (m_pointer)->element_bit_size], (t) % (m_pointer)->element_bit_size))

/**
 * Check if is set bit at s, t position in vector.
 * @param v_pointer GF2 vector address
 * @param t is col
 * @return 1 - is set, else zero
 */
/// Check if is set bit at i-th position in vector.
#define BPU_gf2VecGetBit(v_pointer, i) (BPU_getBit((v_pointer)->elements[(i) / (v_pointer)->element_bit_size], (i) % (v_pointer)->element_bit_size))

/**
 * Set bit in matrix GF2 at index s, t
 * @param  m_pointer address to matrix GF2
 * @param  s         row
 * @param  i         col index
 * @param  bit       bit value 0 or 1
 */
#define BPU_gf2MatSetBit(m_pointer, s, t, bit)  if (bit) { \
												(m_pointer)->elements[s][(t) / (m_pointer)->element_bit_size] |= ((BPU_T_GF2) 1) << ((t) % (m_pointer)->element_bit_size);\
												} \
												else { \
													/* this is like: 00101111 ^ 00000100 = 00101011 */\
													(m_pointer)->elements[s][(t) / (m_pointer)->element_bit_size] &= ((BPU_T_GF2) (0xFFFFFFFFu)) ^ (((BPU_T_GF2) 1) << ((t) % (m_pointer)->element_bit_size));\
												}

/**
 * Set bit in vector GF2 at index i
 * @param  v_pointer address to matrix GF2
 * @param  i         col index
 * @param  bit       bit value 0 or 1
 */
#define BPU_gf2VecSetBit(v_pointer, i, bit)  if (bit) { \
												(v_pointer)->elements[(i) / (v_pointer)->element_bit_size] |= ((BPU_T_GF2) 1) << ((i) % (v_pointer)->element_bit_size);\
												} \
												else { \
													/* this is like: 00101111 ^ 00000100 = 00101011 */\
													(v_pointer)->elements[(i) / (v_pointer)->element_bit_size] &= ((BPU_T_GF2) (0xFFFFFFFFu)) ^ (((BPU_T_GF2) 1) << ((i) % (v_pointer)->element_bit_size));\
												}

/**
 * Copy Matrix GF2 row to Vector GF2.
 * @param v_pointer[out] pointer to GF2 vector  
 * @param m_pointer[in] pointer to GF2 matrix 
 * @param row[in] row index
 */
/// Copy Matrix GF2 row to Vector GF2.
#define BPU_gf2MatCopyRowToVec(v_pointer, m_pointer, row) memcpy((void *) ((v_pointer)->elements), (void *) ((m_pointer)->elements[row]), (v_pointer)->element_bit_size / 8 * (v_pointer)->elements_in_row)

/**
 * Check if is set coeff with index bit in poly.
 * @param  poly polynomial
 * @param  bit  index of coefficient
 * @return      1 if is set bit, else 0
 */
#define BPU_gf2PolyGetBit(poly, bit) ((poly->elements[bit/poly->element_bit_size] >> (bit%poly->element_bit_size)) & 1ul)

/**
 * @brief BPU_gf2MatCopyCreate copy of input matrix.
 * @param out
 * @param in
 * @return
 */
int BPU_gf2MatCopy(BPU_T_GF2_Matrix *out, const BPU_T_GF2_Matrix *in);

/**
 * Permute matrix GF2 with permutation.
 * @param m matrix GF2
 * @param permutation permutation vector
 * @return on succes 0, on size error -1, on allocation error -2
 */
int BPU_gf2MatPermute(BPU_T_GF2_Matrix *m, BPU_T_Perm_Vector *permutation);

/**
 * Permute vector GF2 with permutation.
 * @param vec vector GF2
 * @param permutation permutation vector
 * @return on succes 0, on size error -1, on allocation error -2
 */
int BPU_gf2VecPermute(BPU_T_GF2_Vector *vec, const BPU_T_Perm_Vector *permutation);

/**
 * Get masked bit from exact row of Matrix GF2
 * @param m matrix GF2
 * @param row row
 * @param bit bit
 * @return masked bit
 */
BPU_T_GF2 BPU_gf2MatGetMaskedBit(const BPU_T_GF2_Matrix *m, uint32_t row, uint32_t bit);

/**
 * Get masked bit from Vector GF2
 * @param vec vector GF2
 * @param bit bit
 * @return masked bit
 */
BPU_T_GF2 BPU_gf2VecGetMaskedBit(const BPU_T_GF2_Vector *vec, uint32_t bit);

/**
 * Transpose GF2 Matrix.
 * @param  out transposed GF2 matrix
 * @param  in  matrix to transpose
 * @return     on success 0, else error
 */
int BPU_gf2MatTransp(BPU_T_GF2_Matrix *out, const BPU_T_GF2_Matrix *in);

/**
 * Swaps GF2 elements.
 * @param a pointer to GF2 element
 * @param b pointer to GF2 element 
 * @return
 */
void BPU_gf2Swap(BPU_T_GF2 *a, BPU_T_GF2 *b);

/**
 * It swaps i-th and j-th rows of Matrix GF2.
 * @param  mat Matrix GF2
 * @param  int i
 * @param  int j
 * @return permutation needed for equivalent codes
 */
void BPU_gf2MatSwapRows(BPU_T_GF2_Matrix *mat, int i, int j);

/**
 * Finds row in Matrix GF2 where 1 is at i-th position (from left). Looking for row starts at start_index.
 * @param  mat Matrix GF2
 * @param  i int
 * @param  start_index int
 * @return number of row on success, else -1 
 */
int BPU_gf2MatFindRow(const BPU_T_GF2_Matrix *mat, int i, int start_index);

/**
 * Finds column in Matrix GF2 where 1 is at i-th position (from top). Looking for column starts at start_index.
 * @param  mat Matrix GF2
 * @param  i int
 * @param  start_index int
 * @return number of row on success, else -1 
 */
int BPU_gf2MatFindCol(const BPU_T_GF2_Matrix *mat, int i, int start_index);

/**
 * It brings Matrix GF2 into the systematic form -> with I on the left side. After work, return value should be freed, it is allocated dynamically.
 * @param  inout Matrix GF2
 * @return       on success pointer to BPU_T_Perm_Vector
 */
/// It brings Matrix GF2 into the systematic form -> with I on the left side.
int BPU_gf2MatMakeSystematic(BPU_T_GF2_Matrix *inout);

int BPU_gf2MulMat(BPU_T_GF2_Matrix **out, BPU_T_GF2_Matrix *left, BPU_T_GF2_Matrix *right);
/**
 * Concats two vectors without allocation ouput.
 * @param  vec1 first vector
 * @param  vec2 second vector
 * @param  out  output vector - concat of vec1 and vec2, it allocates vector inside function, should be freed after use BPU_freeVecGF2()
 * @return    0 - succes, else error
 */
/// Concats two vectors without allocation ouput.
int BPU_gf2VecConcat(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *vec1, const BPU_T_GF2_Vector *vec2);

/**
 * Crop the vector
 * @param  out    output vector
 * @param  in     input vector
 * @param  start  starting position in vector
 * @param  length count of bits of cropped vector
 * @return    0 - succes, else error
 */
int BPU_gf2VecCrop(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *in, const int start, const int length);

int BPU_gf2VecShiftLeft(BPU_T_GF2_Vector *in);

int BPU_gf2VecIsZero(BPU_T_GF2_Vector *in);

int BPU_gf2VecGetWeight(BPU_T_GF2_Vector *in);

int BPU_gf2VecShiftRead(BPU_T_GF2_Vector *in, int bits_to_read);
/**
 * Get matrix GF2 row as vector gf2. You can set alloc param, to allocate it dynamically inside function, or use allocated vector yet. When set alloc, after work call BPU_freeVecGF2
 * @param  out   vector
 * @param  in    matrix
 * @param  row   row index
 * @param  alloc if set to 0, jsut copy row to allocated vector yet, or also allocate output vector
 * @return       0 - success, else error
 */
int BPU_gf2MatGetRowAsGf2Vec(BPU_T_GF2_Vector *out, const BPU_T_GF2_Matrix *in, int row);

/**
 * Copy VectorGF2.
 * @param dest[out] pointer to VectorGF2
 * @param src[in] pointer to VectorGF2  
 */
/// Copy VectorGF2.
void BPU_gf2VecCopy(BPU_T_GF2_Vector *dest, const BPU_T_GF2_Vector *src);

/**
 * @brief BPU_gf2VecCmp Compare two vectors.
 * @param v1
 * @param v2
 * @return 0 - same, -1 - len differs, > 0 (index + 1) of first difference
 */
int BPU_gf2VecCmp(const BPU_T_GF2_Vector *v1, const BPU_T_GF2_Vector *v2);

/**
 * XOR operation on rows of Matrix GF2. row[i] = row[i] ^ row[j]
 * @param  mat Matrix GF2
 * @param  int i
 * @param  int j
 * @return
 */
void BPU_gf2MatXorRows(BPU_T_GF2_Matrix *mat, int i, int j);

/**
 * Xor two Vectors GF2 and store result in first vector.
 * @param out[out] vector, where will be stored result
 * @param in[in]  vector
 * @return 0 - successm else error
 */
/// Xor two Vectors GF2 and store result in first vector.
int BPU_gf2VecXor(BPU_T_GF2_Vector *out, const BPU_T_GF2_Vector *in);

/**
 * Create a binary vector of required length and weight. After work call BPU_freeVecGF2
 * @param  out GF2 vector representation (L)
 * @param  w weight of vector, if 0 weight is random
 * @return     0 - succes, else error
 */
int BPU_gf2VecRand(BPU_T_GF2_Vector *out, int w);

/**
 * Vector and matrix multiplication over GF2.
 * x = v * b, vector is in 'line' format like [010111010001]. It selects i-th row from matrix b and xor it together, when vector v has at i-th column 1.  After work you have to free memory using call BPU_freeMat
 * @param[out] x vector GF2, it is matrix k = 1, n = length of vec, new vector (matrix)
 * @param[in] v vector GF2, it is matrix k = 1, n = length of vec
 * @param[in] b matrix GF2
 * @return on succes 0, on size error -1, on allocation error -2
 */
int BPU_gf2VecMulMat(BPU_T_GF2_Vector *x, const BPU_T_GF2_Vector *v, const BPU_T_GF2_Matrix *b);

/**
 * Crop matrix GF2 from left.
 * @param in input matrix GF2
 * @param out croped output matrix GF2
 * @param width width of cropped matrix
 * @return on succes 0, on higher or equal width as actual width of in matrix -1, on allocation of new matrix error -2
 */
/// Crop matrix GF2 from left.
int BPU_gf2MatCrop(BPU_T_GF2_Matrix *m, uint16_t width);

/**
 * @brief BPU_getParity Get parity of word.
 * @param dword
 * @return
 */
uint8_t BPU_getParity(BPU_T_GF2 dword);

/************************************************
 POLYNOMIAL UTILS
 ************************************************/

/**
 * Is poly zero?
 * @param  a poly
 * @return   if 1, poly is zero, else 0
 */
int BPU_gf2PolyIsZero(const BPU_T_GF2_Poly *a);

/**
 * Find highest coefficient in polynomial and set degree.
 * Reallocating new size.
 * @param a   poly
 * @param deg if -1, set degree = max poly degree, else set given degree
 */
void BPU_gf2PolySetDeg(BPU_T_GF2_Poly *a, int deg);

/**
 * Returns highest set coefficient in polynomial.
 * @param  a poly
 * @return   Index of highest set coefficient in polynomial.
 */
int BPU_gf2PolyGetHighestBitPos(BPU_T_GF2_Poly *a);

/**
 * Shift polynomial left by given positions.
 * @param a           polynomial to be shifted
 * @param shift_count count of shiftes to do
 */
void BPU_gf2PolyShiftLeft(BPU_T_GF2_Poly *a, int shift_count);

/**
 * Shift polynomial right by one.
 * @param  a polynomial to be shifted
 */
void BPU_gf2PolyShiftRightOne(BPU_T_GF2_Poly *a);

/**
 * Transpose polynomial.
 * @param out transposed output polynomial
 * @param in  input polynomial
 */
void BPU_gf2PolyTransp(BPU_T_GF2_Poly *out, const BPU_T_GF2_Poly *in);

/************************************************
 POLYNOMIAL MATH
 ************************************************/

/**
 * Multiplicate polynomial by x.
 * @param a input / output polynomial
 */
void BPU_gf2PolyMulX(BPU_T_GF2_Poly *a);

/**
 * Polynomial add.
 * out = out + in
 * If is set crop to 1, it will set new polynomial degree.
 * Else it will have degree of maximum degree of out and in poly.
 * @param out  input / output polynomial
 * @param in   intput polynomial
 * @param crop boolean, if set actual degree of output
 */
void BPU_gf2PolyAdd(BPU_T_GF2_Poly *out, const BPU_T_GF2_Poly *in, int crop);

/**
 * Polynomial multiplication modulo.
 * c = a * b mod m
 * If is set crop to 1, it will set new polynomial degree.
 * Else it will have degree of degree(modulo) - 1.
 * @param a    factor
 * @param b    factor
 * @param c    product
 * @param m    modulo
 * @param crop boolean, if set actual degree of output
 */
void BPU_gf2PolyMulMod(const BPU_T_GF2_Poly *a, const BPU_T_GF2_Poly *b, BPU_T_GF2_Poly *c, const BPU_T_GF2_Poly *m, int crop);

/**
 * Polynomial division.
 * q = a / b
 * r = a % b
 * @param q quotient
 * @param r reminder
 * @param a dividend
 * @param b divisor
 */
void BPU_gf2PolyDiv(BPU_T_GF2_Poly *q, BPU_T_GF2_Poly *r, const BPU_T_GF2_Poly *a, const BPU_T_GF2_Poly *b);

/**
 * Extended Euclidean algorithm (XGCD).
 * a*s + b*t = d
 * @param  d gcd(a,b)
 * @param  s Bézout coefficient s
 * @param  t Bézout coefficient t
 * @param  a poly a
 * @param  b poly b
 * @param  m modulo
 */
void BPU_gf2PolyExtEuclidA(BPU_T_GF2_Poly *d, BPU_T_GF2_Poly *s, BPU_T_GF2_Poly *t, const BPU_T_GF2_Poly *a, const BPU_T_GF2_Poly *b, const BPU_T_GF2_Poly *m);

/**
 * Calc inversion polynomial.
 * out = a^-1 mod m 
 * @param  out inversion to a
 * @param  a   polynomial
 * @param  m   modulo
 * @return     1 if found, else not found
 */
int BPU_gf2PolyInv(BPU_T_GF2_Poly *out, const BPU_T_GF2_Poly *a, const BPU_T_GF2_Poly *mod);

/************************************************
 SPARSE POLYNOMIAL UTILS
 ************************************************/

/**
 * Copy sparse polynomial. After work you have to free memory using call BPU_gf2SparsePolyFree.
 * @param out output sparse polynomial
 * @param in input sparse polynomial 
 */
void BPU_gf2SparsePolyCopy(BPU_T_GF2_Sparse_Poly *out, const BPU_T_GF2_Sparse_Poly *in);

/**
 * Copy polynomial. After work you have to free memory using call BPU_gf2PolyFree.
 * @param out output polynomial
 * @param in input polynomial 
 */
void BPU_gf2PolyCopy(BPU_T_GF2_Poly *out, const BPU_T_GF2_Poly *in);

void BPU_gf2PolyReset(BPU_T_GF2_Poly *out);
/**
 * Initialize random polynomial. After work you have to free memory using call BPU_gf2PolyFree.
 * @param out output polynomial
 * @param l length of polynomial (length - 1 = degree of polynomial)
 * @param w weight of polynomial
 * @param set_deg boolean param, if 1, it will crop polynomial to the actual degree and reallocate it
 * @return 0 - succes, else error
 */
int BPU_gf2PolyInitRand(BPU_T_GF2_Poly *out, int l, int w, int set_deg);

/************************************************
 SPARSE POLYNOMIAL MATH
 ************************************************/

/**
 * Polynomial add sparse polynomial.
 * out = out + in
 * @param out  input / output polynomial
 * @param in   intput sparse polynomial
 */
void BPU_gf2SparsePolyAdd(BPU_T_GF2_Poly *out, const BPU_T_GF2_Sparse_Poly *in);

/**
 * Polynomial and sparse polynomial, returns hamming weight of result.
 * hw(and(a,b))
 * @param  a polynomial
 * @param  b sparse polynomial
 * @return   hamming weight of result of and operation
 */
int BPU_gf2SparsePolyAndHW(const BPU_T_GF2_Poly *a, const BPU_T_GF2_Sparse_Poly *b);

/************************************************
 QUASI-CYCLIC MATRIX UTILS
 ************************************************/

/**
 * Transpose quasi-cyclic matrix.
 * @param out output transposed matrix
 * @param in  input matrix
 */
void BPU_gf2QcMatrixTransp(BPU_T_GF2_QC_Matrix *out, const BPU_T_GF2_QC_Matrix *in);

void BPU_gf2QcMultirowMatrixTransp(BPU_T_GF2_QC_Matrix *out, const BPU_T_GF2_QC_Matrix *in);

void BPU_gf2QcEyeMatrix(BPU_T_GF2_QC_Matrix *out, int block_size, int blocks_count);

/**
 * @param direction - direction of the appending: 0 - horizontal, 1 - vertical
 */
void BPU_gf2QcAppendMatrix(BPU_T_GF2_QC_Matrix *out, BPU_T_GF2_QC_Matrix *first, BPU_T_GF2_QC_Matrix *second, int direction);
/**
 * Convert quasi-cyclic matrix into sparse quasi-cyclic matrix. Allocate memory, so after work it has to be freed by using call BPU_gf2SparseQcMatrixFree.
 * @param out output sparse quasi-cyclic matrix
 * @param input quasi-cyclic matrix
 * @param wi weights of cyclic elements in input matrix
 * @return
 */

void BPU_gf2QcSelectMatrix(BPU_T_GF2_QC_Matrix *out, BPU_T_GF2_QC_Matrix *in, int column_start, int column_end, int row_start, int row_end);

void BPU_gf2QcMatrixMultiply(BPU_T_GF2_QC_Matrix *out, BPU_T_GF2_QC_Matrix *left, BPU_T_GF2_QC_Matrix *right);

void BPU_gf2QcMatrixAdd(BPU_T_GF2_QC_Matrix *out, BPU_T_GF2_QC_Matrix *in);

int BPU_gf2QcInvMatrix(BPU_T_GF2_QC_Matrix *out, BPU_T_GF2_QC_Matrix *in);

int BPU_gf2QcMatrixToRref(BPU_T_GF2_QC_Matrix *out, BPU_T_GF2_QC_Matrix *in);

void BPU_gf2QcMatrixSwapRowBlocks(BPU_T_GF2_QC_Matrix *in, int row1, int row2);

void BPU_gf2QcMatrixCopy(BPU_T_GF2_QC_Matrix *out, BPU_T_GF2_QC_Matrix *in);

void BPU_gf2QcMatrixMultiplyRow(BPU_T_GF2_QC_Matrix *out, int row, BPU_T_GF2_Poly *multiple);

void BPU_gf2QcMatrixAddRowMultiple(BPU_T_GF2_QC_Matrix *out, int source, int target, BPU_T_GF2_Poly *multiple, BPU_T_GF2_Poly *module);

void BPU_gf2QcPermuteMatrixColumns(BPU_T_GF2_QC_Matrix *out, BPU_T_Perm_Vector *permutation);

void BPU_gf2QcPermuteMatrixRows(BPU_T_GF2_QC_Matrix *out, BPU_T_Perm_Vector *permutation);

void BPU_gf2QcMatrixVectorMultiply(BPU_T_GF2_Vector *out, BPU_T_GF2_QC_Matrix *mat, BPU_T_GF2_Vector *vec);

void BPU_gf2QcMatrixGetColumn(BPU_T_GF2_Vector *out, BPU_T_GF2_QC_Matrix *in, int column);

void BPU_gf2QcMatrixGetRow(BPU_T_GF2_Vector *out, BPU_T_GF2_QC_Matrix *in, int row);

int BPU_gf2QcMatrixToSparse(BPU_T_GF2_Sparse_Qc_Matrix *out, const BPU_T_GF2_QC_Matrix *in, const int wi[]);

/************************************************
 SPARSE QUASI-CYCLIC MATRIX UTILS
 ************************************************/

/**
 * Get row from sparse quasi-cyclic matrix.
 * @param m       sparse QC matrix
 * @param p       output row
 * @param row_num index of row to get
 */
void BPU_gf2SparseQcMatrixGetRow(BPU_T_GF2_Sparse_Poly *p, const BPU_T_GF2_Sparse_Qc_Matrix *m, int row_num);

/**
 * Transpose sparse quasi-cyclic matrix.
 * @param  out output transposed matrix
 * @param  in  input matrix
 */
void BPU_gf2SparseQcMatrixTransp(BPU_T_GF2_Sparse_Qc_Matrix *out, const BPU_T_GF2_Sparse_Qc_Matrix *in);

#endif // BPU_GF2_H
