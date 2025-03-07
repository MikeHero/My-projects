#include "tema.h"


// functia intoarce 1 daca stiva S este vida, 0 altfel


void Push(TLG *L, int x)
{
	TLG aux = alocCelulaStiva(x);
	if( *L == NULL)
		*L = aux;
	else
	{
		aux->urm = *L;
		*L = aux;
	}
}

void Pop(TLG *L, int *x)
{
	TLG p = *L;
	*L = (*L)->urm;	
	
	TThread *y = ((TThread*)(p->info));
	*x = y->thread_id;
	
	free(p->info);
	free(p);
}

void initS(TLG *L, int n)
{
	int i;
	for(i = n - 1; i >= 0; i--)
	{
		Push(L, i);
	}
}

//	functie auxiliara cu rol in debugging
void afisareStiva( TLG *L )
{
	int x;
	TLG s_aux = NULL;

	while( (*L) != NULL)
	{
		Pop(L, &x);
		printf("%d ", x);
		Push(&s_aux, x);
	}
	printf("\n");
	
	while( s_aux != NULL)
	{
		Pop(&s_aux, &x);
		Push(L, x);
	}
}

void DistrugeS(TLG *L)
{
	int x;
	while( *L != NULL)
	{
		Pop(L, &x);
	}
}