#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100000

char litera_glob;

int nr_aparitii(char* s, char x) {
	int count = 0;
	while ( *s != '\0' ) {
		if( *s == x )
			count++;
		s++;
	}
	return count;
}


void valoare(char*s, char x, int* lg, int* fr) {
	*fr = 0;
	*lg = 0;
	while ( *s != '\0' ) {
		if( *s == x )
			(*fr)++;
		(*lg)++;
		s++;
	}
}

int exista_litera_dominanta(char *s, char* c) {
	int v2[26];
	int i, poz;
	for( i = 0 ; i < 26; i++)
		v2[i] = 0;
	char *p;
	p = s;
	int dim = strlen(s);
	while( *p != '\0' ) {
		v2[*p - 'a']++;
		p++;
	}
	int max = 0;
	for( i = 0; i < 26; i++)
		if(max < v2[i]) {
			max = v2[i];
			poz = i;
		}
	if( max > (dim / 2) ) {
		*c = 'a' + poz;
		return 1;
	}
	return 0;
}

int fcmp2(const void* e1, const void* e2) {
	char *x = (char*) e1;
	char *y = (char*) e2;
	int lg_x, fr_x, lg_y, fr_y;
	valoare(x, litera_glob, &lg_x, &fr_x);
	valoare(y, litera_glob, &lg_y, &fr_y);
	float val_x = fr_x - 1.0 * lg_x / 2;
	float val_y = fr_y - 1.0 * lg_y / 2;
	if( val_x > val_y )
		return -1;
	return 1;
}

int main() {
	FILE* in = fopen("statistics.in", "rt");
	if( !in ) {
		printf("Eroare deschidere fisier de input\n");
		return -1;
	}
	FILE* out = fopen("statistics.out", "wt");
	if( !out ) {
		printf("Eroare deschidere fisier de output\n");
		return -1;
	}
	int n;
	fscanf(in, "%d", &n);
	int v[26], i, j;
	char s[16800][100];
	char mega_cuvant[70000] = "";
	char *p;
	for(i = 0 ; i < 26; i++)
		v[i] = 0;
	int count, indice, max;
	int verificator = 0;
	int gol[26];
	char litera2;
	int vector_litera_dominanta[26];
	for( i = 0; i < 26; i++)
		vector_litera_dominanta[i] = 0;
	int k = 0;
	for( i = 1 ; i <= n; i++ ) {
		fscanf(in, "%s", s[i]);
		int r = exista_litera_dominanta(s[i], &litera2);
		if( r != 0 ) {
			vector_litera_dominanta[ litera2 - 'a' ] = 1;
		}
	}
	int no_dec = 1;
	int nr;
	int contor;
	int max_nr = 0; float valoare, valoare_ant;
	for( contor = 0; contor < 26; contor++ ) {
		nr = 0;
		if( vector_litera_dominanta[contor] > 0 ) {
			litera_glob = 'a' + contor;
			qsort(s + 1, n, 100, fcmp2);
			i = 1;
			int frecventa = 0;
			int lungime = 0;
			valoare = 0;
			no_dec = 1;
			strcpy(mega_cuvant, "");
			do {
				if( i == n + 1 ) {
					no_dec = 0;
					break;
				}
				frecventa+= nr_aparitii(s[i], litera_glob);
				lungime+= strlen(s[i]);
				nr++;
				if( frecventa )
					strcat(mega_cuvant, " ");
				valoare = 1.0 * frecventa / lungime;
				strcat(mega_cuvant, s[i]);
				i++;
			}while( frecventa > (lungime / 2) );
			if( nr > max_nr )
				max_nr = nr;
		}
	}
	nr = max_nr - no_dec;
	fprintf(out, "%d\n", nr);
	fclose(in);
	fclose(out);
	return 0;
}
