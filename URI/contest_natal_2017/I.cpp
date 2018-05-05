#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int N, K, x[MAXN], y[MAXN];

int gcd(int x, int y) {
	if (y == 0) return x;
	return gcd(y, x%y);
}

typedef long long ll;
typedef pair<int, int> ii;
vector<ii> adjList[MAXN];

ll prim(){
	bool taken[MAXN];
	memset(&taken, false, sizeof taken);
	taken[0] = true;
	priority_queue<ii> pq;
	ii v, front; int u, w; ll cost = 0;
	for (int j = 0; j < (int)adjList[0].size(); j++) {
		v = adjList[0][j];
		pq.push(ii(-v.second, -v.first));
	}
	while (!pq.empty()) {
		front = pq.top(); pq.pop();
		u = -front.second; w = -front.first;
		if (!taken[u]) {
			cost += (ll)w; taken[u] = true;
			for (int j = 0; j < (int)adjList[u].size(); j++) {
				v = adjList[u][j];
				if (!taken[v.first]) pq.push(ii(-v.second, -v.first));
			}
		}
	}
	return cost;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d", &N, &K);
		for(int i = 0; i < N; i++) {
			scanf("%d %d", &x[i], &y[i]);
		}
		ll ans = 0;
		for(int i = 0; i < N; i++) {
			adjList[i].clear();
			for(int j = 0; j < N; j++) {
				int dx = abs(x[i]-x[j]);
				int dy = abs(y[i]-y[j]);
				int w = gcd(dx, dy) - 1;
				adjList[i].push_back(ii(j, w));
				ans += w;
			}
		}
		ans = prim();
		printf("%lld\n", ans*K);
	}
	return 0;
}