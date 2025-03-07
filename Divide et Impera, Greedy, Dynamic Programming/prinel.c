#include <stdio.h>
#include <stdlib.h>

#define SIZE 1001

int nr_operatii(int x, int target)
{
	int nr = 0;
	// printf("%4d", target);
	if( x == target)
		return nr;

	while( 2 * x <= target )
	{	
		x*= 2;
		// if( x == 2)
		// 	printf("%d", x);
		// else
		// 	printf("%4d ", x);
		nr++;
	}

	int i;

	while( x < target )
	{
		for( i = x / 2 + 1 ; i >= 1; i-- )
		{
			if(( x % i == 0 ) && ( x + i <= target))
			{	
				x = x + i;
				// printf("%4d ", x);
				nr++;
				break;
			}
		}
	}
	// printf("nr pasi este %4d\n", nr);
	return nr;
}

int rucsac(int n, int W, int p[SIZE], int w[SIZE])
{
	int i, c;
	int **dp;
	dp = (int**) calloc( (n + 1), sizeof(int*) );
	if( !dp)
	{
		printf("eroare alocare dp\n");
		return -1;
	}
	//printf("ceva\n");
	int j;
	for( i = 0; i <= n; i++)
	{	
		dp[i] = (int*)calloc( (W + 1) , sizeof(int));
		if( !dp[i])
		{
			for( j = 1; j < i; i++)
				free(dp[j]);
			printf("Eroare alocare dp[i]\n");
			return -1;
		}
	}

	dp[0][0] = 0;
	int aux;
	// dp este o matrice de dimensiunea (n + 1) x ( W + 1)
	// dp [0][orice] este pentru multimea vida
	// dp [orice][0] cazul in care avem K vid, 0, ghiozdan de capacitate 0

	for(c = 0 ; c <= W; c++ )
		dp[0][c] = 0;
	for( i = 0 ; i <= n; i++)
		dp[i][0] = 0;


	for( i = 1; i <= n; i++ )
	{
		for( c = 0; c <= W; c++)
		{
			// nu folosesc obiectul i, deci solutie ramane cea de la pasul i - 1
			dp[i][c] = dp[i - 1][c];

			// folosesc obiectul i, trebuie sa rezerv W[i] unitati in rucsac.
			// inseamna ca inainte trebuie sa ocup maxim capacity - W[i] unitati;
			if( c - w[i] >= 0 )
			{
				aux = dp[i - 1][ c - w[i]] + p[i];
				if( aux > dp[i][c])
					dp[i][c] = aux;
			}
		}
	}
	if( 0 )
	{ 
		printf("linie 0 matrice:\n");
		for( c = 0; c <= W; c++)
			printf("%4d ", dp[0][c]);
		printf("\n\n");


		printf("linie 1 matrice:\n");
		for( c = 0; c <= W; c++)
			printf("%4d ", dp[1][c]);
		printf("\n\n");


		printf("linie 2 matrice:\n");
		for( c = 0; c <= W; c++)
			printf("%4d ", dp[2][c]);
		printf("\n\n");


		printf("linie 3 matrice:\n");
		for( c = 0; c <= W; c++)
			printf("%4d ", dp[3][c]);
		printf("\n\n");

		printf("linie 4 matrice:\n");
		for( c = 0; c <= W; c++)
			printf("%4d ", dp[4][c]);
		printf("\n\n");

		printf("linie 5 matrice:\n");
		for( c = 0; c <= W; c++)
			printf("%4d ", dp[5][c]);
		printf("\n\n");

			printf("linie 50 matrice:\n");
		for( c = 0; c <= W; c++)
			printf("%4d ", dp[50][c]);
		printf("\n\n");

			printf("linie 51 matrice:\n");
		for( c = 0; c <= W; c++)
			printf("%4d ", dp[51][c]);
		printf("\n\n");
	}

	int res = dp[n][W];
	
	for( i = 0 ; i <= n; i++)
		free(dp[i]);
	free(dp);

	return res;
}

struct TElement{
	int profit;
	int greutate;
};

int fcmp(const void*a, const void*b)
{
	struct TElement x = *(struct TElement*)a;
	struct TElement y = *(struct TElement*)b;

	float val_x = 1.0 * x.profit / x.greutate;
	float val_y = 1.0 * y.profit / y.greutate;

	if(val_x < val_y)
		return 1;
	return -1;
}

int main()
{
	
	int n, k;
	
	FILE* in = fopen("prinel.in", "rt");
	if( in == NULL)
	{
		printf("Eroare deschidere fisier citire\n");
		return -1;
	}

	FILE* out = fopen("prinel.out", "wt");
	if( out == NULL)
	{
		printf("Eroare deschidere fisier citire\n");
		return -1;
	}

	struct TElement v[SIZE];
	int target[SIZE], p[SIZE], w[SIZE];
	fscanf(in, "%d%d", &n, &k);

	int i;
	for( i = 1 ; i <= n; i++) 
		fscanf(in, "%d", &target[i] );		// 51 pozitia 0
	for( i = 1 ; i <= n; i++) 
	{	
		fscanf(in, "%d", &p[i] );
		v[i].profit = p[i];
	}

	int j;
	w[0] = 0;
	for( i = 1; i <= n; i++)
	{	
		w[i] = nr_operatii(1, target[i]);
		v[i].greutate = w[i];
	}

	qsort(v, n, sizeof(struct TElement), fcmp);

	

	int res = rucsac(n, k, p, w);
	fprintf(out, "%d\n", res );
	

	fclose(in);
	fclose(out);

	return 0;
}