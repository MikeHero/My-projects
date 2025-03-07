#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/usr/lib/blas.h"

void afisare(double* mat, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%.2lf ", mat[i * n + j]);
		}
		printf("\n");
	}
}

void transpune_matrice(double* a, double* at, int n)
{
   cblas_dtranspose(CblasRowMajor, n, n, a, n, at, n);
}

int main()
{
	double mat[SIZE * SIZE] = 	{	
									1.0, 2.0, 3.0, 
									0.0, 4.0, 5.0, 
									0.0, 0.0, 6.0 
								};

	double at[SIZE * SIZE] = {0.0};

	double mat2[SIZE * SIZE] = 	{ 	
									 7.0,  8.0,  9.0,
									10.0, 11.0, 12.0,
									13.0, 14.0, 15.0
								};


	printf("\ntranspunere:\n");
	/*double x[SIZE * SIZE] = { 0 };*/
	transpune_matrice(mat2, at, SIZE);
 	afisare(x, SIZE);

}