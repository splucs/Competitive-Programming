#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009

typedef long long ll;


class FenwickTree {
private:
	vector<ll> ft1, ft2;
	ll rsq(vector<ll> & ft, int i) {
		ll sum = 0;
		while(i > 0){
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}
	void update(vector<ll> & ft, int i, ll v) {
		while(i < (int)ft.size()) {
			ft[i] += v;
			i += (i & -i);
		}
	}
public:
	FenwickTree(int n) {
		ft1.assign(n + 1, 0);	//1-indexed
		ft2.assign(n + 1, 0);	//1-indexed
	}
	void update(int i, int j, ll v){
		if (i > j) return;
		update(ft1, i, v);
		update(ft1, j+1, -v);
		update(ft2, i, v*(i-1));
		update(ft2, j+1, -v*j);
	}
	ll rsq(int i){
		return rsq(ft1, i)*i - rsq(ft2, i);
	}
	ll rsq(int i, int j){
		return rsq(j) - rsq(i-1);
	}
};

FenwickTree ft(MAXN);
int cur[MAXN], sz;
ll d[MAXN], ans[MAXN], X[MAXN];
typedef pair<ll, int> ii;
vector<ii> adjList[MAXN];

void dfs(int u, int p, int dp) {
	cur[++sz] = u;
	d[sz] = d[sz-1] + dp;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].second;
		ll w = adjList[u][i].first;
		if (v == p) continue;
		dfs(v, u, w);
	}
	int hi = sz;
	int lo = 0;
	while(hi > lo + 1) {
		int mid = (hi+lo)/2;
		if (d[sz] - X[u] <= d[mid]) hi = mid;
		else lo = mid;
	}
	//printf("computing ans for %d, sz = %d\n", u, sz);
	ft.update(hi, sz-1, 1);
	ans[u] = ft.rsq(sz, sz);
	ft.update(sz, sz, -ans[u]);
	//printf("ans[%d] = %I64d\n", u, ans[u]);
	sz--;
}

int main() {
	freopen("car.in", "r", stdin);
	
	int T, N, u, v;
	ll w;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=1; i<=N; i++) {
			scanf("%I64d", &X[i]);
			adjList[i].clear();
		}
		for(int i=1; i<N; i++) {
			scanf("%d %d %I64d", &u, &v, &w);
			adjList[u].push_back(ii(w, v));
			adjList[v].push_back(ii(w, u));
		}
		sz = 0;
		d[0] = 0;
		ft = FenwickTree(N);
		dfs(1, -1, 0);
		for(int i=1; i<=N; i++) {
			printf("%I64d ", ans[i]);
		}
		printf("\n");
	}
	
	fclose(stdin); 
	return 0;
}