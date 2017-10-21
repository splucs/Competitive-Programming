#include <bits/stdc++.h>
using namespace std;
#define MAXN 2005
#define INF 1000000009

/* Codechef Problem: A game on a graph
// Blossom algorithm O(N^3)
// https://www.codechef.com/problems/HAMILG
*/
int mQueue[MAXN], qHead, qTail, match[MAXN], cur_blossom[MAXN], parent[MAXN], N;
bool inPath[MAXN], inQueue[MAXN], inBlossom[MAXN];

vector<vector<int> > G;

void push(int u) {
	mQueue[qTail++] = u;
	inQueue[u] = true;
}

int lca(int u, int v) {
	memset(inPath, 0, sizeof(inPath));
	u = cur_blossom[u];
	while(true) {
		inPath[u] = true;
		if(match[u] == -1 || parent[match[u]] == -1) break;
		u = cur_blossom[parent[match[u]]];
	}

	v = cur_blossom[v];
	while(true) {
		if(inPath[v]) return v;
		v = cur_blossom[parent[match[v]]];
	}

	return v;
}

int find_aug_path(int R) {
	int u, viz;
	memset(inQueue, 0, sizeof(inQueue));
	memset(parent, -1, sizeof(parent));
	for(int i = 0; i < N; i++) cur_blossom[i] = i;
	qTail = qHead = 0;
	push(R);
	
	while(qHead < qTail) {
		u = mQueue[qHead++];
		for (int i = 0; i < G[u].size(); i++) {
			viz = G[u][i];
			if(viz != match[u] && cur_blossom[viz] != cur_blossom[u]) {
				if(parent[viz] == -1 && !(match[viz] != -1 && parent[match[viz]] != -1)) {
					if(viz == R) continue;
					parent[viz] = u;
					if(match[viz] == -1) return viz; // augmenting path to viz
					push(match[viz]);
					continue;
				}

				if(viz != R && !(match[viz] != -1 && parent[match[viz]] != -1)) continue;

				// blossom found
				int new_blossom = lca(u,viz);
				memset(inBlossom, 0, sizeof(inBlossom));
				
				int v = u, parent_v = viz;
				while(cur_blossom[v] != new_blossom) {
					inBlossom[cur_blossom[v]] = inBlossom[cur_blossom[match[v]]] = true;
					parent[v] = parent_v;
					parent_v = match[v];
					v = parent[match[v]];
				}

				v = viz, parent_v = u;
				while(cur_blossom[v] != new_blossom) {
					inBlossom[cur_blossom[v]] = inBlossom[cur_blossom[match[v]]] = true;
					parent[v] = parent_v;
					parent_v = match[v];
					v = parent[match[v]];
				}

				for(int i =0; i < N; i++) if(inBlossom[cur_blossom[i]]) {
					cur_blossom[i] = new_blossom;
					if(!inQueue[i]) {
						push(i);
					}
				}
			}	
		}
	}

	return -1;
}

void MaxMatch() {
	memset(match, -1, sizeof(match));

	for (int i = 0; i < N; i++) {
		if (match[i] < 0) {
			int v = find_aug_path(i); 
			
			while(v != -1) {
				int parent_v = match[parent[v]];
				match[v] = parent[v];
				match[parent[v]] = v;
				v = parent_v;
			}
		}
	}
}

bool marked[MAXN];

void dfs(int R) {
	int u, viz;
	memset(inQueue, 0, sizeof(inQueue));
	memset(parent, -1, sizeof(parent));

	for(int i =0; i < N; i++) cur_blossom[i] = i;
	
	qTail = qHead = 0;
	push(R);
	
	while(qHead < qTail) {
		u = mQueue[qHead++];
		marked[u] = true;
		for (int i = 0; i < G[u].size(); i++) {
			viz = G[u][i];
			if(viz != match[u] && cur_blossom[viz] != cur_blossom[u]) {
				if(parent[viz] == -1 && !(match[viz] != -1 && parent[match[viz]] != -1)) {
					if(viz == R) continue;
					parent[viz] = u;
					if(match[viz] == -1) return; // augmenting path to viz
					push(match[viz]);
					continue;
				}

				if(viz != R && !(match[viz] != -1 && parent[match[viz]] != -1)) continue;

				// blossom found
				int new_blossom = lca(u,viz);
				memset(inBlossom, 0, sizeof(inBlossom));

				int v = u, parent_v = viz;
				while(cur_blossom[v] != new_blossom) {
					inBlossom[cur_blossom[v]] = inBlossom[cur_blossom[match[v]]] = true;
					parent[v] = parent_v;
					parent_v = match[v];
					v = parent[match[v]];}

				v =viz, parent_v = u;
				while(cur_blossom[v] != new_blossom) {
					inBlossom[cur_blossom[v]] = inBlossom[cur_blossom[match[v]]] = true;
					parent[v] =parent_v;
					parent_v =match[v];
					v =parent[match[v]];}

				for(int i =0; i < N; i++) if(inBlossom[cur_blossom[i]]) {
					cur_blossom[i] = new_blossom;
					if(!inQueue[i]) {
						push(i);
					}
				}
			}	
		}
	}

	return;
}

int main() {
	int t, a, b, M;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &N, &M);

		G.clear();
		G.resize(N+5);
		
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &a, &b);a--;b--;
			G[a].push_back(b);
			G[b].push_back(a);
		}
		MaxMatch();

		int ans = 0;
		memset(marked, 0, sizeof(marked));
		
		for (int u = 0; u < N; u++) {
			if (!marked[u] && match[u] == -1) {
				dfs(u);
			}
		}
		for (int u = 0; u < N; u++) {
			if (marked[u]) ans++;
		}
		printf("%d\n", ans);
	}

}

