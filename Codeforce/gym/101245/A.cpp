#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int S[MAXN];
int n, z[MAXN];
int b[MAXN];

void kmp(int* P){
	b[0] = -1;
	for(int i = 0, j = -1; i < n;) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", &z[i]);
	}
	memset(&S, -1, sizeof S);
	int k = 1;
	for(int i=0, j=0; i<n && j<n; i++){
		while(j < n && S[j] >= 0) j++;
		while(j < n && j < i+z[i]){
			S[j] = S[j-i];
			j++;
		}
		if (S[i] == -1) S[i] = k++;
		//printf("%d ", S[i]);
	}
	kmp(S);
	for(int i=1; i<=n; i++){
		printf("%d", b[i]);
		if (i < n) printf(" ");
	}
	printf("\n");
	return 0;
}