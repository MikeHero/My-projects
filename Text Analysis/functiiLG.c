/* Mihai Ghioca 321CB */

#include "tema.h"

TLI alocCelulaIndex(char* cuvant)
{
	TLI aux = calloc(1, sizeof( TCelulaIndex));
	if( !aux )
	{
		printf("Eroare alocare aux in alocCelulaIndex\n");
		return NULL;
	}
	
	aux->info = alocCelulaG(cuvant);

	int dim = strlen(cuvant);
	aux->index = dim;
	aux->urm = NULL;

	return aux;
	 
}

TLG alocCelulaG(char* cuvant)
{
	TLG aux = calloc( 1, sizeof(TCelulaG));
	if( !aux )
	{
		printf("Eroare alocare aux in alocCelulaG\n");
		return NULL;
	}

	TCuv* cuv = calloc(1, sizeof(TCuv));
	if( !cuvant )
	{
		free(aux);
		printf("eroare alocare cuvant in functia alocCelulaG\n");
		return NULL;
	}

	cuv->cuvant = calloc(LEN , sizeof(char));
	if( !cuv->cuvant )
	{
		free(cuv);
		free(aux);
		printf("Eroare alocare camp cuvant in alocCelulaG\n");
		return NULL;
	}

	int dim = strlen(cuvant);
	strncpy(cuv->cuvant, cuvant, dim);
	cuv->frecventa = 1;

	aux->info = cuv;
	aux->urm = NULL;
	return aux;
}


void AfisareListaIndex(TLI L)
{
	TLI p;
	for( p = L; p != NULL; p = p->urm)
	{
		printf("(%d", p->index);
		printf(":");
		AfisareListaG(p->info, afisare);
		printf(")");
	}
	printf("\n");
}

void afisare(void* elem)
{
	TCuv* cuv = (TCuv*)elem;
	printf("%s/%d", cuv->cuvant, cuv->frecventa);
}

void AfisareListaG(TLG L, TF afiEL)
{
	for( ; L != NULL; L = L->urm)
	{
		afiEL(L->info);
		if( L->urm )
			printf(", ");
	}
}

void Ins_OrdLG(TLG* aL, TLG aux, int (*fcmp)(void *, void*) )
{
	TLG L = *aL;
	TLG p, ant = NULL;


	// Lista vida -> Lista devine noul element introdus
	if( L == NULL)
	{
		L = aux;
	}
	else
	{
		// Lista nu este vida
		if( fcmp( aux->info, L->info ) >= 0)
		{
			// daca elementul pe care doresc sa-l introduc este mai mic, comform relatiei de ordine, 
			// trebuie inserat primul si mutat inceputul listei pe noua celula
			aux->urm = L;
			L = aux;
		}
		else
		{
			// inserarea se va realiza incepand cu minim a doua pozitie
			p = L;
			while( p && fcmp( aux->info, p->info ) < 0 ) 
			{
				// cat timp relatia de ordonare este satisfacuta, continui sa parcurg lista element cu element
				ant = p;
				p = p->urm;
			}
			if( p == NULL)
			{	
				// inseram pe ultima pozitie
				ant->urm = aux;
			}
			else
			{
				// inseram pe o pozitie intermediara
				// inseram aux intre ant si p cu refacerea legaturilor
				aux->urm = p;
				ant->urm = aux;
			}
		
		}
	}
	*aL = L;
	
}

int cauta(TLG L, char* cuvant )
{
	TLG p;
	TCuv * cuv;
	for( p = L; p != NULL; p = p->urm)
	{
		cuv = (TCuv*)(p->info);
		if( strcmp(cuv->cuvant, cuvant) == 0)
			return 1;
	}
	return 0;
}

void free_el(void* el)
{
	TCuv* x = (TCuv*)el;
	free(x->cuvant);
	free(x);
}

void DistrugeLG(TLG* aL, TF free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}



void DistrugeLI(TLI* aL, TF free_elem)
{
	while(*aL != NULL)
    {
        TLI aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        DistrugeLG(&aux->info, free_el);  		
        *aL = aux->urm; 
        free(aux->info);   							
        free(aux);  								
    }
}