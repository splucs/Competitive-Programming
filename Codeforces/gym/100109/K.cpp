#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MOD 99990001ll

typedef long long ll;

typedef pair<ll, int> ii;
map<int, ll> adj[MAXN];

void multiply(int u, ll w) {
	printf("multiplying graph rooted at %d by %I64d\n", u, w);
	queue<int> bfs;
	set<int> vis;
	vis.insert(u);
	bfs.push(u);
	while(!bfs.empty()) {
		u = bfs.front();
		bfs.pop();
		for(map<int, ll>::iterator it = adj[u].begin(); it!=adj[u].end(); it++) {
			it->second = (it->second+w)%MOD;
			int v = it->first;
			printf("%d-%d went from %I64d to %I64d\n", u, v, it->second-w, it->second);
			if (!vis.count(v)){
				vis.insert(v);
				bfs.push(v);
			}
		}
	}
}

bool lesser(int u, int v) {
	queue<int> bfsu, bfsv;
	set<int> visu, visv;
	visu.insert(u);
	visv.insert(v);
	bfsu.push(u);
	bfsv.push(v);
	while(!bfsu.empty()) {
		u = bfsu.front();
		bfsu.pop();
		for(map<int, ll>::iterator it = adj[u].begin(); it!=adj[u].end(); it++) {
			v = it->first;
			if (!visu.count(v)){
				visu.insert(v);
				bfsu.push(v);
			}
		}
		if (bfsv.empty()) return false;
		u = bfsv.front();
		bfsv.pop();
		for(map<int, ll>::iterator it = adj[u].begin(); it!=adj[u].end(); it++) {
			v = it->first;
			if (!visv.count(v)){
				visv.insert(v);
				bfsv.push(v);
			}
		}
	}
	if (!bfsv.empty()) return true;
	return (*visu.begin()) < (*visv.begin());
}

int eu[MAXN], ev[MAXN];
ll ew[MAXN];

int main() {
	int u, v, n;
	scanf("%d", &n);
	ll w;
	for(int i=1; i<n; i++) {
		scanf("%d %d %I64d", &u, &v, &w);
		eu[i] = u;
		ev[i] = v;
		ew[i] = w;
		adj[u][v] = adj[v][u] = w;
	}
	int p;
	for(int i=1; i<n; i++) {
		scanf("%d", &p);
		w = adj[eu[p]][ev[p]];
		printf("%I64d\n", w);
		fflush(stdout);
		
		adj[eu[p]].erase(ev[p]);
		adj[ev[p]].erase(eu[p]);
		if (lesser(eu[p], ev[p])) {
			printf("%d is smaller\n", eu[p]);
			multiply(eu[p], w);
		}
		else {
			printf("%d is smaller\n", ev[p]);
			multiply(ev[p], w);
		}
	}
}