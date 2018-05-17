#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#define MAXN 1009
using namespace std;

int dist[MAXN], N;
typedef pair<int, int> ii;
vector<ii> adjList[MAXN];

//O(VE)
int bellmanford(int s, int t)
	memset(&dist, 1<<20, sizeof dist);
	dist[s] = 0;
	bool hasNegativeWeightCycle = false;
	for (int i = 0, v, w; i < N; i++) {
		for (int u = 0; u < N; u++) {
			for (int j = 0; j < (int)adjList[u].size(); j++) {
				v = adjList[u][j].first;
				w = adjList[u][j].second;
				if (i==N-1 && dist[v] > dist[u] + w)
					hasNegativeWeightCycle = true;
				else dist[v] = min(dist[v], dist[u] + w);
			}
		}
	}
	return dist[t];
}