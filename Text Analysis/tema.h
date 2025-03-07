/* Mihai Ghioca 321CB */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LEN 30
#define SIZE 200

typedef struct
{
	char *cuvant;
	int frecventa;
}TCuv;

typedef struct celulag
{
	void* info;
	struct celulag *urm;
}TCelulaG, *TLG;

typedef struct celula
{
	int index;
	TLG info;
	struct celula* urm;
}TCelulaIndex, *TLI;

typedef int (*TFHash)(void*);
typedef void (*TF)(void*);

typedef struct
{
    size_t M;
    TFHash fh;
    TLI *v;
} TH;

// intoarce pozitia 0-25 succes, -1 eroare;
int codHash(void * element); 

// intoarce pointer catre o tabela hash in caz de succes, altfel NULL
TH* initTH(size_t M, TFHash fh);

// intoarce un pointer catre o celula de tip lista generica sau NULL daca esueaza alocarea
TLG alocCelulaG(char* cuvant);

// intoarce un pointer catre o celula tip lista index sau NULL daca esueaza alocarea
// celula index, are setat dupa apelul acestei functii, pe campul info, o Lista de tip TLG, cu un element de tipul TCuv.
TLI alocCelulaIndex(char* cuvant);


//functie care afiseaza un element de tip TCuv, avand un string cuvant si un int numar de aparitii
void afisare(void* elem);

// Functie pentru a afisa o lista de elemente de tip TLG, unde se apeleaza functia afisare pe campul void* info 
// al acestora 
void AfisareListaG(TLG L, TF afiEL);


// Functie folosita pentru afisarea unei liste de tip TLI care inglobeaza si liste de tip TLG si se foloseste de functia
// de afisare AfisareListaG de mai sus.
void AfisareListaIndex(TLI L);


//Afiseaza intreg continutul tabelei hash, toate listele TLI cu fiecare TLG al fiecareia
void AfiTH( TH* ah);


// functie care afiseaza cuvintele care apar de maxim n ori din tabela hash
void AfinTHN( TH* ah, int n);

// Compara 2 cuvinte dupa frecventa, apoi lexicografic, pentru ordonarea acestora. Intoarce 1 pentru crescator, -1 
// descrescator si 0 pentru egalitate
int comparaCuv(void *e1, void* e2);

// Creaza TLIndex ordonat in raport cu celelalte celule de tip TLIndex cu un singur element daca nu exista o 
// celula index cu dimensiunea corespunzatoare pentru cuvantul de  adaugat(ii creaza si aceastuia o celula de tip TLG 
// a carei informatie contine o structura de tip Cuvant si numar de ocurente in text).Daca exista deja o celula TLI 
// pentru lungimea actualului cuvant, inserarea se va face ordonat in sublista TLG care porneste de la TLIndex in jos.
void insereazaCuvant( TH* h, char* cuvant, int length, int poz );

// cauta un cuvant in lista generica si daca il gaseste intoarce 1, altfel intoarce 0
int cauta(TLG L, char* cuvant );  


// Se cauta elementul in lista, daca il gasim , incrementam frecventa si reordonam.Altfel se creaza o noua celula TLG, 
// inserata ordonat dupa criteriul cerut in lista deja existenta.  
void Ins_OrdLG(TLG* aL, TLG aux, int (*fcmp)(void *, void*) );

// functie de free pe un element de tip TLG
void free_el(void* el);

// functie de free pe o lista de tip TLG
void DistrugeLG(TLG* aL, TF free_elem);

// functie de free pe o lista de TLI unde fiecare celulade tip TLI are un pointer catre o lista TLG.Pe fiecare element
// se apelease DistrugeLG
void DistrugeLI(TLI* aL, TF free_elem);

// functie de free pe tabela hash, unde se apeleaza pe fiecare element din vector DistrugeLI. 
void DistrTH(TH** ah);


