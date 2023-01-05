#include <cstdio>
#include <cstring>
#define MAXN 2000009
char P[MAXN], T[MAXN];
int b[MAXN], res;
void kmpPreprocess() {
	int i = 0, j = -1; b[0] = -1;
	int m = strlen(P);
	while (i < m) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}
//kmp search. O(n+m)
void kmpSearch() {
	int i = 0, j = 0;
	int n = strlen(T), m = strlen(P);
	while (i < n) {
		while (j >= 0 && T[i] != P[j]) j = b[j];
		i++; j++;
		if (j == m) {
			res++;
			j = b[j];
		}
	}
}

int main(){
	while(true){
		scanf(" %s", P);
		if (!strcmp(P, ".")) break;
		strcpy(T, P);
		strcat(T, P);
		kmpPreprocess();
		res = -1;
		kmpSearch();
		printf("%d\n", res);
	}
	return 0;
}