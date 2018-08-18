#include <bits/stdc++.h>
using namespace std;

#define FOR(i, N) for (int i = 0; i < N; ++i)
#define MAXN 100009
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;
const int INF = 1e9 + 1;
const ll MOD = 1000000007;

int N, K, p[MAXN], vis[MAXN] = {};
ll dp[MAXN];
vector<int> divs;

int dfs(int u){
	int first = u;
	int cnt = 1;
	while (u != first) {u = p[u]; ++cnt; vis[u] = 1;}
	vis[u] = 1;
	return cnt;
}

ll solve(int idx, int u, int cnt){
	if (cnt == 0) return 1;
	if (dp[idx] != -1) return dp[idx];
	ll &ans = dp[idx] = 0;
	
	for (auto it : divs){
		if (it > cnt) break;
		if ((K / it - 1) % u) continue;
		ans += solve(idx + it, u, cnt - it);
	}
	return ans;
}

int main() {
	scanf("%d%d", &N, &K);
	vector<int> vals;
	for (int i = 1; i <= K; ++i){
		if (K % i) divs.pb(i);
	}
	FOR(i, N) {scanf("%d", &p[i]); --p[i];}
	FOR(i, N) if (!vis[i]) vals.pb(dfs(i));
	
	sort(vals.begin(), vals.end());
	memset(dp, -1, sizeof dp);
	
	ll ans = 1;
	
	memset(dp, -1, sizeof dp);
	FOR(i, (int) vals.size()){
		int u = vals[i], cnt = 0;
		while (vals[i] == u)++cnt, ++i;
		--i;
		ans *= solve(i - cnt, u, cnt);
	}
	printf("%lld\n", ans);
}