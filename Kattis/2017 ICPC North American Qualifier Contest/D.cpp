#include <bits/stdc++.h>
using namespace std;
#define MAXN 15
#define INF 1e+18
#define EPS 1e-9

double m, powm[MAXN];
double mint[1<<MAXN][MAXN], mouse[MAXN], x[MAXN], y[MAXN], dist[MAXN][MAXN];
int N;
bool pos[1<<MAXN][MAXN];

bool check(double v) {
	for(int mask=1; mask<(1<<N); mask++) {
		for(int i=0; i<N; i++) {
			mint[mask][i] = INF;
			pos[mask][i] = false;
			if (mask == (1<<i)) {
				mint[mask][i] = hypot(x[i], y[i]) / v;
				pos[mask][i] = true;
			}
		}
	}
	for(int mask=1; mask<(1<<N); mask++) {
		int cj = __builtin_popcount(mask);
		for(int i=0; i<N; i++) {
			if (!(mask & (1<<i)) || mint[mask][i] > mouse[i]) {
				pos[mask][i] = false;
				continue;
			}
			for(int j=0; j<N; j++) {
				if (mask & (1<<j)) continue;
				if (mint[mask | (1<<j)][j] > mint[mask][i] + dist[i][j]/(v*powm[cj])) {
					mint[mask | (1<<j)][j] = mint[mask][i] + dist[i][j]/(v*powm[cj]);
					pos[mask | (1<<j)][j] = true;
				}
			}
		}
	}
	int mask = (1<<N)-1;
	for(int i=0; i<N; i++) {
		if (pos[mask][i]) return true;
	}
	return false;
}

int main() {
	
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%lf %lf %lf", &x[i], &y[i], &mouse[i]);
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			dist[i][j] = hypot(x[i]-x[j], y[i]-y[j]);
		}
	}
	scanf("%lf", &m);
	powm[0] = 1;
	for(int i=1; i<MAXN; i++) powm[i] = m*powm[i-1];
	
	double lo = 0;
	double hi = INF;
	while(fabs(hi-lo) > EPS) {
		double mid = (hi+lo)/2;
		if (check(mid)) hi = mid;
		else lo = mid;
	}
	
	printf("%.16f\n", hi);
	return 0;
}