#include <bits/stdc++.h>
using namespace std;
#define MAXN 30009
#define INF (1<<30)

vector<int> adjList[MAXN];
int ball[MAXN], par[MAXN];
typedef pair<int, int> ii;
typedef long long ll;
map<ii, ll> dp;

ll DP(const int u, const int n) {
	if (dp.count(ii(u, n))) return dp[ii(u, n)];
	
	if (adjList[u].size() == 0u) {
		if (n == 0 || n == 1) return dp[ii(u, n)] = abs(ball[u] - n);
		else return dp[ii(u, n)] = INF;
	}
	
	if (adjList[u].size() == 1u) return dp[ii(u, n)] = DP(adjList[u][0], n);
	
	if (n % 2 == 0) {
		return dp[ii(u, n)] = DP(adjList[u][0], n/2) + DP(adjList[u][1], n/2);
	}
	else {
		return dp[ii(u, n)] = min(DP(adjList[u][0], n/2) + DP(adjList[u][1], n/2+1), DP(adjList[u][0], n/2+1) + DP(adjList[u][1], n/2));
	}
}

char buffer[MAXN];

int main() {
	while(scanf(" %s", buffer) != EOF) {
		int len = strlen(buffer);
		int u = 1, cnt = 1, nball = 0;;
		par[u] = -1;
		adjList[u].clear();
		memset(&ball, 0, sizeof ball);
		for(int i=0; i<len; i++) {
			if (buffer[i] == '(') {
				adjList[u].push_back(++cnt);
				par[cnt] = u;
				u = cnt;
				adjList[cnt].clear();
			}
			if (buffer[i] == ')') {
				u = par[u];
			}
			if (buffer[i] == 'B') {
				ball[u] = 1;
				nball++;
			}
		}
		
		dp.clear();
		ll ans = DP(1, nball);
		if (ans < INF) printf("%I64d\n", ans/2);
		else printf("impossible\n");
	}
	
	return 0;
}