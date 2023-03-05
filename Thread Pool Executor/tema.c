#include "tema.h"

// intoarce primul ID disponibil; folosit asignarea unui ID la crearea unui task
int get_disponibil(int v[])
{
	int i;
	for( i = 1; i < LEN; i++)
		if(v[i] == 0)
		{	
			v[i] = 1;
			return i;
		}
	return -1;
}

void add_tasks(char buff[], FILE* out, int v[], TLGC* coada_waiting, TLG* Stiva_thread)
{	
	char *p;
	int number_of_tasks, execution_time, priority;
	
	p = strtok( buff, " " );
	p = strtok( NULL, " " );
	number_of_tasks = atoi(p);
	p = strtok(NULL, " ");
	execution_time = atoi(p);
	p = strtok(NULL, " ");
	priority = atoi(p);

	int i, id, thread_number = -1;
	TTask t;
	for( i = 1; i <= number_of_tasks; i++ )
	{	
		id = get_disponibil(v);
		fprintf(out, "%s %d.\n", "Task created successfully : ID", id);

		t.task_id = id;
		t.prioritate = priority;
		t.timp = execution_time;
		t.initial_time = t.timp;
		t.thread = thread_number;
		
		IntrQOrd(coada_waiting, t);
	}
}

void get_task(char buff[], FILE* out, TLGC* coada_waiting, TLGC* coada_running, TLGC* coada_finished)
{
	char* p;
	int id;
	p = strtok(buff, " ");
	p = strtok(NULL, " ");
	id = atoi(p);
	int gasit = 0;
	TLGC c_aux = NULL;
	TTask t;


	// se cauta Taskul cu ID precizat in coada running
	while( *coada_running != NULL)
	{
		ExtrQ(coada_running, &t);
		IntrQ(&c_aux, t);
		if(t.task_id == id)
		{
			fprintf(out, "Task %d is running (remaining_time = %d).\n", id, t.timp);
			gasit = 1;	// daca l-am gasit il printez si nu mai caut alt ID identic in alta coada 
			id = 999;
		}
	}
	//refacere coada initiala
	while( c_aux != NULL )
	{
		ExtrQ(&c_aux, &t);
		IntrQ(coada_running, t);
	}


	if( gasit == 0)
	{
		// se cauta Taskul cu ID precizat in coada waiting
		while( *coada_waiting != NULL )
		{
			ExtrQ(coada_waiting, &t);
			IntrQ(&c_aux, t);
			if( t.task_id == id )
			{
				fprintf(out, "Task %d is waiting (remaining_time = %d).\n", id, t.timp);
				id = 999;
				gasit = 1;	// daca l-am gasit il printez si nu mai caut alt ID identic in alta coada 
			}
		}

		//refacere coada initiala
		while( c_aux != NULL )
		{
			ExtrQ(&c_aux, &t);
			IntrQ(coada_waiting, t);
		}
	}
	
	if( gasit == 0)
	{

		// se cauta Taskul cu ID precizat in coada finished
		while( *coada_finished != NULL)
		{
			ExtrQ(coada_finished, &t);
			IntrQ(&c_aux, t);
			if(t.task_id == id /*&& t.timp != 0*/)
			{
				fprintf(out, "Task %d is finished (executed_time = %d).\n", id, t.initial_time);
				id = 999;	// daca l-am gasit il printez si nu mai caut alt ID identic in alta coada 
				gasit = 1;
			}
		}
		//refacere coada initiala
		while( c_aux != NULL )
		{
			ExtrQ(&c_aux, &t);
			IntrQ(coada_finished, t);
		}
	}
	
	if( gasit == 0 )
	{
		fprintf(out, "Task %d not found.\n", id);
	}

}

void get_thread(char buff[], FILE* out, TLG* Stiva_thread, TLGC* coada_running)
{
	char* p;
	int id, id_cautat;
	p = strtok(buff, " ");
	p = strtok(NULL, " ");
	id_cautat = atoi(p);
		
	TLG s_aux = NULL;

	// se cauta threadul cu ID precizat in stiva de thread uri
	while( *Stiva_thread != NULL )
	{
		Pop(Stiva_thread, &id);
		if(id == id_cautat)
		{	
			fprintf(out,"Thread %d is idle.\n", id);
		}
		Push(&s_aux, id);
	}
	// refacere stiva initiala
	while( s_aux != NULL)
	{
		Pop( &s_aux, &id);
		Push( Stiva_thread, id);
	}

	//se cauta threadul cu ID specificat in coada running
	TTask t;
	TLGC c_aux = NULL;
	while( *coada_running != NULL)
	{
		ExtrQ(coada_running, &t);
		if(t.thread == id_cautat && (t.timp != 0))
		{
			fprintf(out,"Thread %d is running task %d (remaining_time = %d).\n", id_cautat, t.task_id, t.timp);
		}
		IntrQ(&c_aux, t);
	}

	// se reface coada running
	while( c_aux != NULL )
	{
		ExtrQ(&c_aux, &t);
		IntrQOrd(coada_running, t);
	}
}

