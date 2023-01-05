#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXK 20

char buffer[30];
int dist[1<<MAXK];

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	
	queue<int> q;
	memset(&dist, -1, sizeof dist);
	
	for(int i=0; i<N; i++) {
		scanf(" %s", buffer);
		int mask = 0;
		for(int j=0; j<K; j++) {
			if (buffer[j] == '1') mask |= (1<<j);
		}
		dist[mask] = 0;
		q.push(mask);
	}
	
	int ans = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int j=0; j<K; j++) {
			int v = u^(1<<j);
			if (dist[v] < 0) {
				dist[v] = dist[u]+1;
				q.push(v);
				ans = v;
			}
		}
	}
	
	for(int j=0; j<K; j++) {
		if (ans & (1<<j)) printf("1");
		else printf("0");
	}
	printf("\n");
	
	return 0;
}