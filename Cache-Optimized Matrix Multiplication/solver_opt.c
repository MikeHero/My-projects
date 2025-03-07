/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"
#include <string.h>

/*
 * Add your unoptimized implementation here
 */

void swap(double *x, double *y)
{
    double temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void transpune_matrice(double* a, double *at, int n)
{
    
    register int i;
    for( i = 0; i < n; i++)
    {
        // linia i din A
        register double* a_ptr = a + i * n;

        // coloana i din A
        register double* a_t_ptr = at + i;

        register int j;
        for( j = 0; j < n; j++)
        {
            *(a_t_ptr) = *(a_ptr);
            a_t_ptr += n;
            a_ptr++;
        }
    }
    
}
void transpune_matrice_triung(double *a, double* at, int n)
{
    register int i, j;
    
    memcpy(at, a, n * n * sizeof(double));

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            swap ( ( at + i * n + j), ( at + j * n + i ) );
        }
    }
}

void inmultire_matrice(double *a, double*b, double *c, int n)
{
	register int i, j, k;
	for( i = 0; i < n; i++)
	{
		register double *orig_pa = a + i * n;
		for( j = 0; j < n; j++)
		{
			register double* pa = orig_pa;
			register double* pb = b + j;
			register double s = 0.0;

			for( k = 0; k < n; k++)
			{
				s += (*pa) * (*pb);
				pa++;
				pb += n;
			}
			c[i * n + j] = s;
		}
	}
}

void inmultire_matrice_triung(double *a, double* b, double *c, int n)
{
    register int i, j, k;

    // Se calculeaza "D = A x B" din formula
    // inmultire matrice triung sup


    double *d = malloc(n * n * sizeof(double));
    memset(d, 0, n * n * sizeof(double));
    for( i = 0; i < n; i++)
    {
        for( j = 0; j < n; j++)
        {
            // se ignora elementele de sub diagonala lui A
           
            register double sum = 0.0;
            for( k = i; k < n; k++)
            {
                // matricea este triunghiulara superior
		sum += a[i * n + k] * b[k * n + j];
            }
	    d[i * n + j ] = sum;
        
        }
    }

    double *at = malloc(n * n * sizeof(double));
    memset(at, 0, n * n * sizeof(double));

    memcpy(at, a, n * n * sizeof(double));
    transpune_matrice_triung(a, at, n);

    // se calculeaza C = D x At = (A x B) x At;
    for(i = 0; i < n; i++)
    {
        for( j = 0; j < n; j++)
        {
            register double sum = 0.0;
            for( k = j; k < n; k++)
            {
                // se ignora elementele de deasupra diagonalei principale
                sum += d[i * n + k] * at[k * n + j];
            }
	    c[i * n + j ] = sum;
        }
    }
    // in matricea c se regaseste rezultatul
    free(at);
    free(d);

}


void calculeaza(double *a, double *b, double *c, int n)
{
    // am facut C = A x B x At;
    
    inmultire_matrice_triung(a, b, c, n);
    double *d, *v;
    d = malloc(n * n * sizeof(double));
    memset(d, 0, n * n * sizeof(double));

    v = malloc( n * n * sizeof(double));
    memset(v, 0, n * n * sizeof(double));

    // D = Bt
    transpune_matrice(b, d, n);
    
    // V = Bt x Bt
    inmultire_matrice(d, d, v, n);


    // C = C + V; sau C = A x B x At + Bt x Bt;
    
    register int i, j;
    for( i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            c[i * n + j] += v[i * n + j];
        }
    }
    free(d);
    free(v);
}

double* my_solver(int N, double *A, double* B) 
{
	printf("OPT SOLVER\n");
    
    double *C = malloc(N * N * sizeof(double));
    if( C == NULL)
    {
        return NULL; // eroare alocare
    }
    calculeaza(A, B, C, N);

	return C;
}
