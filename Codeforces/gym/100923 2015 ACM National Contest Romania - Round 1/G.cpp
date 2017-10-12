#include <bits/stdc++.h>
#define INF (1<<30)
using namespace std;
#define MAXN 309

int a[MAXN][MAXN], mx[MAXN][MAXN], aux[MAXN];

int main(){	
	freopen("livada2.in", "r", stdin);
	freopen("livada2.out", "w", stdout);
	
	int T, N, M;
	scanf("%d", &T);
	while(T --> 0) {
		
		scanf("%d %d", &N, &M);
		int maxa = -INF;
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				scanf("%d", &a[i][j]);
				if (a[i][j] > maxa) maxa = a[i][j];
			}
		}
		
		memset(&mx, 0, sizeof mx);
		int sum, ans = -INF;
		for(int k=0; k<N; k++) {
			for(int j=0; j<M; j++) aux[j] = -INF;
			for(int i=0; i<M; i++) {
				sum = 0;
				for(int j=i; j<M; j++) {
					sum += a[k][j];
					if (aux[j] < sum + mx[i][j]) aux[j] = sum + mx[i][j];
				}
				for(int j = M-2; j>=i; j--) {
					if (aux[j] < aux[j+1]) aux[j] = aux[j+1];
				}
			}
			for(int i=0; i<M; i++) {
				mx[i][i] = aux[i] > 0 ? aux[i] : 0;
				for(int j=i+1; j<M; j++) {
					if (aux[j] > mx[i][j-1]) mx[i][j] = aux[j];
					else mx[i][j] = mx[i][j-1];
				}
			}
			if (ans < mx[0][M-1]) ans = mx[0][M-1];
			
			/*printf("aux:");
			for(int i=0; i<M; i++) printf(" %2d", aux[i]);
			printf("\n");
			printf("mx:\n");
			for(int i=0; i<M; i++) {
				for(int j=0; j<M; j++) {
					printf(" %2d", j >= i ? mx[i][j] : -1);
				}
				printf("\n");
			}*/
		}
		
		if (ans == 0) ans = maxa;
		printf("%d\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}