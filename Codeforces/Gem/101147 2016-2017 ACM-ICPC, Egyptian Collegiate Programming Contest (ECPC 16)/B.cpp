#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define INF 1e+18

struct rec {
	double x[2], y[2];
} vet[MAXN];

double distrec(int u, int v) {
	rec ru = vet[u];
	rec rv = vet[v];
	if (!(ru.x[0] > rv.x[1] || ru.x[1] < rv.x[0])) {
		if (ru.y[0] > rv.y[1]) return ru.y[0] - rv.y[1];
		if (rv.y[0] > ru.y[1]) return rv.y[0] - ru.y[1];
		return 0.0;
	}
	if (!(ru.y[0] > rv.y[1] || ru.y[1] < rv.y[0])) {
		if (ru.x[0] > rv.x[1]) return ru.x[0] - rv.x[1];
		if (rv.x[0] > ru.x[1]) return rv.x[0] - ru.x[1];
		return 0.0;
	}
	double ans = INF;
	for(int i1=0; i1<2; i1++) for(int j1=0; j1<2; j1++)
		for(int i2=0; i2<2; i2++) for(int j2=0; j2<2; j2++) {
			ans = min(ans, hypot(ru.x[i1] - rv.x[i2], ru.y[j1] - rv.y[j2]));
		}
	return ans;
}

double dist[MAXN][MAXN];
int N;

int main() {
	freopen("street.in", "r", stdin);
	
	int T, k;
	double h, w, d, L, U;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %lf %lf", &N, &L, &U);
		for(int i=1; i<=N; i++) {
			scanf("%lf %lf %lf %d", &h, &w, &d, &k);
			vet[i].y[0] = d;
			vet[i].y[1] = d+h;
			if (k == 0) {
				vet[i].x[0] = 0;
				vet[i].x[1] = w;
			}
			else {
				vet[i].x[0] = U-w;
				vet[i].x[1] = U;
			}
		}
		//printf("N=%d\n", N);
		vet[0].x[0] = 0;
		vet[0].x[1] = U;
		vet[0].y[0] = -1;
		vet[0].y[1] = 0;
		N += 2;
		vet[N-1].x[0] = 0;
		vet[N-1].x[1] = U;
		vet[N-1].y[0] = L;
		vet[N-1].y[1] = L+1;
		//printf("N=%d\n", N);
		
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				dist[i][j] = distrec(i, j);
				//printf("dist[%d][%d] = %.6f\n", i, j, dist[i][j]);
			}
		}
		for(int k=0; k<N; k++) {
			for(int i=0; i<N; i++) {
				for(int j=0; j<N; j++) {
					dist[i][j]  = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
		
		printf("%.6f\n", dist[0][N-1]);
	}
	
	fclose(stdin); 
	return 0;
}