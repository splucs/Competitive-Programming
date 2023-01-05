#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

int mat[MAXN][MAXN];

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		int N, M;
		scanf("%d %d", &N, &M);
		int k = N*M;
		for(int s = 0; s < N+M-1; s++) {
			for(int j = 0; s-j >= 0 && j < M; j++) {
				int i = s - j;
				if (i >= N) {
					i = N-1;
					j = s - i;
				}
				mat[i][j] = k--;
			}
		}
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				printf("%d ", mat[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}