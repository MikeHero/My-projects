/* Mihai Ghioca 321CB */

#include "tema.h"

TH* initTH(size_t M, TFHash fh)
{
	TH* ath = (TH*)malloc(sizeof(TH));
	if( ath == NULL)
	{	
		printf("Eroare alocare Tabela Hash\n");
		return NULL;
	}
	
	ath->v = calloc(M, sizeof(TLI));
	if( ath->v == NULL)
	{
		printf("Eroare alocare vector din Tabela Hash\n");
		free(ath);
		return NULL;
	}

	ath->M = M;
	ath->fh = fh;

	return ath;
}

void AfiTH( TH* ah)
{
    TLI p;
    int i;

    for(i = 0; i < ah->M; i++) 
    {
        p = ah->v[i];
        if(p) 
        {
            printf("pos %d: ", i);
            AfisareListaIndex(p);
        }
    }
}

int comparaCuv(void *e1, void* e2)
{
	TCuv* a = (TCuv*)e1;
	TCuv* b = (TCuv*)e2;
	if( b->frecventa > a->frecventa )
		return -1;
	if( b->frecventa < a->frecventa)
		return 1;
	 
	return strcmp(b->cuvant, a->cuvant);
}

void insereazaCuvant( TH* h, char* cuvant, int length, int poz )
{
	int dim = length;
	
	// Prima celula din lista index
	if( h->v[poz] == NULL )
	{
		h->v[poz] = alocCelulaIndex(cuvant);
	}

	else
	{
		// inseram in lista de lungime corespunzatoare daca exista.
		TLI p, ant = NULL;
		p = h->v[poz];
		
		while ( p )
		{	
			if( dim <= p -> index)
			{	
				// am gasit acea lista verticala si ne dorim sa inseram in aceasta
				break;
			}
			ant = p;
			p = p->urm;
		}

		// nu am gasit acea lista index, acea lista verticala, o vom crea noi
		//verificam daca trebuie sa inseram lista verticala la inceput
		if(	ant == NULL && p->index != dim)
		{
			TLI aux = alocCelulaIndex( cuvant );
			aux->urm = h->v[poz];
			h->v[poz] = aux;
			return ;
		}

		// nu am gasit acea lista index, acea lista verticala, o vom crea noi si inseram la finalul listei INDEX
		// verificam daca trebuie sa inseram acea lista index, acea lista verticala la inceput
		if( p == NULL )
		{
			TLI aux = alocCelulaIndex( cuvant );
			ant->urm = aux;
			return ;
		}

		// Nu am gasit acea lista index, o cream, si o inseram pe pozitia Corespunzatoare in lista index
		// exemplu inseram Lista avand indexul 6 cu singura celula cu un cuvant de dimens 6, 
		// in lista cu index care contin cuvinte de dimens 4,8 => TListaIndex 4, 6, 8
		if( p && p->index != dim)
		{
			TLI aux = alocCelulaIndex ( cuvant );
			ant->urm = aux;
			aux->urm = p;
			return ;
		}
		
		if( p && p->index == dim )
		{
			// am gasit lista index unde trebuie sa fac inserarea
			TLG L = p->info;
			if( cauta(L, cuvant) == 0 )
			{
				// nu exista acest cuvant in lista de cuvinte
				// se introduce cuvantul unic nou in lista
				TLG aux2 = alocCelulaG( cuvant);
				Ins_OrdLG(&(p->info), aux2, comparaCuv);
			}

			else
			{
				// daca acesta exista deja incrementam frecventa si reordonam, nu mai alocam nicio celula suplimentara
				TLG p1, ant1 = NULL;
				for( p1 = L; p1 != NULL; ant1 = p1, p1 = p1->urm)
				{	
					//Nu mergea strcasecmp din prima IDK WHY
					if( ((TCuv*)(p1->info))->cuvant[0] == cuvant[0] && 
						strcmp( ((TCuv*)(p1->info))->cuvant+1, cuvant+1 ) == 0 )	
					{
						// gasesc sigur, din functia cauta, altfel nu intra pe else de la linia 125
						break;
					}	
				}

				//extrag celula, incrementez frecventa de aparatie a cuvantului
				TLG aux2 = p1;
				((TCuv*)aux2->info)->frecventa++;
				
				//daca era prima celula
				if(ant1 == NULL)
				{	
					p->info = L->urm;
				}
				else
				{
					ant1->urm = p1->urm;
				}
				aux2->urm = NULL;
				Ins_OrdLG(&(p->info), aux2, comparaCuv);

			}
		}


	}
}

int f(TLG L, int n)		// intoarce 1 daca celula curenta din ListaG are cel putin o celula de printat pentru N dat
{						// (celulele verticale.)
	TLG p;
	for( p = L; p != NULL; p = p->urm)
		if( ((TCuv*)p->info)->frecventa <= n )
			return 1;
	return 0;
}

int f2(TLI L, int n)	//intoarce 1 daca celula curenta din lista index are cel putin o celula de printat pentru N dat
{
	TLG p = L->info;
	return f(p, n);
	
}

void AfisareListaGN(TLG L, TF afiEL, int n, int (*f)(TLG L, int n) )
{	
	int printat = 0;
	for( ; L != NULL; L = L->urm)
	{
		if( ((TCuv*)L->info)->frecventa <= n)
		{	
			afiEL(L->info);
			printat = 1;
		}
		if( f( L->urm, n ) && printat==1)
			printf(", ");
	}
}

void AfisareListaIndexN(TLI L, int n)
{
	TLI p;
	for( p = L; p != NULL; p = p->urm)
	{
		if(f2(p, n) == 1)
		{
			printf("(%d", p->index);
			printf(": ");
			AfisareListaGN(p->info, afisare, n, f);
			printf(")");
		}

	}
	
	printf("\n");
}

int f3(TLI L, int n)	// intoarce 1 daca in intrega liste de index exista minim o celula care are o lista verticala
{						// pe care va trebui sa o printam
	TLI p ;
	for (p = L; p!= NULL; p = p->urm)
	{	
		TLG aux = p->info;
		if( f(aux, n)==1)
			return 1;
	}
	return 0;
	
}

void AfinTHN( TH* ah, int n)
{
    TLI p;
    int i;

    for(i = 0; i < ah->M; i++) 
    {
        p = ah->v[i];
        if(p && f3(p, n)) 
        {
            printf("pos%d: ", i);
            AfisareListaIndexN(p, n);
        }
    }
}



void DistrTH(TH** ah)
{
    TH *h = *ah;

    for(int i = 0 ; i < h->M; i++)
    	DistrugeLI(&(h->v[i]), free_el);

    
    free((*ah)->v);
    free(h);
    *ah = NULL;
}