void print_waiting(FILE* out, TLGC* coada_waiting)
{
	fprintf(out, "====== Waiting queue =======\n[");
	afisareCoadaW(coada_waiting, out);
	fprintf(out, "]\n");
}

void print_running(FILE* out, TLGC* coada_running)
{
	fprintf(out, "====== Running in parallel =======\n[");
	afisareCoadaR(coada_running, out);
	fprintf(out, "]\n");
}
void print_finished(FILE* out, TLGC* coada_finished)
{
	fprintf(out, "====== Finished queue =======\n[");
	afisareCoadaF(coada_finished, out);
	fprintf(out, "]\n");
}
// determina max_time al tuturor thread-urilor dintr-o coada data ca parametru
int max_time(TLGC* coada_running)
{
	int max = 0;
	TTask t;
	TLGC c_aux = NULL;
	while( *coada_running != NULL )
	{
		ExtrQ(coada_running, &t);
		if( t.timp > max)
			max = t.timp;
		IntrQ(&c_aux, t);
	}
	while( c_aux != NULL )
	{
		ExtrQ(&c_aux, &t);
		IntrQOrd(coada_running, t);
	}
	return max;
}

void run_aux(int time, FILE* out, TLG* Stiva_thread, TLGC* coada_waiting, TLGC *coada_running, 
																TLGC* coada_finished, int v[])
{

	TTask t;
	int x;
	TLGC c_aux = NULL;

	while( ( *Stiva_thread != NULL ) && ( *coada_waiting != NULL ))
	{
		Pop(Stiva_thread, &x);
		ExtrQ(coada_waiting, &t);
		t.thread = x;
		IntrQOrd(coada_running, t);
	}
	// printf("timpul_rulat_la_acest_pas %d\n", time);
	//se executa time unitati de timp
	while( *coada_running != NULL )
	{
		ExtrQ(coada_running, &t);
		
		// se introduce in finished
		if( t.timp <= time )
		{	
			t.timp = 0;
			IntrQ(coada_finished, t);
			x = t.thread;
			Push(Stiva_thread, x);
			v[t.task_id] = 0;
		}
		else
		{	
			//se introduce in c_aux ca sa fie reintrodus in running ulterior	
			t.timp = t.timp - time;
			IntrQ(&c_aux, t);
		}
	}

	while( c_aux != NULL )
	{
		ExtrQ(&c_aux, &t);
		if(t.timp > 0)
			IntrQOrd(coada_running, t);
	}
	// daca s-a eliberat un thread, ii asignez un nou task, iar taskul se muta din waiting in running
	while( (*coada_waiting != NULL ) && ( *Stiva_thread != NULL ))
	{
		Pop(Stiva_thread, &x);
		ExtrQ(coada_waiting, &t);
		t.thread = x; 
		IntrQ(coada_running, t);
	}
}

void run(char buff[], FILE* out, TLG** Stiva_thread, TLGC** coada_waiting, TLGC **coada_running, 
																TLGC** coada_finished, int v[], int q, int* all_my_time, int scrie)
{
	char* p = strtok(buff, " ");
	p = strtok(NULL, " ");
	int time = atoi(p);	// argumentul comenzii run
	if(	scrie == 1 )
	{
		fprintf(out, "%s", "Running tasks for ");
		fprintf(out, "%d ms...\n", time);
	}
	int my_time;

	// daca am taskuri si timp pozitiv, inseamna ca am ce sa pot rula
	while( (time > 0) && ( ((*(*coada_running) != NULL)) || ((*(*coada_waiting) != NULL)) ) )
	{
		if( time <= q )
			my_time = time;
		else
			my_time = q;

		int maxim_time_din_coada = max_time( *coada_running );

		if( maxim_time_din_coada < my_time )	
		{	
			my_time = maxim_time_din_coada;
		}
		*all_my_time = (*all_my_time) + my_time;
		//printf("Am modificat total_time: %d\n", *all_my_time);
		run_aux(my_time, out, *Stiva_thread, *coada_waiting, *coada_running, *coada_finished, v);
		time = time - my_time;
	}
}



