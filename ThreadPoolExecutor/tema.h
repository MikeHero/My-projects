#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 200
#define LEN 32768

typedef struct celulag
{
	void* info;
	struct celulag *urm;
}TCelulaG, *TLG;  

typedef struct celulagCoada
{
	void* info;
	struct celulagCoada *urm;
	struct celulagCoada *sf;
}TCelulaGC, *TLGC;

typedef struct 
{
	unsigned short task_id;
	unsigned char thread;
	char prioritate;
	unsigned int timp;
	unsigned int initial_time;
}TTask;

typedef struct 
{
	int thread_id;
}TThread;

//functii auxiliare de lucru pentru stiva
TLG alocCelulaStiva(int x);
void Push(TLG *L, int x);
void Pop(TLG *L, int *x);
void initS(TLG *L, int n);
void afisareStiva( TLG *L );
void DistrugeS(TLG *L);

//functii auxiliare de lucru pentru coada
TLGC alocCelulaCoada(unsigned short id, unsigned int timp_executie, char prioritate, int thread, unsigned int timp_initial);
void IntrQ(TLGC *L, TTask t);
void ExtrQ(TLGC *L, TTask *x);
void IntrQOrd(TLGC *L, TTask task );
void afisare_task(void* x, FILE* out);
void afisareCoadaW(TLGC *L, FILE* out);
void afisareCoadaR(TLGC *L, FILE* out);
void afisareCoadaF(TLGC *L, FILE* out);
void DistrugeQ(TLGC *L);