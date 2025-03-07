#include "tema.h"

// functie de ordonare pentru elementele din coada waiting
int fcmp(void *a, void *b)
{
	TTask *x = (TTask*)a;
	TTask *y = (TTask*)b;

	// descrescator prioritate
	if( x->prioritate > y->prioritate )
		return 1;
	// crescator dupa timp de executie ramas, in caz de prioritati egale
	if( ( x->prioritate == y->prioritate ) && ( x->timp < y->timp ) )
		return 1;
	// crescator dupa ID, in caz de prioritate si timp executie egal
	if( ( x->prioritate == y->prioritate ) && ( x->timp == y->timp ) && ( x->task_id < y->task_id) )
		return 1;
	return -1;
}
void IntrQ(TLGC *L, TTask t)
{
	TLGC aux = alocCelulaCoada(t.task_id, t.timp, t.prioritate, t.thread, t.initial_time );
	if( *L == NULL )
	{	
		*L = aux;
		(*L)->sf = aux;
	}
	else
	{
		(*L)->sf->urm = aux;
		(*L)->sf= aux;
	}

}
void ExtrQ(TLGC *L, TTask *x)
{
	TLGC p = *L;
	*L = (*L)->urm;
	TTask *t = (TTask*)(p->info);
	
	x->prioritate = t->prioritate;
	x->timp = t->timp;
	x->task_id = t->task_id;
	x->thread = t->thread;
	x->initial_time = t->initial_time;
	
	free(p->info);
	free(p);

}

void IntrQOrd(TLGC *L, TTask task )
{
	
	TLGC coada_aux = NULL;
	TLGC aux = alocCelulaCoada(task.task_id, task.timp, task.prioritate, task.thread, task.initial_time);
	if( *L == NULL )
	{	
		*L = aux;
	}
	else
	{
		TTask t; 
		if( fcmp( (*L)->info, aux->info) < 0 ) // inserez aux la inceput
		{
			while( *L != NULL )
			{
				ExtrQ(L, &t);
				IntrQ(&coada_aux, t);
			}

			*L = aux;
			
			while( coada_aux != NULL )
			{
				ExtrQ(&coada_aux, &t);
				IntrQ(L, t);
			}
		}
		else
		{	
			// coada nu e vida si nici nu inserez pe prima pozitie
			while( ( *L != NULL ) && ( fcmp ( (*L)->info, aux->info ) > 0 ) )
			{
				ExtrQ(L, &t);
				IntrQ(&coada_aux, t);
			}
			ExtrQ(&aux, &t);
			IntrQ(&coada_aux, t);
			while( (*L) != NULL )
			{
				ExtrQ(L, &t);
				IntrQ(&coada_aux, t);
			}

			while(coada_aux != NULL)
			{
				ExtrQ(&coada_aux, &t);
				IntrQ(L, t);
			}
		}
		
	}

}

void afisare_taskW(void* x, FILE* out)
{
	TTask t = *( (TTask *)x );
	fprintf(out, "(%d: priority = %d, remaining_time = %d)", t.task_id, t.prioritate, t.timp );
}

void afisareCoadaW(TLGC *L, FILE* out)
{
	TLGC c_aux = NULL;
	TTask t;
	while( *L != NULL )
	{
		afisare_taskW((*L)->info, out); 
		if( (*L)->urm) 
			fprintf(out, ",\n");	// pentru a se respecta tiparul de afisare
		ExtrQ(L, &t);
		IntrQ(&c_aux, t);
	}
	//refac coada initiala
	while( c_aux != NULL )
	{
		ExtrQ(&c_aux, &t);
		IntrQ(L, t);
	}
}

void afisare_taskR(void* x, FILE* out)
{
	TTask t = *( (TTask *)x );
	fprintf(out, "(%d: priority = %d, remaining_time = %d, running_thread = %d)", 
							t.task_id, t.prioritate, t.timp, t.thread);
}

void afisareCoadaR(TLGC *L, FILE* out)
{
	TLGC c_aux = NULL;
	TTask t;
	while( *L != NULL )
	{
		afisare_taskR((*L)->info, out); 
		if( (*L)->urm) 
			fprintf(out, ",\n");	// pentru a se respecta tiparul de afisare
		ExtrQ(L, &t);
		IntrQ(&c_aux, t);
	}
	//refac coada initiala
	while( c_aux != NULL )
	{
		ExtrQ(&c_aux, &t);
		IntrQ(L, t);
	}
}

void afisare_taskF(void* x, FILE* out)
{
	TTask t = *( (TTask *)x );
	fprintf(out, "(%d: priority = %d, executed_time = %d)", t.task_id, t.prioritate, t.initial_time );
}

void afisareCoadaF(TLGC *L, FILE* out)
{
	TLGC c_aux = NULL;
	TTask t;
	while( *L != NULL )
	{
		afisare_taskF((*L)->info, out); 
		if( (*L)->urm) 
			fprintf(out, ",\n");	// pentru a se respecta tiparul de afisare
		ExtrQ(L, &t);
		IntrQ(&c_aux, t);
	}
	//refac coada initiala
	while( c_aux != NULL )
	{
		ExtrQ(&c_aux, &t);
		IntrQ(L, t);
	}
}

void DistrugeQ(TLGC *L)
{
	TTask t;
	while(*L)
	{
		ExtrQ(L, &t);
	}
}