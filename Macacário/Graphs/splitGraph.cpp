#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <algorithm>
using namespace std;

/*
* Verifies if a graph is split in O(Nlog(N)) and build it in O(N). A split graph can
* be divided in a complete graph and a independent set (graph with 0 edges).
*/
class SplitGraph {

public:

	SplitGraph(int N, vector<int>* g): d(N)
	{
		computeSplit(g, N);
		if (isSplit()) build(N);
	}

	vector<int> getCliqueSet(){
		return K;
	}

	vector<int> getStableSet(){
		return I;
	}

	bool isSplit() {
		return maxClique >= 0;
	}

	int maximumClique() {
		return maxClique;
	}

private:
	int maxClique;
	vector<pair<int, int> > d;
	vector<int> K, I, verts;

	void computeSplit(vector<int>* g, int N) {
		for (int i = 0; i < N; ++i) d[i] = {g[i].size(), i};
		sort(d.begin(), d.end());

		int m = N;
		for (int i = 0; i < N; ++i) {
			if (d[i].first >= N - i - 1) {
				m = i;
				break;
			}
		}

		long long lowSum = 0, highSum = 0;

		for (int i = 0; i < m; ++i) lowSum += d[i].first;
		for (int i = m; i < N; ++i) highSum += d[i].first;
		m = N - m;

		if (lowSum + m * 1LL * (m - 1) == highSum) {
			maxClique = m;
		}
		else {
			maxClique = -1;
		}
	}

	void build(int N){
		for (int i = 0; i < N - maxClique; ++i){
			I.push_back(d[i].second);
		}for (int i = N - maxClique; i < N; ++i){
			K.push_back(d[i].second);
		}
	}

};

/*
* Example: URI 1974 - Into darkness
*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <set>

#define MAXN 1009
#define MAXM 109
#define MAXS 210000
#define ALFA 2
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
typedef long long int ll;
typedef pair<int, int> ii;

int N, M;
vector<int> g[MAXN];
vector< pair<int, ii> > edgeList;
char code[MAXN][MAXM];
int len[MAXN];
ll MOD = 1000000009;

class SuffixAutomaton {
	int len[MAXS], link[MAXS], cnt[MAXS];
	int nxt[MAXS][ALFA], sz, last, root;
	int newnode() {
		int x = ++sz;
		len[x] = 0; link[x] = -1; cnt[x] = 1;
		for(int c = 0; c < ALFA; c++) nxt[x][c] = 0;
		return x;
	}
	inline int reduce(char c) { return c - '0'; }
public:
	SuffixAutomaton() { clear(); }
	void clear() {
		sz = 0;
		root = last = newnode();
	}
	void insert(const char *s) {
		for(int i = 0; s[i]; i++) extend(reduce(s[i]));
	}
	void extend(int c) {
		int cur = newnode(), p;
		len[cur] = len[last] + 1;
		for(p = last; p != -1 && !nxt[p][c]; p = link[p]) {
			nxt[p][c] = cur;
		}
		if (p == -1) link[cur] = root;
		else {
			int q = nxt[p][c];
			if (len[p] + 1 == len[q]) link[cur] = q;
			else {
				int clone = newnode();
				len[clone] = len[p] + 1;
				for(int i = 0; i < ALFA; i++)
					nxt[clone][i] = nxt[q][i];
				link[clone] = link[q];
				cnt[clone] = 0;
				while(p != -1 && nxt[p][c] == q) {
					nxt[p][c] = clone;
					p = link[p];
				}
				link[q] = link[cur] = clone;
			}	
		}
		last = cur;
	}

	int longestCommonSubstring(const char *s) {
		int cur = root, curlen = 0, ans = 0;
		for(int i = 0; s[i]; i++) {
			int c = reduce(s[i]);
			while(cur != root && !nxt[cur][c]) {
				cur = link[cur];
				curlen = len[cur];
			}
			if (nxt[cur][c]) {
				cur = nxt[cur][c];
				curlen++;
			}
			if (ans < curlen) ans = curlen;
		}
		return ans;
	}
private:
	int deg[MAXS];
};

class UnionFind {
private:
	vector<int> parent, rank;
public:
	UnionFind(int N) {
		rank.assign(N + 9, 0);
		parent.assign(N + 9, 0);
		for (int i = 0; i < N; i++) parent[i] = i;
	}
	int find(int i) {
		while (i != parent[i]) i = parent[i];
		return i;
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	void unionSet(int i, int j) {
		if (isSameSet(i, j)) return;
		int x = find(i), y = find(j);
		if (rank[x] > rank[y]) parent[y] = x;
		else {
			parent[x] = y;
			if (rank[x] == rank[y]) rank[y]++;
		}
	}
};

ll kruskal() {
	ll cost = 0;
	UnionFind UF(N);
	sort(edgeList.begin(), edgeList.end());
	for (auto edge : edgeList) {
		if (!UF.isSameSet(edge.second.first, edge.second.second)) {
			cost += edge.first;
			UF.unionSet(edge.second.first, edge.second.second);
		}
	}
	return cost;
}

int minCost(SplitGraph& sg) {
	SuffixAutomaton sa;
	for (auto& edge : edgeList){
		sa.clear();
		int u = edge.second.first;
		int v = edge.second.second;

		sa.insert(code[u]);
		edge.first = sa.longestCommonSubstring(code[v]);
	}

	return kruskal();
}

int vis[MAXN];

bool isConnected() {
	int count = 1;
	queue<int> inuse;

	inuse.push(0);
	vis[0] = 1;
	while (!inuse.empty()) {
		int u = inuse.front();
		inuse.pop();

		for (int v : g[u]) {
			if (!vis[v]) {
				vis[v] = 1;
				++count;
				inuse.push(v);
			}
		}
	}
	return count == N;
}

int main() {
	int u, v;

	scanf("%d%d", &N, &M);

	FOR(i, M) {
		scanf("%d%d", &u, &v);
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
		edgeList.push_back({ 0, {u, v} });
	}
	FOR(i, N) {
		scanf("%s", code[i]);
		len[i] = strlen(code[i]);
	}
	auto sg = SplitGraph(N, g);

	if (!isConnected() || !sg.isSplit()) {
		printf(":[\n");
	}
	else {
		int trainees = sg.maximumClique();
		printf(":]\n%d %d %d\n", trainees, N - trainees, minCost(sg));
	}
}
