#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1<<30)

typedef long long ll;
ll t[MAXN], b[MAXN];
vector<ll> adj[MAXN];

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) {
		scanf("%I64d", &t[i]);
		if (i > 0) adj[i].push_back(t[i-1]);
	}
	t[N] = INF;
	for(int i=0, j=0; i<M; i++) {
		scanf("%I64d", &b[i]);
		while(j < N && b[i] > t[j]) j++;
		adj[j].push_back(b[i]);
	}
	ll ans = 0;
	for(int i=1; i<N; i++){
		ll dx = 0;
		adj[i].push_back(t[i]);
		if (adj[i].size() == 2u) continue;
		for(int j=1; j<(int)adj[i].size(); j++){
			dx = max(dx, adj[i][j] - adj[i][j-1]);
		}
		ans += min(t[i] - t[i-1], 2*(t[i] - t[i-1] - dx));
	}
	if (!adj[0].empty()) ans += 2*(t[0] - b[0]);
	if (!adj[N].empty()) ans += 2*(b[M-1] - t[N-1]);
	printf("%I64d\n", ans);
	return 0;
}