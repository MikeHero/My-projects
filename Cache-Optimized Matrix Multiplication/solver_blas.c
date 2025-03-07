/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"
#include <cblas.h>
#include <string.h>
/* 
 * Add your BLAS implementation here
 */

void sum_matrices(double *A, double* B, double *C, int n)
{
  
    // c = c + a;
    cblas_daxpy(n * n, 1.0, A, 1, C, 1);
    // c = c + b;
    cblas_daxpy(n * n, 1.0, B, 1, C, 1);
    
}
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	
    double *C = calloc(N * N, sizeof(double));
    if( C == NULL)
    {
        return NULL; // eroare alocare
    }
    
    int n = N;

    double alpha = 1.0;
    double beta = 1.0;

    // copie_b = A x B;
    double *copie_b = calloc( N * N, sizeof(double));
    memcpy(copie_b, B, N * N * sizeof(double));

    cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans,
                CblasNonUnit, n, n, alpha, A, n, copie_b, n);

    // copie_b = A x B x A_t
    cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans,
                CblasNonUnit, n, n, alpha, A, n, copie_b, n);

    // x = B_t x B_t
    double *x = calloc( N * N, sizeof(double));
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, n, n, n, 
                alpha, B, n, B, n, beta, x, n);

    sum_matrices(copie_b, x, C, n);

    free(copie_b);
    free(x);
    return C;
}

