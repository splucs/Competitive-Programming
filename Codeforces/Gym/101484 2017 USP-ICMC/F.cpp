#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

vector<int> adjList[MAXN];
typedef long long ll;
ll heap[MAXN], shine[MAXN], sum[MAXN];
int nd2heap[MAXN], N, M;

void buildheap(int h, int u) {
	nd2heap[u] = h;
	heap[h] = shine[u];
	for(int i=0; i<(int)adjList[u].size(); i++) {
		buildheap(2*h + i, adjList[u][i]);
	}
	adjList[u].clear();
}

int main() {
	scanf("%d %d %I64d", &N, &M, &shine[1]);
	int u, v, h;
	ll w;
	for(int i=1; i<N; i++) {
		scanf("%d %d %I64d", &u, &v, &w);
		adjList[v].push_back(u);
		shine[u] = w;
	}
	
	memset(&heap, 0, sizeof heap);
	buildheap(1, 1);
	int n = 1;
	while(n-1 < N) n <<= 1;
	n--;
	sum[0] = 0;
	for(int i=1; i<=n; i++) sum[i] = sum[i-1] + heap[i];
	
	int l, r, i, j;
	ll ans, cur;
	for(int q=0; q<M; q++) {
		scanf("%d", &u);
		l = r = nd2heap[u];
		i = 1, j = 1;
		ans = 0;
		while(i <= n) {
			cur = 0;
			if (l >= i && r <= j) {
				cur = sum[l-1] - sum[i-1] + sum[j] - sum[r];
				l = 2*l;
				r = 2*r + 1;
			}
			else cur = sum[j] - sum[i-1];
			i = 2*i;
			j = 2*j + 1;
			ans = max(ans, cur);
		}
		printf("%I64d\n", ans);
	}
	
	return 0;
}