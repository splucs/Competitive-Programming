#include <vector>
#include <set>
#include <queue>
using namespace std;
#define MAXN 109
#define MAXM 10009

typedef pair<int,int> ii;
vector<ii> adjList[MAXN];
vector<int> Q, A[MAXM];
ii edges[MAXM];
vector<bool> T, Fcolors;
set<int> F;
int c[MAXM], N, M, C;

class UnionFind {
private:
	vector<int> parent, rank;
public:
	UnionFind(int N) {
    	rank.assign(N+1, 0);
		parent.assign(N+1, 0);
		for (int i = 0; i <= N; i++) parent[i] = i;
	}
	int find(int i) {
		while(i != parent[i]) i = parent[i];
		return i;
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	void unionSet (int i, int j) {
		if (isSameSet(i, j)) return;
		int x = find(i), y = find(j);
		if (rank[x] > rank[y]) parent[y] = x;
		else {
			parent[x] = y;
			if (rank[x] == rank[y]) rank[y]++;
		}
	}
};

vector<int> findCycle(int s, int t) {
	vector<int> ans; vector<ii> prev;
	queue<int> q;
	prev.assign(N, ii(-1, -1));
	q.push(s); prev[s] = ii(s, -1);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == t) break;
		for (int i = 0; i < (int)adjList[u].size(); i++) {
			int v = adjList[u][i].first;
			if (prev[v].first == -1) {
				prev[v] = ii(u, adjList[u][i].second);
				q.push(v);
			}
		}
	}
	while (t != s) {
		ans.push_back(prev[t].second);
		t = prev[t].first;
	}
	return ans;
}

void start() {
	T.assign(M, false); Q.clear();
	for (int i=0; i<N; i++) adjList[i].clear();
	for (int i=0; i<M; i++) A[i].clear();
}

void greedyAugmentation(UnionFind &UF) {
	int e, u, v;
	Fcolors.assign(C, false);
	for (set<int>::iterator it = F.begin(); it != F.end(); it++) {
		e = *it;
		u = edges[e].first, v = edges[e].second;
		UF.unionSet(u, v);
		adjList[u].push_back(ii(v, e));
		adjList[v].push_back(ii(u, e));
		Fcolors[c[e]] = true;
	}
	for (int i = 0; i < M; i++) {
		u = edges[i].first, v = edges[i].second;
		if (!UF.isSameSet(u, v) && !Fcolors[c[i]]) {
			UF.unionSet(u, v);
			adjList[u].push_back(ii(v, i));
			adjList[v].push_back(ii(u, i));
			Fcolors[c[i]] = true;
			F.insert(i);
		}
	}
}

void digraphConstruction(UnionFind &UF) {
	vector<int> cycle;
	for (int i = 0; i < M; i++) {
		if (F.count(i)) continue;
		if (!Fcolors[c[i]]) Q.push_back(i);
		else for (set<int>::iterator it = F.begin(); it != F.end(); it++) {
			if (c[*it] == c[i]) A[*it].push_back(i);
		}
		if (!UF.isSameSet(edges[i].first, edges[i].second)) T[i] = true;
		else {
			cycle = findCycle(edges[i].first, edges[i].second);
			for (int j = 0; j < (int)cycle.size(); j++)
            	A[i].push_back(cycle[j]);
		}
	}
}

bool augmentation() {
	queue<int> q;
	vector<int> prev;
	prev.assign(M, -1);
	for (int i = 0; i < (int)Q.size(); i++) {
		q.push(Q[i]);
		prev[Q[i]] = Q[i];
	}
	int u, v, found = -1;
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (T[u]) {
			found = u; break;
		}
		for (int i = 0; i < (int)A[u].size(); i++) {
			v = A[u][i];
			if (prev[v] == -1) {
				prev[v] = u; q.push(v);
			}
		}
	}
	if (found == -1) return false;
	u = found;
	while (true) {
		if (F.count(u)) F.erase(u);
		else F.insert(u);
		if (u == prev[u]) break;
		u = prev[u];
	}
	return true;
}

void buildSpanningTree() {
	F.clear();
	while (true) {
		UnionFind UF(M);
		start();
		greedyAugmentation(UF);
		digraphConstruction(UF);
		if (!augmentation()) break;
	}
}

/*
 * URI 2128
 */

#include <cstdio>

int main() {
    int u,v,c1,t=1;
    while (scanf("%d%d%d",&N,&M,&C)!=EOF) {
        for (int i=0;i<M;i++) {
            scanf("%d%d%d",&u,&v,&c1);
            u--, v--, c1--;
            edges[i] = ii(u, v);
            c[i] = c1;
        }
        buildSpanningTree();
        if (F.size()!=N-1) {
            printf("Instancia %d\nnao\n\n",t++);
        }else{
            printf("Instancia %d\nsim\n\n",t++);
        }
    }
}
