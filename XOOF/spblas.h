/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*             ********   ***                                 SparseLib++    */
/*          *******  **  ***       ***      ***               v. 1.5c        */
/*           *****      ***     ******** ********                            */
/*            *****    ***     ******** ********              R. Pozo        */
/*       **  *******  ***   **   ***      ***                 K. Remington   */
/*        ********   ********                                 A. Lumsdaine   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                                                                           */
/*                                                                           */
/*                     SparseLib++ : Sparse Matrix Library                   */
/*                                                                           */
/*               National Institute of Standards and Technology              */
/*                        University of Notre Dame                           */
/*              Authors: R. Pozo, K. Remington, A. Lumsdaine                 */
/*                                                                           */
/*                                 NOTICE                                    */
/*                                                                           */
/* Permission to use, copy, modify, and distribute this software and         */
/* its documentation for any purpose and without fee is hereby granted       */
/* provided that the above notice appear in all copies and supporting        */
/* documentation.                                                            */
/*                                                                           */
/* Neither the Institutions (National Institute of Standards and Technology, */
/* University of Notre Dame) nor the Authors make any representations about  */
/* the suitability of this software for any purpose.  This software is       */
/* provided ``as is'' without expressed or implied warranty.                 */
/*                                                                           */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#ifndef SPBLAS_H
#define SPBLAS_H

// #ifndef F77NAME
// # include "generic.h"
// # if defined(RIOS)
// #  define F77NAME(x) x
// # else
// #  define F77NAME(x) name2(x,_)
// # endif
// #endif

#ifdef COMPLEX_SUPPORT
#include "complex.h"
#endif

extern "C" {

void scoomm
  (const int &transa, const int &m, const int &n, const int &k, 
   const float &alpha, 
   const int descra[], const float *val, 
   const int *indx, const int *jndx, const int &nnz, 
   const float *b, const int &ldb, 
   const float &beta, float *c, const int &ldc, 
   float *work, const int &lwork);

void scscmm
  (const int &transa, const int &m, const int &n, const int &k, 
   const float &alpha, 
   const int descra[], const float *val, 
   const int *indx, const int *pntr, const float *b, int &ldb, 
   const float &beta, float *c, const int &ldc, 
   float *work, const int &lwork);
   
void scsrmm
  (const int &transa, const int &m, const int &n, const int &k, 
   const float &alpha, 
   const int descra[], const float *val, 
   const int *indx, const int *pntr, const float *b, int &ldb, 
   const float &beta, float *c, const int &ldc, 
   float *work, const int &lwork);
   
void dcoomm
  (const int &transa, const int &m, const int &n, const int &k, 
   const double &alpha, 
   const int descra[], const double *val, 
   const int *indx, const int *jndx, const int &nnz, 
   const double *b, const int &ldb, 
   const double &beta, double *c, const int &ldc, 
   double *work, const int &lwork);

void dcscmm
  (const int &transa, const int &m, const int &n, const int &k, 
   const double &alpha, 
   const int descra[], const double *val, 
   const int *indx, const int *pntr, const double *b, int &ldb, 
   const double &beta, double *c, const int &ldc, 
   double *work, const int &lwork);
   
void dcsrmm
  (const int &transa, const int &m, const int &n, const int &k, 
   const double &alpha, 
   const int descra[], const double *val, 
   const int *indx, const int *pntr, const double *b, int &ldb, 
   const double &beta, double *c, const int &ldc, 
   double *work, const int &lwork);
  

void dcscsm
  (const int &transa, const int &m, const int &n,
   const int &unitd, const double *dv, const double &alpha, 
   const int descra[], const double *val, 
   const int *indx, const int *pntr, const double *b, int &ldb, 
   const double &beta, double *c, const int &ldc, 
   double *work, const int &lwork);

void dcsrsm
  (const int &transa, const int &m, const int &n,
   const int &unitd, const double *dv, const double &alpha, 
   const int descra[], const double *val, 
   const int *indx, const int *pntr, const double *b, int &ldb, 
   const double &beta, double *c, const int &ldc, 
   double *work, const int &lwork);

void scscsm
  (const int &transa, const int &m, const int &n,
   const int &unitd, const float *dv, const float &alpha, 
   const int descra[], const float *val, 
   const int *indx, const int *pntr, const float *b, int &ldb, 
   const float &beta, float *c, const int &ldc, 
   float *work, const int &lwork);

void scsrsm
  (const int &transa, const int &m, const int &n,
   const int &unitd, const float *dv, const float &alpha, 
   const int descra[], const float *val, 
   const int *indx, const int *pntr, const float *b, int &ldb, 
   const float &beta, float *c, const int &ldc, 
   float *work, const int &lwork);

#ifdef COMPLEX_SUPPORT

void zcoomm
  (const int &transa, const int &m, const int &n, const int &k, 
   const complex &alpha, 
   const int descra[], const complex *val, 
   const int *indx, const int *jndx, const int &nnz, 
   const complex *b, const int &ldb, 
   const complex &beta, complex *c, const int &ldc, 
   complex *work, const int &lwork);

void zcscmm
  (const int &transa, const int &m, const int &n, const int &k, 
   const complex &alpha, 
   const int descra[], const complex *val, 
   const int *indx, const int *pntr, const complex *b, int &ldb, 
   const complex &beta, complex *c, const int &ldc, 
   complex *work, const int &lwork);
   
void zcsrmm
  (const int &transa, const int &m, const int &n, const int &k, 
   const complex &alpha, 
   const int descra[], const complex *val, 
   const int *indx, const int *pntr, const complex *b, int &ldb, 
   const complex &beta, complex *c, const int &ldc, 
   complex *work, const int &lwork);

void zcscsm
  (const int &transa, const int &m, const int &n,
   const int &unitd, const complex *dv, const complex &alpha, 
   const int descra[], const complex *val, 
   const int *indx, const int *pntr, const complex *b, int &ldb, 
   const complex &beta, complex *c, const int &ldc, 
   complex *work, const int &lwork);

void zcsrsm
  (const int &transa, const int &m, const int &n,
   const int &unitd, const complex *dv, const complex &alpha, 
   const int descra[], const complex *val, 
   const int *indx, const int *pntr, const complex *b, int &ldb, 
   const complex &beta, complex *c, const int &ldc, 
   complex *work, const int &lwork);


#endif
// COMPLEX_SUPPORT



}

#endif
