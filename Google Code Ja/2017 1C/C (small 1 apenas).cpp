#include <bits/stdc++.h>
using namespace std;
#define MAXN 59
#define MAXT 500000

int T, N, K;
double U, P[MAXN];

void stabilize(int k, double tar) {
	double req = (tar-P[0])*k;
	double h = min(req, U)/k;
	U -= min(req, U);
	for(int i=0; i<k; i++) P[i] += h;
}

int main(){
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++) {
		scanf("%d  %d %lf", &N, &K, &U);
		for(int i=0; i<N; i++){
			scanf("%lf", &P[i]);
		}
		sort(P, P+N);
		for(int i=0; i+1<N; i++){
			if (P[i] < P[i+1]) stabilize(i+1, P[i+1]);
		}
		stabilize(N, 1.0);
		double ans = 1.0;
		for(int i=0; i<N; i++){
			ans *= P[i];
		}
		printf("Case #%d: %.6f\n", caseNo, ans);
	}
	return 0;
}