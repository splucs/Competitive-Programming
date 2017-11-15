#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 1e+18
#define state dp[u][r1][r2]

typedef long long ll;

struct circle{
	ll x, y, r;
	bool contains(circle c){
		if (c.r >= r) return false;
		return (x-c.x)*(x-c.x) + (y-c.y)*(y-c.y) <= r*r;
	}
	bool operator < (circle c){
		return r < c.r;
	}
};
circle dance[MAXN];
double C[MAXN], dp[MAXN][2][2];
int deg[MAXN];

vector<int> adj[MAXN];

double DP(const int u, const int r1, const int r2){
	if (state > -INF/2.0) return state;
	double a1, a2;
	a1 = (r1 == 1 ? -C[u] : C[u]);
	for(int i=0, v; i<(int)adj[u].size(); i++){
		v = adj[u][i];
		a1 += DP(v, 1-r1, r2);
	}
	a2 = (r2 == 1 ? -C[u] : C[u]);
	for(int i=0, v; i<(int)adj[u].size(); i++){
		v = adj[u][i];
		a2 += DP(v, r1, 1-r2);
	}
	state = max(a1, a2);
	//printf("dp[%d][%d][%d] = %f\n", u, r1, r2, state);
	return state;
}

int main() {
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%I64d %I64d %I64d", &dance[i].x, &dance[i].y, &dance[i].r);
		deg[i] = 0;
	}
	sort(dance, dance+N);
	for(int i=0; i<N; i++){
		C[i] = dance[i].r*1.0*M_PI*1.0*dance[i].r;
		for(int j=i+1; j<N; j++){
			if (dance[j].contains(dance[i])){
				deg[i]++;
				adj[j].push_back(i);
				break;
			}
		}
		dp[i][0][0] = -INF;
		dp[i][0][1] = -INF;
		dp[i][1][0] = -INF;
		dp[i][1][1] = -INF;
	}
	double ans = 0;
	for(int i=0; i<N; i++){
		if (deg[i] == 0) ans += DP(i, 0, 0);
	}
	printf("%.8f\n", ans);
	return 0;
}