#include <cstdio>
#define foreach(i, n) for (int i = 0; i < n; ++i)
#define MAXN 1009

int N, n, big[MAXN][MAXN], small[MAXN][MAXN], aux[MAXN][MAXN];

void rotate(){
	foreach(i, n){
		foreach(j, n){
			aux[j][n-i-1]=small[i][j];
		}
	}
	foreach(i, n){
		foreach(j, n){
			small[i][j]=aux[i][j];
		}
	}
}

int verify(int x, int y){
	foreach(i, n){
		foreach(j, n){
			if (big[i+x][j+y]!=small[i][j]) return 0;
		}
	}
	return 1;
}

int main(){
	int ans;
	while(scanf("%d %d", &N, &n), (N || n)){
		foreach(i, N){
			foreach(j, N){
				scanf(" %c", &big[i][j]);
			}
		}
		foreach(i, n){
			foreach(j, n){
				scanf(" %c", &small[i][j]);
			}
		}
		ans = 0;
		foreach(i, N-n+1){
			foreach(j, N-n+1) ans += verify(i, j);
		}
		printf("%d ", ans);
		rotate();
		ans = 0;
		foreach(i, N-n+1){
			foreach(j, N-n+1) ans += verify(i, j);
		}
		printf("%d ", ans);
		rotate();
		ans = 0;
		foreach(i, N-n+1){
			foreach(j, N-n+1) ans += verify(i, j);
		}
		printf("%d ", ans);
		rotate();
		ans = 0;
		foreach(i, N-n+1){
			foreach(j, N-n+1) ans += verify(i, j);
		}
		printf("%d\n", ans);
	}
	return 0;
}