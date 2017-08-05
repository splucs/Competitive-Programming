#include <vector>
#include <stack>
#define MAXN 400009
using namespace std;

vector<int> adjList[MAXN];
int N, M;

vector<int> euler(int s = 0) {
	vector<int> work(N, 0), in(N, 0), out(N, 0), tour;
	for(int u = 0; u < N; u++) {
		for(int i=0; i<(int)adjList[u].size(); i++) {
			int v = adjList[u][i];
			out[u]++; in[v]++;
		}
	}
	int cntin = 0, cntout = 0;
	for (int u = 0; u < N; u++) {
		if (in[u] == out[u]+1) {
			cntout++;
			if (cntout == 2) return tour;
		}
		else if (out[u] == in[u]+1) {
			cntin++; s = u;
			if (cntin == 2) return tour;
		}
		else if (out[u] != in[u] || in[u]==0) return tour;
	}
	stack<int> dfs;
	dfs.push(s);
	while (!dfs.empty()) {
		int u = dfs.top();
		if (work[u] < (int)adjList[u].size()) {
			dfs.push(adjList[u][work[u]++]);
		}
		else {
			tour.push_back(u);
			dfs.pop();
		}
	}
	int n = tour.size();
	for(int i=0; 2*i<n; i++) swap(tour[i], tour[n-i-1]);
	return tour;
}

/*
 * Codeforces 508D
 */

#include <map>
#include <cstring>
#include <cstdio>

typedef pair<char, char> cc;
cc id2cc[MAXN];
map<cc, int> cc2id;
int deg[MAXN];

int main()
{
	char s[5];
	int u, v;
	N = 0;
	scanf("%d", &M);
	memset(&deg, 0, sizeof deg);
	for(int i=0; i<M; i++) {
		scanf(" %s", s);
		cc p1 = make_pair(s[0], s[1]);
		cc p2 = make_pair(s[1], s[2]);
		if (!cc2id.count(p1)) {
			//printf("%c%c: %d\n", p1.first, p1.second, N);
			id2cc[N] = p1;
			cc2id[p1] = N++;
		}
		if (!cc2id.count(p2)) {
			//printf("%c%c: %d\n", p2.first, p2.second, N);
			id2cc[N] = p2;
			cc2id[p2] = N++;
		}
		u = cc2id[p1];
		v = cc2id[p2];
		adjList[u].push_back(v);
		deg[v]++;
	}
	vector<int> ans = euler();
	int n = ans.size();
	if (M + 1 != n) {
		printf("NO\n");
	}
	else {
		printf("YES\n");
		for(int i=0; i<n; i++) {
			printf("%c", id2cc[ans[i]].first);
		}
		printf("%c\n", id2cc[ans.back()].second);
	}
	return 0;
}