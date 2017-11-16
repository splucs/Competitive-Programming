#include <bits/stdc++.h>
using namespace std;
#define MAXN 209

char tab[MAXN][MAXN], mes[MAXN*MAXN];

int main() {
	int N, M;
	while(scanf("%d", &M), M) {
		scanf(" %s", mes);
		N = strlen(mes)/M;
		for(int i=0, k=0; i<N; i++) {
			if (i % 2 == 0) for(int j=0; j<M; j++) {
				tab[i][j] = mes[k++];
			}
			else for(int j=M-1; j>=0; j--) {
				tab[i][j] = mes[k++];
			}
		}
		for(int j=0, k=0; j<M; j++) {
			for(int i=0; i<N; i++) {
				mes[k++] = tab[i][j];
			}
		}
		printf("%s\n", mes);
	}
	return 0;
}