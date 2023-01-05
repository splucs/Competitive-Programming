#include <cstdio>
#include <cstring>
#define MAXN 100009
//pre process P in order to get b. O(m)
void kmpPreprocess(char* P, int* b) {
	b[0] = -1;
	int m = strlen(P);
	for(int i = 0, j = -1; i < m;) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}
//kmp search. O(n+m)
int kmpSearch(char* P, char* T, int* b) {
	int n = strlen(T), m = strlen(P);
	for (int i=0, j=0; i < n;) {
		while (j >= 0 && T[i] != P[j]) j = b[j];
		i++; j++;
		if (i == n) {
			return j;
			j = b[j];
		}
	}
}

int main(){
	char S[MAXN], R[MAXN];
	int b[MAXN], n, m;
	while(scanf(" %s", S)!=EOF){
		n = strlen(S);
		for(int i=0; i<n; i++) R[i] = S[n-1-i];
		R[n]='\0';
		kmpPreprocess(R, b);
		m = kmpSearch(R, S, b);
		printf("%s%s\n", S, &R[m]);
	}
	return 0;
}