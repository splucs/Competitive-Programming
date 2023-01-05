#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009

class SegmentTree {
	vector<int> stmin, stmax;
	int n;
public:
	SegmentTree(int sz) {
		for (n = 1; n < sz; n <<= 1);
		stmin.assign(n << 1, MAXN);
		stmax.assign(n << 1, 0);
	}
	void update(int i, int x) {
		stmax[i+n] = x; //substitui
		stmin[i+n] = x; //substitui
		for (i += n, i >>= 1; i; i >>= 1) {
			stmax[i] = max(stmax[i<<1], stmax[1+(i<<1)]);
			stmin[i] = min(stmin[i<<1], stmin[1+(i<<1)]);
		}
	}
	int maxquery(int l, int r) {
		int ans = 0;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, stmax[l++]);
			if (r & 1) ans = max(ans, stmax[--r]);
		}
		return ans;
	}
	int minquery(int l, int r) {
		int ans = MAXN;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = min(ans, stmin[l++]);
			if (r & 1) ans = min(ans, stmin[--r]);
		}
		return ans;
	}
};

SegmentTree st(MAXN);

int num[MAXN], pos[MAXN], last[MAXN], am[MAXN], cnt, N, M;
long long sum[MAXN];
vector<int> adjList[MAXN];

void dfs(int u, int p) {
	num[u] = 1;
	pos[u] = cnt++;
	st.update(pos[u], u);
	for(int i = 0; i < (int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == p) continue;
		if (num[v] == 0) dfs(v, u);
		else if (num[v] == 1) {
			int mi = st.minquery(pos[v], pos[u]);
			int ma = st.maxquery(pos[v], pos[u]);
			//printf("cycle %d->%d\n", mi, ma);
			last[mi] = min(last[mi], ma-1);
		}
	}
	num[u] = 2;
	cnt--;
}

int main() {

	scanf("%d %d", &N, &M);
	for(int j = 0; j < M; j++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	for(int u = 1; u <= N; u++) {
		last[u] = N;
		num[u] = 0;
	}

	cnt = 0;
	for(int u = 1; u <= N; u++) {
		if (num[u] == 0) dfs(u, -1);
	}
	for(int u = N-1; u >= 1; u--) {
		last[u] = min(last[u], last[u+1]);
		//printf("last[%d] = %d\n", u, last[u]);
	}
	sum[0] = 0;
	for(int u = 1; u <= N; u++) {
		am[u] = last[u] - u + 1;
		sum[u] = am[u] + sum[u-1];
	}

	int Q, l, r;
	scanf("%d", &Q);
	for(int q = 0; q < Q; q++) {
		scanf("%d %d", &l, &r);
		int lo = l-1;
		int hi = r+1;
		while(hi > lo + 1) {
			int mid = (hi+lo)/2;
			if (last[mid] > r) hi = mid;
			else lo = mid;
		}
		int n = r-hi+1;
		long long ans = n*(n+1LL)/2 + sum[lo] - sum[l-1];
		printf("%I64d\n", ans);
	}

	return 0;
}