/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <string.h>

/*
 * Add your unoptimized implementation here
 */

void transpune_matrice(double* a, double* at, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            *( at + i * n + j ) = * ( a + j * n + i );
        }
    }
}

void transpune_matrice_triung(double *a, double* at, int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = i; j < n; j++)
        {
            *( at + j * n + i)= *( a + i * n + j ) ;
        }
    }
}

void inmultire_matrice(double *a, double *b, double* c, int n)
{
    int i, j, k;
    for( i = 0 ; i < n; i++)
    {
        for( j = 0; j < n; j++)
        {
            c[i * n + j] = 0.0;
            for( k = 0; k < n; k++)
            {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}

void inmultire_matrice_triung_inferior_cu_matrice(double *a, double* b, double *d, int n)
{
    int i, j, k;

    // Se calculeaza "D = A x B" din formula
    // inmultire matrice triung inf

    memset(d, 0, n * n * sizeof(double));
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            // se ignora elementele de deasupra diagonalei lui A
            for (k = 0; k <= i; k++)
            {
                // matricea este triunghiulara inferior
                d[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}


void inmultire_matr_cu_matrice_triung_sup(double *a, double* b, double *d, int n)
{
    int i, j, k;

    memset(d, 0, n * n * sizeof(double));

    // D = B x A
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k <= j; k++) 
            {
                d[i * n + j] += b[i * n + k] * a[k * n + j];
            }
        }
    }
}

void calculeaza(double *a, double *b, double *c, int n)
{
	memset(c, 0, n * n *sizeof(double));

    double *at, *d, *e, *bt, *res;
	at = malloc(n * n * sizeof(double));
	memset(at, 0, n * n * sizeof(double));

    d = malloc(n * n * sizeof(double));
	memset(d, 0, n * n * sizeof(double));

    e = malloc(n * n * sizeof(double));
	memset(e, 0, n * n * sizeof(double));

    bt = malloc(n * n * sizeof(double));
	memset(bt, 0, n * n * sizeof(double));

    res = malloc(n * n * sizeof(double));
	memset(res, 0, n * n * sizeof(double));

	// at = A transpus
    transpune_matrice_triung(a, at, n);

    // d = a_t*b
    inmultire_matrice_triung_inferior_cu_matrice(at, b, d, n);

    // e = B x A
    inmultire_matr_cu_matrice_triung_sup(a, b, e, n);

    // C = D + E
    int i, j;
    for(i = 0; i < n; i++)
    {
        for( j = 0; j < n; j++)
        {
            c[i * n + j] += d[i * n + j] + e[i * n + j];  
        }
    }

    transpune_matrice(b, bt, n);
    inmultire_matrice(c, bt, res, n);

    free(at);
    free(d);
    free(e);
    free(bt);

    for( i = 0; i < n; i++)
        for( j = 0; j < n; j++)
            c[i * n + j] = res[i * n + j];
    free(res);
}


double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	double *C = malloc(N * N * sizeof(double));
    memset(C, 0, N * N * sizeof(double));

    if( C == NULL)
    {
        return NULL; // eroare alocare
    }
    calculeaza(A, B, C, N);
    
	return C;
}
