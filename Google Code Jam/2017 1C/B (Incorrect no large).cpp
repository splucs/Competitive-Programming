#include <bits/stdc++.h>
using namespace std;
#define MAXN 1500
#define N 1440
#define MAXA 109
#define INF (1<<30)
#define s first
#define t second

int T, Ac, Aj;
typedef pair<int, int> ii;
ii vc[MAXA], vj[MAXA];

int dp[2][2][MAXN][MAXN];

int findf(int k, bool isc){
	int n = isc ? Ac : Aj;
	ii *v = isc ? vc : vj;
	for(int i=0; i<n; i++){
		if (v[i].t >= k && v[i].s < k) return i;
	}
	return -1;
}

int find(int k, bool isc){
	int lo = 0;
	int hi = isc ? Ac : Aj;
	int mid;
	ii *v = isc ? vc : vj;
	if (hi == lo) return -1;
	if (v[lo].t >= k){
		if (v[lo].s < k) return lo;
		else return -1;
	}
	while(hi > lo+1){
		int mid = (hi+lo)/2;
		if (v[mid].t >= k) hi = mid;
		else lo = mid;
	}
	if ((isc ? Ac : Aj) > hi && v[hi].s < k) return hi;
	else return -1;
}

int DP(int i, int j, int k, int t) {
	if (dp[i][j][k][t] >= 0) return dp[i][j][k][t];
	if (k == N){
		if (t != N/2) return dp[i][j][k][t] = INF;
		return dp[i][j][k][t] = (i == j ? 0 : 1);
	}
	if (t > N/2 || k-t > N/2) dp[i][j][k][t] = INF;
	if (j == 1) {
		int cc = find(k, true);
		if (cc >= 0) return dp[i][j][k][t] = INF;
	}
	else {
		int cj = find(k, false);
		if (cj >= 0) return dp[i][j][k][t] = INF;
	}
	return dp[i][j][k][t] = min(DP(i, j, k+1, (j==0?t+1:t)), 1+DP(i, 1-j, k+1, (j==1?t+1:t)));
}

bool comp(ii i, ii j) {
	if (i.t != j.t) return i.t < j.t;
	else return i.s < j.s;
}

int main(){
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++) {
		scanf("%d %d", &Ac, &Aj);
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				for(int k=0; k<=N; k++){
					for(int t=0; t<=N; t++){
						dp[i][j][k][t] = -1;
					}
				}
			}
		}
		for(int i=0; i<Ac; i++){
			scanf("%d %d", &vc[i].s, &vc[i].t);
		}
		sort(vc, vc+Ac, &comp);
		for(int i=0; i<Aj; i++){
			scanf("%d %d", &vj[i].s, &vj[i].t);
		}
		sort(vj, vj+Aj, &comp);
		/*for(int i=0; i<=N; i++){
			int cc = find(i, true), cj = find(i, false);
			int fc = findf(i, true), fj = findf(i, false);
			if (cc != fc) printf("k=%d, cc=%d, fc=%d\n", i, cc, fc);
			if (cj != fj) printf("k=%d, cj=%d, fj=%d\n", i, cj, fj);
		}*/
		printf("Case #%d: %d\n", caseNo, min(DP(0,0,0,0), DP(1,1,0,0)));
	}
	return 0;
}