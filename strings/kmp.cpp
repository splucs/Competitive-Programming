#include <cstdio>
#include <cstring>
#define MAXN 100009 
void kmpPreprocess(char* P, int* b) {
	b[0] = -1;
	int m = strlen(P);
	for (int i = 0, j = -1; i < m;) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}

void action(int i) {
	printf("P is found at index %d in T\n", i);
}

int kmpSearch(char* P, char* T, int* b) {
	int n = strlen(T), m = strlen(P), nmatches = 0;
	for (int i = 0, j = 0; i < n;) {
		while (j >= 0 && T[i] != P[j]) j = b[j];
		i++; j++;
		if (j == m) {
			action(i - j);
			nmatches++;
			j = b[j];
		}
	}
	return nmatches;
}