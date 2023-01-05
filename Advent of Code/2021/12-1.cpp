#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

map<string, int> name2node;
vector<int> g[MAXN];
int n;
bool isBig[MAXN];

int getNode(string s) {
	if (!name2node.count(s)) {
		name2node[s] = n;
		if (s[0] >= 'A' && s[0] <= 'Z') {
			isBig[n] = true;
		}
		n++;
	}
	return name2node[s];
}

void readInput() {
	char line[209];
	memset(isBig, 0, sizeof(isBig));
	n = 0;

	while(scanf(" %s", line) != EOF) {
		for (int i = 0; i < strlen(line); i++) {
			if (line[i] != '-') {
				continue;
			}
			string a(line, line+i);
			string b(line+i+1, line+strlen(line));
			printf("%s to %s\n", a.c_str(), b.c_str());
			int u = getNode(a), v = getNode(b);
			g[u].push_back(v);
			g[v].push_back(u);
			break;
		}
	}
}

int ans = 0;
int st, en;
bool visited[MAXN];

void dfs(int u) {
	if (u == en) {
		ans++;
		return;
	}
	if (visited[u] && !isBig[u]) {
		return;
	}
	visited[u] = true;
	for (int v : g[u]) {
		dfs(v);
	}
	visited[u] = false;
}

int main () {
	readInput();
	memset(visited, false, sizeof visited);
	st = getNode("start");
	en = getNode("end");
	dfs(st);
	printf("%d\n", ans);
	return 0;
}
