#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#define MAXN 10009
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
vector<ii> adjList[MAXN];

int N, M;

ll prim() {
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
	scanf("%d %d", &N, &M);
	int u, v, w;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &w);
		adjList[u-1].push_back(make_pair(v-1, w));
		adjList[v-1].push_back(make_pair(u-1, w));
	}
	printf("%lld\n", prim());
	return 0;
}