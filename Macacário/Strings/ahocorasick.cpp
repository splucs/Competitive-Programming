#include <queue>
#include <vector>
using namespace std;
#define ALFA 256
#define MAXS 2000009
typedef pair<int, int> ii;

/*
 * Aho-Corasick's Algorithm
 */

int go[MAXS][ALFA], link[MAXS], h[MAXS], cnt = 0;
vector<int> pats[MAXS], adj[MAXS];

int suffix(int u, char c) {
	while (u && !go[u][c]) u = link[u];
	return go[u][c];
}

void aho() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < (int)adj[u].size(); i++) {
			int c = adj[u][i];
			int v = go[u][c];
			link[v] = u ? suffix(link[u], c) : 0;
			pats[v].insert(pats[v].end(), pats[link[v]].begin(), pats[link[v]].end());
			q.push(v);
		}
	}
}

void insert(const char s[], int id) {
	int u = 0;
	for (int i = 0; s[i]; i++) {
		int &v = go[u][s[i]];
		if (!v) {
			v = ++cnt;
			adj[u].push_back(s[i]);
			h[v] = i + 1;
		}
		u = v;
	}
	pats[u].push_back(id);
}

vector<ii> match(const char s[]) { //(id, pos)
	vector<ii> ans;
	for (int i = 0, u = 0; s[i]; i++) {
		u = suffix(u, s[i]);
		for(int j = 0; j < (int)pats[u].size(); j++) {
			int id = pats[u][j];
			ans.push_back(ii(id, i - h[u] + 1));
		}
	}
	return ans;
}

/*
 * SPOJ SUB_PROB
 */

#include <cstdio>
#define MAXN 100009

char str[MAXN], in[MAXN];
bool found[MAXN];
int N;

int main() {
	scanf(" %s %d", str, &N);
	for (int i = 0; i < N; i++) {
		scanf(" %s", in);
		insert(in, i);
	}
	aho();
	vector<ii> ans = match(str);
	memset(&found, false, sizeof found);
	for (int i = 0; i < (int)ans.size(); i++) {
		found[ans[i].first] = true;
	}
	for (int i = 0; i < N; i++) {
		if (found[i]) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