int main(int argc, char** argv)
{	

	FILE* in = fopen(argv[1], "rt");
	if( in == NULL)
	{
		printf("Eroare deschidere fisier input\n");
		return -1;
	}

	FILE *out = fopen(argv[2], "wt");
	if( !out )
	{
		printf("Eroare deschidere fisier output\n");
		return -1;
	}

	int q, c, n;
	fscanf(in, "%d", &q);
	fscanf(in, "%d", &c);
	n = 2 * c;


	int all_my_time = 0;

	TLG Stiva_thread = NULL;
	TLGC coada_waiting = NULL, coada_running = NULL, coada_finished = NULL;
	
	// sa fie vizibile in exterior modificarile aduse in functia run
	TLG* adresa_stiva = &Stiva_thread;
	TLGC* adresa_coada_waiting = &coada_waiting;
	TLGC* adresa_coada_running = &coada_running;
	TLGC* adresa_coada_finished = &coada_finished;
	
	initS(&Stiva_thread, n);
	
	int v[LEN], i;

	for( i = 0; i < LEN; i++)
		v[i] = 0;

	char buff[SIZE], copie[SIZE]; 	
	fscanf(in,"%c", buff);	// citim \n
		
	int dim;
	char* p;
	int scrie = 1;
	while( fgets(buff, 200, in) )
	{
		dim = strlen( buff );

		if( buff[dim - 1] == '\n' )
		{
			buff[--dim] = '\0';
		}
		strncpy(copie, buff, dim + 1);

		p = strtok(buff, " ");
		
		if( strcmp(p, "add_tasks") == 0 )
			add_tasks(copie, out, v, &coada_waiting, &Stiva_thread);
		else if( strcmp(p, "get_task") == 0 )
			get_task(copie, out, &coada_waiting, &coada_running, &coada_finished);
		else if( strcmp(p, "get_thread") == 0 )
			get_thread(copie, out, &Stiva_thread, &coada_running);
		else if( strcmp(p, "print") == 0 )
		{
			p = strtok( NULL, " " );
			if(strcmp(p, "waiting") == 0 )
				print_waiting(out, &coada_waiting);
			else if( strcmp(p, "running") == 0)
				print_running(out, &coada_running);
			else if( strcmp(p, "finished") == 0)
				print_finished(out, &coada_finished);
		}
		else if( strcmp(p, "run") == 0)
		{		
			run(copie, out, &adresa_stiva, &adresa_coada_waiting, &adresa_coada_running, 
													&adresa_coada_finished, v, q, &all_my_time, scrie);
		}
		else if(strcmp(p, "finish") == 0)
		{
			// execut tot ce am in coada running
			while( coada_running != NULL )
			{
				
				int biggest_time = max_time( &coada_running );
				sprintf(copie, "run %d", biggest_time);	// creez o pseudo comanda run 
				run(copie, out, &adresa_stiva, &adresa_coada_waiting, &adresa_coada_running, 
														&adresa_coada_finished, v, q, &all_my_time, scrie);
			}
			// daca coada running este vida, 
			// mut din waiting in running, in limita thread-urilor disponibile
			while( coada_waiting != NULL && Stiva_thread != NULL )
			{	
				int x;
				TTask t;
				ExtrQ(&coada_waiting, &t);
				Pop(&Stiva_thread, &x);
				t.thread = x;
				IntrQOrd(&coada_running, t);
			}
			// dupa ce am pornit runningul, coada running o sa fie mereu plina, pana se goleste,
			// iar in momentul in care se goleste coada running si coada waiting o sa fie vida.
			while( coada_running != NULL )
			{
				scrie = 0;	// parametru ca sa nu mai afiseze o linie in plus.
				int biggest_time = max_time( &coada_running );
				sprintf(copie, "run %d", biggest_time);	// creez o pseudo comanda run 
				run(copie, out, &adresa_stiva, &adresa_coada_waiting, &adresa_coada_running, 
														&adresa_coada_finished, v, q, &all_my_time, scrie);
			}
			
			fprintf(out, "Total time: %d", all_my_time);
		}
	}

	// Eliberez memoria alocata
	DistrugeS(&Stiva_thread);
	DistrugeQ(&coada_waiting);
	DistrugeQ(&coada_running);
	DistrugeQ(&coada_finished);

	fclose(in);
	fclose(out);
	
	return 0;
}