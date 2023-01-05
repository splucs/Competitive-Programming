#include <cstdio>
#define MAXN 3009

double a[MAXN][MAXN], y[MAXN], c[MAXN][MAXN], yc[MAXN], xc[MAXN], x[MAXN], k[MAXN][MAXN];
int N;

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			scanf("%lf", &c[i][j]);
		}
	}
	for(int i=0; i<N; i++){
		scanf("%lf", &y[i]);
		x[i] = y[i];
	}
	for(int i=0; i<N; i++){
		scanf("%lf", &yc[i]);
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			x[i] += c[i][j];
		}
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			k[i][j] = -c[i][j]/x[j];
		}
		k[i][i] += 1.0;
	}
	int count=0, iter = 1000/N, minit = 6;
	if (iter < minit) iter = minit;
	for(int i=0; i<N; i++) x[i] = yc[i];
	do {
		for(int i=0; i<N; i++) {
			xc[i] = yc[i];
			for(int j=0; j<N; j++) {
				if (i < j) xc[i] -= k[i][j]*xc[j];
				if (i > j) xc[i] -= k[i][j]*x[j];
			}
			xc[i] /= k[i][i];
		}
		for(int i=0; i<N; i++) x[i] = xc[i];
		count++;
	} while(count < iter);
	for(int i=0; i<N; i++) {
		printf("%.8f ", xc[i]);
	}
	printf("\n");
	return 0;
}