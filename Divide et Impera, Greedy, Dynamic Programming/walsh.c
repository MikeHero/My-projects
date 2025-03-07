#include <stdio.h>

int f(int n, int x, int y) {
	if( n == 1)
		 return 0;
	int mid = n / 2;
	if( x > mid && y > mid )					// cadranu 4
		return 1 ^ f(n / 2, x - mid, y - mid );
	if( x <= mid && y > mid )					// cadranu 1
		return f(n / 2, x, y - mid );
	if( x > mid && y <= mid )					// cadranu 3
		return f(n / 2, x - mid, y );
	return f(n / 2, x, y);
}


int g(int n, int x, int y) {
	int result = 0;
	while(n > 0) {
		int dim = 1 << n;
		int mid = dim >> 1;
		if( x > mid && y > mid ) {
			n--;
			x = x - mid;
			y = y - mid;
			result = result ^ 1;
			continue;
		}
		if( x <= mid && y > mid ) {
			n--;
			y = y - mid;
			continue;
		}
		if( x > mid && y <= mid ) {
			n--;
			x = x - mid;
			continue;
		}
		n--;
	}
	return result;
}

int main() {
	FILE* in = fopen("walsh.in", "rt");
	if( in == NULL ) {
		printf("Eroare deschidere fisier intrare\n");
		return -1;
	}
	FILE* out = fopen("walsh.out", "wt");
	if( out == NULL ) {
		printf("Eroare deschidere fisier iesire\n");
		return -1;
	}
	int n, k, x, y;
	fscanf(in, "%d%d", &n, &k);
	int i;
	for( i = 0; i < k ; i++ ) {
		fscanf(in, "%d%d", &x, &y);
		fprintf(out, "%d\n", f(n, x, y));
	}
	fclose(in);
	fclose(out);
	return 0;
}
