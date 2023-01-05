#include <bits/stdc++.h>
using namespace std;
#define MAXN 51

int N, c[MAXN][MAXN][MAXN], a[MAXN*MAXN*MAXN];
int cubo[MAXN][MAXN][MAXN][MAXN];
int ans[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=0; i<N*N*N; i++) {
			scanf("%d", &a[i]);
		}
		for(int x=0; x<N; x++) {
			for(int y=0; y<N; y++) {
				for(int z=0; z<N; z++) {
					c[x][y][z] = a[x*N*N + y*N + z];
				}
			}
		}
		//cubo
		memset(&ans, 0, sizeof ans);
		for(int n=1; n<=N; n++) {
			for(int x=0; x+n-1<N; x++) {
				for(int y=0; y+n-1<N; y++) {
					for(int z=0; z+n-1<N; z++) {
						if (n == 1) cubo[x][y][z][n] = c[x][y][z];
						else {
							cubo[x][y][z][n] = cubo[x][y][z][n-1];
							cubo[x][y][z][n] = max(cubo[x][y][z][n], cubo[x+1][y+1][z+1][n-1]);
							cubo[x][y][z][n] = max(cubo[x][y][z][n], cubo[x+1][y][z][n-1]);
							cubo[x][y][z][n] = max(cubo[x][y][z][n], cubo[x][y+1][z][n-1]);
							cubo[x][y][z][n] = max(cubo[x][y][z][n], cubo[x][y][z+1][n-1]);
							cubo[x][y][z][n] = max(cubo[x][y][z][n], cubo[x][y+1][z+1][n-1]);
							cubo[x][y][z][n] = max(cubo[x][y][z][n], cubo[x+1][y][z+1][n-1]);
							cubo[x][y][z][n] = max(cubo[x][y][z][n], cubo[x+1][y+1][z][n-1]);
						}
						if (cubo[x][y][z][n] == n) ans[n]++;
						//if (n > 0) printf("cubo[%d][%d][%d][%d] = %d\n", x, y, z, n, cubo[x][y][z][n]);
					}
				}
			}
		}
		for(int k=1; k<=N; k++) {
			printf("%d ", ans[k]);
		}
		printf("\n");
	}
	return 0;
}