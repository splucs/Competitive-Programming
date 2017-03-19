#include <cstdio>
#define MAXN 1009

char mat[MAXN][MAXN];
int N, M;

int main(){
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			scanf(" %c", &mat[i][j]);
		}
	}
	int ans = 0, cur = 0;
	for(int i=0; i<N; i++){
		for(int j=(i%2==0? 0 : M-1); j>=0 && j<M; j += (i%2==0? 1 : -1)){
			if (mat[i][j] == '.') cur++;
			if (mat[i][j] == 'L') cur = 0;
			if (cur > ans) ans = cur;
		}
	}
	printf("%d\n", ans);
	return 0;
}