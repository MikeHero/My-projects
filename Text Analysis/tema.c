/* Mihai Ghioca 321CB */

#include "tema.h"

int codHash( void * element )
{
	char *cuvant = (char*)element;
	if( 'A' <= cuvant[0] && cuvant[0] <= 'Z' )
		return cuvant[0] - 'A';
	if( 'a' <= cuvant[0] && cuvant[0] <= 'z' )
		return *cuvant - 'a';
	// daca nu primim un cuvant care incepe cu litera mare/mica il ignoram
	return -1;
}


int main( int argc, char** argv )
{
	int my_M = 26;
	TH* h = initTH( my_M, codHash );

	FILE* in = fopen( argv[1], "rt" );
	if( in == NULL)
	{	
		printf( "Eroare deschidere fisier\n" );
		return -1;
	}
	char buff[SIZE];
	char copie[SIZE];
	
	// cat timp citim din fisier
	while( fgets( buff, SIZE, in ) )
	{
		int dim = strlen( buff );
		
		// eventual eliminam \n
		if(buff[dim - 1] == '\n')
			buff[--dim]='\0';

		// strncpy dubla o litera cauzand erori
		strcpy(copie, buff);

		char* p = strtok( copie, " .," );


		// tratam operatia de insert
		if( strcmp("insert", p) == 0)
		{
			p = strtok( NULL, " .," );
			
			while(p)
			{

				int pozitie = codHash( p );
				int length = strlen( p );
				if( 0 <= pozitie && pozitie <= 25 && length >=3 )
				{
					insereazaCuvant( h, p, length, pozitie );
				}
				p = strtok( NULL, " .," );

			}
		}
		else 
		{	
			//tratam operatia de print
			if( strcmp( "print", p ) == 0 )
			{
				p = strtok( NULL, " .,");
				if( p == NULL)
					AfiTH(h);
				else
				{
					// afisare cuvinte care incep cu litera *p si au o anumita lungime 
					// print a 5
					if( ('a' <= *p && *p <= 'z') || ('A' <= *p && *p <= 'Z') )
					{
						int my_poz = codHash(p);
						p = strtok(NULL, " .,");
						int lungime = atoi(p);
						
						TLI phe ;
						for( phe = h->v[my_poz]; phe != NULL; phe = phe->urm )
						{
							if( phe->index == lungime)
							{	
								printf("(%d:", lungime);
								// avem o functie care stie sa afiseze toate elementele din Lista generica 
								
								AfisareListaG(phe->info, afisare);
								printf(")\n");
								break;
							}
							
						}

					}
					else
					{
						// afisare cuvinte care apar de maxim n ori
						if( '1' <= *p && *p <= '9')
						{
							int n = *p;
							n = *p - '0';	// sau scadeam 48 deoarece '0' = 48
							// avem o functia care rezolva aceasta sarcina
							AfinTHN(h, n);
						}
					}
				}
			}
		}
	}
	

	
	DistrTH(&h);
	fclose(in);

	return 0;
}
