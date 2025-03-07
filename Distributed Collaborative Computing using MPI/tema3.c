#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 200


void afisare(int rank, int *v0, int n0, int *v1, int n1, int *v2, int n2, int *v3, int n3)
{
    printf("%d -> 0:", rank);
    int i;
    for(i = 0; i < n0; i++)
    { 
        printf("%d", v0[i]);
        if( i < n0 - 1 )
            printf(",");
    }
    printf(" 1:");
    for(i = 0; i < n1; i++)
    { 
        printf("%d", v1[i]);
        if( i < n1 - 1 )
            printf(",");
    }
    printf(" 2:");
    for(i = 0; i < n2; i++)
    { 
        printf("%d", v2[i]);
        if( i < n2 - 1 )
            printf(",");
    }
    printf(" 3:");
    for(i = 0; i < n3; i++)
    { 
        printf("%d", v3[i]);
        if( i < n3 - 1 )
            printf(",");
    }
    printf("\n");

}

void afisare_vector(int n, int* v)
{
        
    printf("Rezultat: ");
    for(int i = 0; i < n; i++)
    {    
        printf("%d", v[i]);
        if( i != n -1)
            printf(" ");
    }
    printf("\n");
}

int min(int a, int b)
{
    return (a < b )? a : b; 
}

int main (int argc, char *argv[])
{
    int  numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int nr_workeri_0 = -1;
    int nr_workeri_1 = -1;
    int nr_workeri_2 = -1;
    int nr_workeri_3 = -1;
    
    int *vector_workeri_0 = NULL;
    int *vector_workeri_1 = NULL;
    int *vector_workeri_2 = NULL;
    int *vector_workeri_3 = NULL;
    

    int *v;
    int n;

    MPI_Status status;
    int parinte = -1;
    
    char buff[SIZE];
    int i = 0, j;

    int nr_workeri_total = numtasks - 4;
    int start, stop;

    int id;
    int unit;
    int contor = 0;


    if( rank == 0)
    {
        FILE* in = fopen( "cluster0.txt", "rt" );
        fgets( buff, SIZE, in );
        nr_workeri_0 = atoi(buff);

        vector_workeri_0 = malloc(nr_workeri_0 * sizeof(int));
        if(vector_workeri_0 == NULL )
        {
            printf("Eroare alocare\n");
            return -1;
        }


        // Trimit mesaj catre workeri sa le spun ca eu sunt coordonatorul
        
        for( i = 0; i < nr_workeri_0; i++)
        {
            fgets(buff, SIZE, in);
            vector_workeri_0[i] = atoi(buff);
            printf("M(%d,%d)\n", rank, vector_workeri_0[i]);
            MPI_Send(&rank, 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
        }

        fclose(in);


        // Coordonator 0 trimite workerii sai catre coordonator 3
        
        {
            printf("M(%d,%d)\n", 0, 3);
            MPI_Send(&nr_workeri_0, 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
            for( i = 0; i < nr_workeri_0; i++)
            {
                printf("M(%d,%d)\n", 0, 3);
                MPI_Send(&vector_workeri_0[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
            }
        }

        // facem receive de la Coordonator 3 si astfel Coordonator 0 va cunoaste intreaga topologie
        {
            // primim informatii despre coordonator 1
            MPI_Recv(&nr_workeri_1, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
            vector_workeri_1 = malloc(nr_workeri_1 * sizeof(int));
            
            if(vector_workeri_1 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_1; i++)
                MPI_Recv(&vector_workeri_1[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);


            // primim informatii despre coordonator 2
            MPI_Recv(&nr_workeri_2, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
            vector_workeri_2 = malloc(nr_workeri_2 * sizeof(int));
            
            if(vector_workeri_2 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_2; i++)
                MPI_Recv(&vector_workeri_2[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);


            // primim informatii despre coordonator 3
            MPI_Recv(&nr_workeri_3, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
            vector_workeri_3 = malloc(nr_workeri_3 * sizeof(int));
            
            if(vector_workeri_3 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_3; i++)
                MPI_Recv(&vector_workeri_3[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
        }

         // In acest moment Coordonator 1 are topologia completa si o afiseaza
        afisare(rank, vector_workeri_0, nr_workeri_0, vector_workeri_1, nr_workeri_1,
            vector_workeri_2, nr_workeri_2, vector_workeri_3, nr_workeri_3);


        // Coordonator 0 anunta topologia tuturor proceselor worker pe care le are fiecare Coordonator
        {   
            
            for( i = 0; i < nr_workeri_0; i++)
            {
              
                // Coordonator 0
                printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                MPI_Send(&nr_workeri_0, 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                for(int j = 0; j < nr_workeri_0; j++)
                {
                    printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                    MPI_Send(&vector_workeri_0[j], 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                }

              
                // Coordonator 1
                printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                MPI_Send(&nr_workeri_1, 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_1; j++)
                {
                    printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                    MPI_Send(&vector_workeri_1[j], 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                }

                //Coordonator 2
                printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                MPI_Send(&nr_workeri_2, 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_2; j++)
                {
                    printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                    MPI_Send(&vector_workeri_2[j], 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                }

                // Coordonator 3
                printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                MPI_Send(&nr_workeri_3, 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_3; j++)
                {
                    printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                    MPI_Send(&vector_workeri_3[j], 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                }


            }
        }

        
        n = atoi(argv[1]);

        v = malloc( n * sizeof(int));
        if( v == NULL )
        {
            printf("Eroare alocare\n");
            return -1;
        }

        for( i = 0 ; i < n; i++)
        {
            v[i] = n - i - 1;
        }

        // trimitem vectorul si la Coordonator 3
        {
            printf("M(%d,%d)\n", 0, 3);
            MPI_Send(&n, 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
            for(i = 0 ; i < n; i++)
            {
                printf("M(%d,%d)\n", 0, 3);
                MPI_Send(&v[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
            }
        }

        
        // toate procesele coordonator cunosc vectorul


     
        // coordonator 0 imparte calculele workerilor sai si primeste rezultatul
        contor = 0;
        for( i = 0; i < nr_workeri_0; i++)
        {
            id = vector_workeri_0[i] - 4;
            start = id * (double)n / nr_workeri_total ;
            stop = min( (id + 1) * (double)n / nr_workeri_total, n);

            unit = stop - start;

            printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
            MPI_Send(&unit, 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
            
            for( j = start; j < stop; j++)
            {
                printf("M(%d,%d)\n", 0, vector_workeri_0[i]);
                MPI_Send(&v[j], 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD);
                if(v[j] != 0 )
                    contor++;

                MPI_Recv(&v[j], 1, MPI_INT, vector_workeri_0[i], 10, MPI_COMM_WORLD, &status);

            }

        }

        //Coord 0 prim calc de la coord 3
        int contor_primit;
        MPI_Recv(&contor_primit, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);

        for(j = 0; j < contor_primit; j++)
        {
            int index;
            MPI_Recv(&index, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
            int val;
            MPI_Recv(&val, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
            v[index] = val;
        }
        

       
        afisare_vector(n, v);


    }
    else if( rank == 1)
    {
        FILE* in = fopen( "cluster1.txt", "rt" );
        fgets( buff, SIZE, in );
        nr_workeri_1 = atoi(buff);

        vector_workeri_1 = malloc(nr_workeri_1 * sizeof(int));
        if(vector_workeri_1 == NULL )
        {
            printf("Eroare alocare\n");
            return -1;
        }
        int i = 0;
        for( i = 0; i < nr_workeri_1; i++)
        {
            fgets(buff, SIZE, in);
            vector_workeri_1[i] = atoi(buff);
            printf("M(%d,%d)\n", rank, vector_workeri_1[i]);
            MPI_Send(&rank, 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
        }

        // am terminat citirea
        fclose(in);

        // facem receive de la 2
        {
            // ce a primit de la coordonator 0
            MPI_Recv(&nr_workeri_0, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
            vector_workeri_0 = malloc(nr_workeri_0 * sizeof(int));
            
            if(vector_workeri_0 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_0; i++)
                MPI_Recv(&vector_workeri_0[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);


            // ce a primit de la coordonator 3
            MPI_Recv(&nr_workeri_3, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
            vector_workeri_3 = malloc(nr_workeri_3 * sizeof(int));
            
            if( vector_workeri_3 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_3; i++)
                MPI_Recv(&vector_workeri_3[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);



            // ce era al lui initial
            MPI_Recv(&nr_workeri_2, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
            vector_workeri_2 = malloc(nr_workeri_2 * sizeof(int));
            
            if( vector_workeri_2 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_2; i++)
                MPI_Recv(&vector_workeri_2[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);

        }

        // In acest moment Coordonator 1 are topologia completa si o afiseaza
        afisare(rank, vector_workeri_0, nr_workeri_0, vector_workeri_1, nr_workeri_1,
            vector_workeri_2, nr_workeri_2, vector_workeri_3, nr_workeri_3);

        // Coordonator 1 trimite catre Coordonator 2 
        // In urma acestui send devine si Coordonator 2 complet
        {
            // trimite doar ce tine de Coordpnator 1 ca doar asta ii lipseste lui 2 pentru a fi omniscient 
            // asupra topologiei 

            printf("M(%d,%d)\n", 1, 2);
            MPI_Send(&nr_workeri_1, 1, MPI_INT, 2, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_1; i++)
            {
                printf("M(%d,%d)\n", 1, 2);
                MPI_Send(&vector_workeri_1[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
            }
        }



        // Coordonator 1 anunta topologia tuturor proceselor worker pe care le are fiecare Coordonator
        {   
            for( i = 0; i < nr_workeri_1; i++)
            {
                // Coordonator 0
                printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                MPI_Send(&nr_workeri_0, 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                for(int j = 0; j < nr_workeri_0; j++)
                {
                    printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                    MPI_Send(&vector_workeri_0[j], 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                }

              
                // Coordonator 1
                printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                MPI_Send(&nr_workeri_1, 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_1; j++)
                {
                    printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                    MPI_Send(&vector_workeri_1[j], 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                }

                //Coordonator 2
                printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                MPI_Send(&nr_workeri_2, 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_2; j++)
                {
                    printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                    MPI_Send(&vector_workeri_2[j], 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                }

                // Coordonator 3
                printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                MPI_Send(&nr_workeri_3, 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_3; j++)
                {
                    printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                    MPI_Send(&vector_workeri_3[j], 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                }


            }
        }

        // Coordonator 1 primeste vectorul de la Coordonator 2
        {
            MPI_Recv(&n, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
            v = malloc(n * sizeof(int));
            if(v == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0 ; i < n; i++)
                MPI_Recv(&v[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
        }

       // toate procesele coordonator cunosc vectorul

        int *v_copie = malloc(n * sizeof(int));
        if(v_copie == NULL)
        {
            printf("Eroare alocare\n");
            return -1;
        }
        for(i = 0 ; i < n; i++)
            v_copie[i] = v[i];

        //coordonator 1 trimite la workerii lui calculele si primeste rezultatul
       contor = 0;
        for( i = 0; i < nr_workeri_1; i++)
        {
            id = vector_workeri_1[i] - 4;
            start = id * (double)n / nr_workeri_total ;
            stop = min( (id + 1) * (double)n / nr_workeri_total, n);

            unit = stop - start;

            printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
            MPI_Send(&unit, 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
            
            for( j = start; j < stop; j++)
            {
                printf("M(%d,%d)\n", 1, vector_workeri_1[i]);
                MPI_Send(&v[j], 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD);
                if(v[j] != 0 )
                    contor++;

                MPI_Recv(&v[j], 1, MPI_INT, vector_workeri_1[i], 10, MPI_COMM_WORLD, &status);

            }

        }
        
        


        // 1 trimite ce are spre coord 2
        {
            printf("M(%d,%d)\n", 1, 2);
            MPI_Send(&contor, 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
            for(i = 0; i < n ; i++)
            {
                if(v[i] != v_copie[i])
                {
                    printf("M(%d,%d)\n", 1, 2);
                    MPI_Send(&i, 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
                    printf("M(%d,%d)\n", 1, 2);
                    MPI_Send(&v[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
                }   

            }

        }
    }
    else if( rank == 2)
    {
        FILE* in = fopen( "cluster2.txt", "rt" );
        fgets( buff, SIZE, in );
        nr_workeri_2 = atoi(buff);

        vector_workeri_2 = malloc(nr_workeri_2 * sizeof(int));
        if(vector_workeri_2 == NULL )
        {
            printf("Eroare alocare\n");
            return -1;
        }
        int i = 0;
        for( i = 0; i < nr_workeri_2; i++)
        {
            fgets(buff, SIZE, in);
            vector_workeri_2[i] = atoi(buff);
            printf("M(%d,%d)\n", rank, vector_workeri_2[i]);
            MPI_Send(&rank, 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
        }
        fclose(in);

        // facem receive de la 3
        {

            // ce a primit de la coordonator 0
            MPI_Recv(&nr_workeri_0, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
            vector_workeri_0 = malloc(nr_workeri_0 * sizeof(int));
            
            if(vector_workeri_0 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_0; i++)
                MPI_Recv(&vector_workeri_0[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);


            // ce era al lui initial
            MPI_Recv(&nr_workeri_3, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
            vector_workeri_3 = malloc(nr_workeri_3 * sizeof(int));
            
            if( vector_workeri_3 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_3; i++)
                MPI_Recv(&vector_workeri_3[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);


        }

        // Coordonator 2 trimite catre coordonator 1
        {
            // trimite ce stia de la 0
            printf("M(%d,%d)\n", 2, 1);
            MPI_Send(&nr_workeri_0, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_0; i++)
            {
                printf("M(%d,%d)\n", 2, 1);
                MPI_Send(&vector_workeri_0[i], 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
            }


            // trimite ce stie de la 3
            printf("M(%d,%d)\n", 2, 1);
            MPI_Send(&nr_workeri_3, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_3; i++)
            {
                printf("M(%d,%d)\n", 2, 1);
                MPI_Send(&vector_workeri_3[i], 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
            }

            // trimite ce e al lui
            printf("M(%d,%d)\n", 2, 1);
            MPI_Send(&nr_workeri_2, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_2; i++)
            {
                printf("M(%d,%d)\n", 2, 1);
                MPI_Send(&vector_workeri_2[i], 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
            }
            
        }

        // facem receive de la 1 si astfel Coordonator 2 va cunoaste intreaga topologie
        {
            MPI_Recv(&nr_workeri_1, 1, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);
            vector_workeri_1 = malloc(nr_workeri_1 * sizeof(int));
            
            if( vector_workeri_1 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_1; i++)
                MPI_Recv(&vector_workeri_1[i], 1, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);
        }

        // In acest moment Coordonator 1 are topologia completa si o afiseaza
        afisare(rank, vector_workeri_0, nr_workeri_0, vector_workeri_1, nr_workeri_1,
            vector_workeri_2, nr_workeri_2, vector_workeri_3, nr_workeri_3);


        // Coordonator 2 trimite catre coordonator 3
        {
            // trimite ce stie de la coordonator 1
            printf("M(%d,%d)\n", 2, 3);
            MPI_Send(&nr_workeri_1, 1, MPI_INT, 3, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_1; i++)
            {
                printf("M(%d,%d)\n", 2, 3);
                MPI_Send(&vector_workeri_1[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
            }

            // trimite ce era al lui
            printf("M(%d,%d)\n", 2, 3);
            MPI_Send(&nr_workeri_2, 1, MPI_INT, 3, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_2; i++)
            {
                printf("M(%d,%d)\n", 2, 3);
                MPI_Send(&vector_workeri_2[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
            }
        }

        // Coordonator 2 anunta topologia tuturor proceselor worker pe care le are fiecare Coordonator
        {   
            for( i = 0; i < nr_workeri_2; i++)
            {
                // Coordonator 0
                printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                MPI_Send(&nr_workeri_0, 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                for(int j = 0; j < nr_workeri_0; j++)
                {
                    printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                    MPI_Send(&vector_workeri_0[j], 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                }

                // Coordonator 1
                printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                MPI_Send(&nr_workeri_1, 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_1; j++)
                {
                    printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                    MPI_Send(&vector_workeri_1[j], 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                }

                //Coordonator 2
                printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                MPI_Send(&nr_workeri_2, 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_2; j++)
                {
                    printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                    MPI_Send(&vector_workeri_2[j], 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                }

                // Coordonator 3
                printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                MPI_Send(&nr_workeri_3, 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_3; j++)
                {
                    printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                    MPI_Send(&vector_workeri_3[j], 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                }


            }
        }

        // Coordonator 2 primeste vectorul de la Coordonator 3
        {
            MPI_Recv(&n, 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
            v = malloc(n * sizeof(int));
            if(v == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0 ; i < n; i++)
                MPI_Recv(&v[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD, &status);
        }

        // Coordonator 2 trimite vectorul catre Coordonator1
        {
            printf("M(%d,%d)\n", 2, 1);
            MPI_Send(&n, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
            for(i = 0 ; i < n; i++)
            {
                printf("M(%d,%d)\n", 2, 1);
                MPI_Send(&v[i], 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
            } 
        }
        // toate procesele coordonator cunosc vectorul

        int *v_copie = malloc(n * sizeof(int));
        if(v_copie == NULL)
        {
            printf("Eroare alocare\n");
            return -1;
        }
        for(i = 0 ; i < n; i++)
            v_copie[i] = v[i];


        //coordonator 2 trimite la workeri calculele si primeste rezultatul
        contor = 0;
        for( i = 0; i < nr_workeri_2; i++)
        {
            id = vector_workeri_2[i] - 4;
            start = id * (double)n / nr_workeri_total ;
            stop = min( (id + 1) * (double)n / nr_workeri_total, n);

            unit = stop - start;

            printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
            MPI_Send(&unit, 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
            
            for( j = start; j < stop; j++)
            {
                printf("M(%d,%d)\n", 2, vector_workeri_2[i]);
                MPI_Send(&v[j], 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD);
                if(v[j] != 0)
                    contor++;
                MPI_Recv(&v[j], 1, MPI_INT, vector_workeri_2[i], 10, MPI_COMM_WORLD, &status);

            }

        }


        //Coord 2 prim calc de la coord 1
        int contor_primit;
        MPI_Recv(&contor_primit, 1, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);

        for(j = 0; j < contor_primit; j++)
        {
            int index;
            MPI_Recv(&index, 1, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);
            int val;
            MPI_Recv(&val, 1, MPI_INT, 1, 10, MPI_COMM_WORLD, &status);
            v[index] = val;
        }
        contor = contor + contor_primit;
    

        // coord 2 trimite catre coord 3
        {
            printf("M(%d,%d)\n", 2, 3);
            MPI_Send(&contor, 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
            for(i = 0; i < n ; i++)
            {
                if(v[i] != v_copie[i])
                {
                    printf("M(%d,%d)\n", 2, 3);
                    MPI_Send(&i, 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
                    printf("M(%d,%d)\n", 2, 3);
                    MPI_Send(&v[i], 1, MPI_INT, 3, 10, MPI_COMM_WORLD);
                }   

            }

        }

    }
    else if( rank == 3)
    {
        FILE* in = fopen( "cluster3.txt", "rt" );
        fgets( buff, SIZE, in );
        nr_workeri_3 = atoi(buff);

        vector_workeri_3 = malloc(nr_workeri_3 * sizeof(int));
        if(vector_workeri_3 == NULL )
        {
            printf("Eroare alocare\n");
            return -1;
        }
        int i = 0;
        for( i = 0; i < nr_workeri_3; i++)
        {
            fgets(buff, SIZE, in);
            vector_workeri_3[i] = atoi(buff);
            printf("M(%d,%d)\n", rank, vector_workeri_3[i]);
            MPI_Send(&rank, 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);

        }

        fclose(in);

        // Coordonator 3 primeste de la Coordonator 0
        {
            MPI_Recv(&nr_workeri_0, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
            vector_workeri_0 = malloc(nr_workeri_0 * sizeof(int));
            if(vector_workeri_0 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0 ; i < nr_workeri_0; i++)
                MPI_Recv(&vector_workeri_0[i], 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        }


        // Coordonator 3 trimite catre Coordonator 2
        {
            // trimite ce stie de la 0
            printf("M(%d,%d)\n", 3, 2);
            MPI_Send(&nr_workeri_0, 1, MPI_INT, 2, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_0; i++)
            {
                printf("M(%d,%d)\n", 3, 2);
                MPI_Send(&vector_workeri_0[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
            }


            // trimite ce stie de la el
            printf("M(%d,%d)\n", 3, 2);
            MPI_Send(&nr_workeri_3, 1, MPI_INT, 2, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_3; i++)
            {
                printf("M(%d,%d)\n", 3, 2);
                MPI_Send(&vector_workeri_3[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
            }
        }

        // facem receive de la 2
        {

            // ce a primit de la Coordonator 1
            MPI_Recv(&nr_workeri_1, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
            vector_workeri_1 = malloc(nr_workeri_1 * sizeof(int));
            
            if(vector_workeri_1 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_1; i++)
                MPI_Recv(&vector_workeri_1[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
        

            // ce era al lui
            MPI_Recv(&nr_workeri_2, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
            vector_workeri_2 = malloc(nr_workeri_2 * sizeof(int));
            
            if(vector_workeri_2 == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0; i < nr_workeri_2; i++)
                MPI_Recv(&vector_workeri_2[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
        }

        // In acest moment Coordonator 3 are topologia completa si o afiseaza
        afisare(rank, vector_workeri_0, nr_workeri_0, vector_workeri_1, nr_workeri_1,
            vector_workeri_2, nr_workeri_2, vector_workeri_3, nr_workeri_3);


        // Coordonator 3 trimite catre Coordonator 0
        {
            // trimite informatii despre Coordonator 1
            printf("M(%d,%d)\n", 3, 0);
            MPI_Send(&nr_workeri_1, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_1; i++)
            {
                printf("M(%d,%d)\n", 3, 0);
                MPI_Send(&vector_workeri_1[i], 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
            }

            //trimitem informatii despre Coordonator 2
            printf("M(%d,%d)\n", 3, 0);
            MPI_Send(&nr_workeri_2, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_2; i++)
            {
                printf("M(%d,%d)\n", 3, 0);
                MPI_Send(&vector_workeri_2[i], 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
            }

            //trimitem informatii despre Coordonator 3
            printf("M(%d,%d)\n", 3, 0);
            MPI_Send(&nr_workeri_3, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);

            for(i = 0 ; i < nr_workeri_3; i++)
            {
                printf("M(%d,%d)\n", 3, 0);
                MPI_Send(&vector_workeri_3[i], 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
            }
        }

        // Coordonator 3 anunta topologia tuturor proceselor worker pe care le are fiecare Coordonator
        {   
            for( i = 0; i < nr_workeri_3; i++)
            {
                // Coordonator 0
                printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                MPI_Send(&nr_workeri_0, 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                for(int j = 0; j < nr_workeri_0; j++)
                {
                    printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                    MPI_Send(&vector_workeri_0[j], 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                }

                // Coordonator 1
                printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                MPI_Send(&nr_workeri_1, 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_1; j++)
                {
                    printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                    MPI_Send(&vector_workeri_1[j], 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                }

                //Coordonator 2
                printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                MPI_Send(&nr_workeri_2, 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_2; j++)
                {
                    printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                    MPI_Send(&vector_workeri_2[j], 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                }

                // Coordonator 3
                printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                MPI_Send(&nr_workeri_3, 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                for( int j = 0; j < nr_workeri_3; j++)
                {
                    printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                    MPI_Send(&vector_workeri_3[j], 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                }


            }
        }

        // Coordonator 3 primeste vectorul de la Coordonator 0
        {
            MPI_Recv(&n, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
            v = malloc(n * sizeof(int));
            if(v == NULL)
            {
                printf("Eroare alocare\n");
                return -1;
            }

            for(i = 0 ; i < n; i++)
                MPI_Recv(&v[i], 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        }


        // Coordonator 3 trimite vectorul catre Coord 2
        {
            printf("M(%d,%d)\n", 3, 2);
            MPI_Send(&n, 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
            for(i = 0 ; i < n; i++)
            {
                printf("M(%d,%d)\n", 3, 2);
                MPI_Send(&v[i], 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
            }
        
        }

        // toate procesele coordonator cunosc vectorul



        // coordonator 3 trimite la workeri calculele si primeste rezultatul
        int *v_copie = malloc(n * sizeof(int));
        if(v_copie == NULL)
        {
            printf("Eroare alocare\n");
            return -1;
        }
        for(i = 0 ; i < n; i++)
            v_copie[i] = v[i];

        int contor = 0;
        for( i = 0; i < nr_workeri_3; i++)
        {
            id = vector_workeri_3[i] - 4;
            start = id * (double)n / nr_workeri_total ;
            stop = min( (id + 1) * (double)n / nr_workeri_total, n);

            unit = stop - start;

            printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
            MPI_Send(&unit, 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
            
            for( j = start; j < stop; j++)
            {
                printf("M(%d,%d)\n", 3, vector_workeri_3[i]);
                MPI_Send(&v[j], 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD);
                if(v[j] != 0)
                    contor++;
                MPI_Recv(&v[j], 1, MPI_INT, vector_workeri_3[i], 10, MPI_COMM_WORLD, &status);

            }

        }

        //coord 3 prim de la coord 2
      
        int contor_primit;
        MPI_Recv(&contor_primit, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);

        for(j = 0; j < contor_primit; j++)
        {
            int index;
            MPI_Recv(&index, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
            int val;
            MPI_Recv(&val, 1, MPI_INT, 2, 10, MPI_COMM_WORLD, &status);
            v[index] = val;
        }
        contor = contor + contor_primit;
        


        // coord 3 trimite catre coord 0
        {
            printf("M(%d,%d)\n", 3, 0);
            MPI_Send(&contor, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
            for(i = 0; i < n ; i++)
            {
                if(v[i] != v_copie[i])
                {
                    printf("M(%d,%d)\n", 3, 0);
                    MPI_Send(&i, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
                    printf("M(%d,%d)\n", 3, 0);
                    MPI_Send(&v[i], 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
                }   

            }

        }
    
    
    }
    else
    {
        // Proces de tip worker
    
        MPI_Recv(&parinte, 1, MPI_INT, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, &status);
        
       
        // Facem receive de la Coordonatorul nostru
        
        // primim informatii despre coordonator 0
        MPI_Recv(&nr_workeri_0, 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);
        vector_workeri_0 = malloc(nr_workeri_0 * sizeof(int));
        
        if(vector_workeri_0 == NULL)
        {
            printf("Eroare alocare\n");
            return -1;
        }

        for(i = 0; i < nr_workeri_0; i++)
            MPI_Recv(&vector_workeri_0[i], 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);
        
        
        // primim informatii despre coordonator 1
        MPI_Recv(&nr_workeri_1, 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);
        vector_workeri_1 = malloc(nr_workeri_1 * sizeof(int));
        
        if(vector_workeri_1 == NULL)
        {
            printf("Eroare alocare\n");
            return -1;
        }

        for(i = 0; i < nr_workeri_1; i++)
            MPI_Recv(&vector_workeri_1[i], 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);

        // primim informatii despre coordonator 2
        MPI_Recv(&nr_workeri_2, 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);
        vector_workeri_2 = malloc(nr_workeri_2 * sizeof(int));
        
        if(vector_workeri_2 == NULL)
        {
            printf("Eroare alocare\n");
            return -1;
        }

        for(i = 0; i < nr_workeri_2; i++)
            MPI_Recv(&vector_workeri_2[i], 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);

        // primim informatii despre coordonator 3
        MPI_Recv(&nr_workeri_3, 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);
        vector_workeri_3 = malloc(nr_workeri_3 * sizeof(int));
        
        if(vector_workeri_3 == NULL)
        {
            printf("Eroare alocare\n");
            return -1;
        }

        for(i = 0; i < nr_workeri_3; i++)
            MPI_Recv(&vector_workeri_3[i], 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);

        // In acest moment Worker[rank] are topologia completa si o afiseaza
        afisare(rank, vector_workeri_0, nr_workeri_0, vector_workeri_1, nr_workeri_1,
        vector_workeri_2, nr_workeri_2, vector_workeri_3, nr_workeri_3);

        


    
        // Worker primeste chunckul de calculat
       
        
        MPI_Recv(&unit, 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);
        
        v = malloc(unit * sizeof(int));
        if(v == NULL)
        {
            printf("Eroare alocare\n");
            return -1;
        }
        for(i = 0 ; i < unit; i++)
        {
            MPI_Recv(&v[i], 1, MPI_INT, parinte, 10, MPI_COMM_WORLD, &status);
            v[i]*=5;
            printf("M(%d,%d)\n", rank, parinte);
            MPI_Send(&v[i], 1, MPI_INT, parinte, 10, MPI_COMM_WORLD);   
        }
        
            
        
        
        // Worker trimite la Coordonator

    }

        
    


    MPI_Finalize();

}

