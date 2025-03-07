/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */

void sum_matrices(double *A, double* B, double *C, int n) {
    // c = c + a;
    cblas_daxpy(n * n, 1.0, A, 1, C, 1);
    // c = c + b;
    cblas_daxpy(n * n, 1.0, B, 1, C, 1);
}

double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	double *C = calloc(N * N, sizeof(double));

	int n = N;
    double alpha = 1.0;
    double beta = 0.0;

    // pentru A_t * B
    double *AtB = calloc(N * N, sizeof(double)); 

    // pentru B * A
    double *BA = calloc(N * N, sizeof(double)); 

    // pentru (A_t * B + B * A)
    double *result = calloc(N * N, sizeof(double)); 

	// Calculam A_t * B
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, n, n, n, alpha, A, n, B, n, beta, AtB, n);

    // Calculam B * A
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, alpha, B, n, A, n, beta, BA, n);

    // Calculam A_t * B + B * A
    sum_matrices(AtB, BA, result, n);

	// inmultim suma de mai sus cu B_t
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, n, n, n, alpha, result, n, B, n, beta, C, n);

	// Eliberam memoria 
    free(AtB);
    free(BA);
    free(result);

    return C;
}
