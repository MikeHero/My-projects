/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <string.h>
/*
 * Add your optimized implementation here
 */


void transpune_matrice_eficient(double *a, double* at, int n)
{
    register int i, j;

        for (i = 0; i != n; ++i) 
        {   
            /* coloana i din A' */
            register double *A_t_ptr = at + i;  

            // linia i din A 
            register double *A_ptr = a + i * n;  

            for ( j = 0; j != n; j++ ) 
            {
                *A_t_ptr = *A_ptr;
                A_t_ptr += n;
                ++A_ptr;
		    }
	}
}

void inmultire_matrice_triung_inferior_cu_matrice2(double *a, double *b, double *c, int n) {
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {   
            // Pointer linia i din matricea A
            register double *pa = a + i * n;  

            // Pointer coloana j din matricea B
            register double *pb = b + j;      

            register double suma = 0;

            // pana la diagonala k<=i; matrice triunghiulara;
            for (int k = 0; k <= i; ++k) 
            {  
                suma += (*pa) * (*pb);
                ++pa;               
                pb += n;           
            }

            *(c + i * n + j) = suma; 
        }
    }
}

void inmultire_matr(double *a, double* b, double *c, int n)
{
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {   
            // Pointer linia i din matricea A
            register double *pa = a + i * n; 

            // Pointer coloana j din matricea B
            register double *pb = b + j;     

            register double s = 0;

            for (int k = 0; k < n; ++k) 
            {
                s += (*pa) * (*pb);  
                ++pa;               
                pb += n;          
            }

            *(c + i * n + j) = s; 
        }
    }
}

void adunare_matrici(double *d, double *e, double *c, int n)
{
    register int i, j;

    for (i = 0; i < n; ++i)
    {
        // pointer la linia i din matricele d, e, c
        register double *pd = d + i * n; 
        register double *pe = e + i * n; 
        register double *pc = c + i * n; 

        for (j = 0; j < n; ++j)
        {
            *pc += (*pd + *pe); 
            ++pd;               
            ++pe;               
            ++pc;             
        }
    }
}

void copie_matrice(double *res, double *c, int n)
{
    register int i, j;

    for (i = 0; i < n; ++i)
    {
        register double *pres = res + i * n; 
        register double *pc = c + i * n;     

        // se parcurg matricele analog ca in functia de insumare de mai sus
        for (j = 0; j < n; ++j)
        {
            *pc = *pres; 
            ++pres;      
            ++pc;       
        }
    }
}

void inmultire_matr_cu_matrice_triung_sup(double *a, double* b, double *d, int n)
{
    register int i, j, k;

    memset(d, 0, n * n * sizeof(double));

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            register double s = 0.0;

            // Pointer linia i din matricea B
            register double *pb = b + i * n; 
            
            // Pointer coloana j din matricea A
            register double *pa = a + j;     

            for (k = 0; k <= j; ++k)
            {
                s += *(pb+k) * *(pa+ k * n);
            }
            * (d + i * n + j) = s;
        }
    }
}

void calculeaza(double *a, double *b, double *res, int n)
{
    double *at, *d, *e, *bt, *c;
	memset(res, 0, n*n*sizeof(double));

	at = malloc(n * n * sizeof(double));
	memset(at, 0, n * n * sizeof(double));

    d = malloc(n * n * sizeof(double));
	memset(d, 0, n * n * sizeof(double));

    e = malloc(n * n * sizeof(double));
	memset(e, 0, n * n * sizeof(double));

    bt = malloc(n * n * sizeof(double));
	memset(bt, 0, n * n * sizeof(double));

    c = malloc(n * n * sizeof(double));
	memset(c, 0, n * n * sizeof(double));

	// at = A transpus
    transpune_matrice_eficient(a, at, n);

    // d = a_t*b
    inmultire_matrice_triung_inferior_cu_matrice2(at, b, d, n); 


    // e = B x A
    inmultire_matr_cu_matrice_triung_sup(a, b, e, n);

    // C = D + E
    adunare_matrici(d,e,c,n);

	// Bt = B transpus
    transpune_matrice_eficient(b, bt, n);

	// rezultat = C x Bt
    inmultire_matr(c, bt, res, n);

	free(at); 
	free(d);
	free(e); 
	free(bt);
	free(c);

}

double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	double *C = malloc(N * N * sizeof(double));
    memset(C, 0, N * N * sizeof(double));

    if( C == NULL)
    {
        return NULL; // eroare alocare
    }
    calculeaza(A, B, C, N);
   
 
	return C;
}
