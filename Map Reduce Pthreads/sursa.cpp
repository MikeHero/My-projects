#include <iostream>
#include <pthread.h>
#include <stdlib.h>		// atoi
#include <string.h>
#include <math.h>
#include <unordered_set>

#define SIZE 200
#define SIZE_L 3000

pthread_barrier_t barrier;
pthread_mutex_t mutex;

int min(double a, double b)
{
	return (a < b) ? a : b;
}


int exponentPerfect(long long x, int e)
{
	long long start, stop, res, mid;
	start = 1;
	stop = sqrt(x) + 1;

	while( start < stop)
	{	
		// corner case
		if( stop - start == 1)
		{
			if( pow(start, e) == x)
				return 1;
			if( pow(stop, e) == x)
				return 1;
			return 0;
		}

		mid = (start + stop) / 2;
		res	= pow(mid, e);
		if( res == x )
			return 1;
		else if( res < x )
		{
			start = mid;
		}
		else if( res > x)
		{
			stop = mid;
		}
	}
	
	return 0;
}

typedef struct ceva
{
	int r, m, n;
	FILE** vf;
	long long** vector_liste;
	int *indice_lista;
	int thread_id;

}TElem;

void *f(void *arg)
{
	// int thread_id = *(int *)arg;
	long long **vector_liste;
	int *indice_lista;

	FILE** vf;	// vector de fisiere
	int r, m, n;

	TElem x = *((TElem*)arg);
	int thread_id = x.thread_id;
	vector_liste = x.vector_liste;
	indice_lista = x.indice_lista;
	vf = x.vf;
	r = x.r;
	m = x.m;
	n = x.n;

	if( thread_id < m )			// thread de tip mapper
	{
		int start = thread_id * (double) n / m;
		int stop = min( (thread_id + 1) * (double)n / m, n);
		

		// am de procesat fisiere din vectorul de fisiere incepand cu indicele start si oprindu-ma 
		// 	la indicele stop
		int i, j;
		for( i = start; i < stop; i++)
		{
			FILE* in = vf[i];
			char buff[SIZE];
			fgets(buff, SIZE, in);
			int n = atoi(buff);

			for(j = 0; j < n; j++)
			{
				fgets(buff, SIZE, in);
				long long nr = atoi(buff);
				// verific daca nr este patrat perfect, cub perfect, ^4 perfect ... si il stochez.
				// normal ar fi sa am nr reduceri liste, de la 2 la M + 1 liste specifice exponentilor	

				// lista comuna mapperilor pentru la a doua perfect, la a treia perfect etc
				// unde putere incepe de la 2 si se termina la r + 1
				for(int k = 2; k < r + 2; k++)
				{
					if( exponentPerfect(nr, k) == 1)
					{
						// 2 thread uri nu pot scrie simultan pe aceeasi pozitie in lista comuna
						pthread_mutex_lock(&mutex);
						vector_liste[k - 2][indice_lista[k - 2]] = nr;
						indice_lista[k - 2]++;	// primo pozitie libera din lista comuna pt la a doua, a treia ...
						pthread_mutex_unlock(&mutex);
					}
				}
				
			}
			// am terminat de procesat fisierul respectiv
			fclose(vf[i]);
		}

	}

	// thread urile reducer au nevoie ca cele de map sa-si fi terminat executia
	pthread_barrier_wait( &barrier);
	
	if( thread_id >= m )
	{
		// unordered set imi elimina duplicatele din listele de exponenti comune
		std::unordered_set<long long> mySet;
		int linie = thread_id - m;
		for(int i = 0; i < indice_lista[linie]; i++)
			mySet.insert(vector_liste[linie][i]);

		char buff[10];
		strncpy(buff, "out1.txt", 9);
		char c = 48 + thread_id - m + 2 ;		// '0' = 48
		buff[3] = c;
		//printf("%s\n", buff);

		FILE* out = fopen(buff, "wt");
		
		fprintf(out,"%ld", mySet.size());
		fclose(out);
	}



	pthread_exit(NULL);

}



int main(int argc, char** argv)
{
	long long **vector_liste;
	int *indice_lista;

	FILE** vf;	// vector de fisiere
	int r, m, n; // nr thread de tip Reducer, respectiv Map, si n = nr pe care-l citesc din fisier
	char buff[SIZE];
	int i;
	int ret;

	m = atoi(argv[1]);
	r = atoi(argv[2]);
	pthread_t threads[m + r];
	//int arguments[m + r];		// id urile thread urilor
	TElem arguments2[m+r];

	FILE* in = fopen( argv[3], "rt" );
	if( in == NULL)
	{	
		printf( "Eroare deschidere fisier : %s\n", argv[3]);
		return -1;
	}

	// se citeste fisierul initial cu numele celolrlalte fisiere
	fgets( buff, SIZE, in );
	n = atoi(buff);

	vf = (FILE**)malloc(n * sizeof(FILE*));
	if( vf == NULL )
	{
		printf("Eroare alocare\n");
		return -1;
	}


	// construim vectorul de fisiere
	for(i = 0; i < n; i++)
	{
		
		vf[i] = (FILE*)malloc(sizeof(FILE*));
		if( vf[i] == NULL )
		{
			printf("Eroare alocare\n");
			
			// dezalocam ceea ce am alocat pana-n prezent
			return -1;
		}

		fgets(buff, SIZE, in);
		int dim = strlen( buff );
		
		// eventual eliminam \n
		if(buff[dim - 1] == '\n')
			buff[--dim]='\0';

		vf[i] = fopen(buff, "rt");
		if( vf[i] == NULL)
		{	
			printf( "Eroare deschidere fisier: %s\n", buff);
			// dezalocam tot 
	
			return -1;
		}
	}


	indice_lista = (int*)malloc( r * sizeof(int) );
	if( indice_lista == NULL)
	{
		//dezalocam tot
		return -1;
	}


	// initial indicele urmatoarei pozitii libere din fiecare lista comuna va fi 0
	for( i = 0 ; i < r; i++)
		indice_lista[i] = 0;


	vector_liste = (long long**)malloc( r * sizeof(long long*));
	if( vector_liste == NULL)
	{
		//dezalocam
		return -1;
	}

	for( i = 0; i < r; i++)
	{
		vector_liste[i] = (long long*)malloc( SIZE_L * sizeof(long long));
		if( vector_liste[i] == NULL )
		{
			// dezalocam
			return -1;
		} 
	}

	pthread_mutex_init(&mutex, NULL);
	pthread_barrier_init(&barrier, NULL, m + r); 


	// cream thread urile
	for( i = 0 ; i < m + r ; i++)
	{
		//arguments[i] = i;
		TElem x;
		x.thread_id = i;
		x.n = n;
		x.m = m;
		x.r = r;
		x.vf = vf;
		x.vector_liste = vector_liste;
		x.indice_lista = indice_lista;

		arguments2[i] = x;
		ret = pthread_create(&threads[i], NULL, f, &arguments2[i]);

		if (ret) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}


	// dam join
	for (i = 0; i < m + r; i++) 
	{
		ret = pthread_join(threads[i], NULL);

		if (ret) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

	pthread_mutex_destroy(&mutex);
	pthread_barrier_destroy(&barrier);


	// eliberam memoria
	for(i = 0; i < r; i++)
		free(vector_liste[i]);
	free(vector_liste);

	free(indice_lista);

	//inchidem fisiere
	fclose(in);

	return 0;
}