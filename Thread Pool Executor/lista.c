#include "tema.h"


TLGC alocCelulaCoada(unsigned short id, unsigned int timp_executie, char prioritate, int thread, unsigned int timp_initial)
{
	TLGC aux = calloc(1,  sizeof(TCelulaGC));
	if( !aux )
	{
		printf("Eroare alocare celula in lista pentru coada\n");
		return NULL;
	}

	TTask *t = calloc(1, sizeof(TTask));
	if( t == NULL)
	{
		printf("Eroare alocare pointer la structura de tip Task\n");
		free(aux);
		return NULL;
	}

	t->task_id = id;
	t->prioritate = prioritate;
	t->initial_time = timp_initial;
	t->timp = timp_executie;
	t->thread = thread;

	aux->info = t;
	aux->urm = NULL;
	aux->sf = aux;

	return aux;
}

TLG alocCelulaStiva(int x)
{
	TLG aux = calloc(1, sizeof(TCelulaG));
	if( !aux )
	{
		printf("Eroare alocare celula in lista pentru stiva\n");
		return NULL;
	}

	TThread *t = calloc(1, sizeof(TThread));
	if( t == NULL)
	{
		printf("Eroare alocare pointer la structura de tip thread\n");
		free(aux);
		return NULL;
	}

	t->thread_id = x;
	aux->info = t;
	aux->urm = NULL;

	return aux;
}


