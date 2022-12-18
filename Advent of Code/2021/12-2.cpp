#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

string names[MAXN];
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
		names[n] = s;
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
			int u = getNode(a), v = getNode(b);
			//printf("%s(%d) to %s(%d)\n", a.c_str(), u, b.c_str(), v);
			g[u].push_back(v);
			g[v].push_back(u);
			break;
		}
	}
	for (int u = 0; u < n; u++) {
		sort(g[u].begin(), g[u].end(), [](int a, int b) {
			return names[a] < names[b];
		});
	}
}

int ans = 0;
int st, en;
int visited[MAXN];
bool visitedTwice = false;
vector<int> path;

void printPath() {
	for (int u : path) {
		if (u != st) printf(",%s", names[u].c_str());
		else printf("%s", names[u].c_str());
	}
	printf("\n");
}

void dfs(int u) {
	if (u == en) {
		ans++;
		//printPath();
		return;
	}
	if (!isBig[u]) {
		if (visited[u] > 0 && visitedTwice) return;
		if (visited[u] == 1 && u == st) return;
	}
	visited[u]++;
	if (!isBig[u] && visited[u] == 2) visitedTwice = true;
	for (int v : g[u]) {
		path.push_back(v);
		dfs(v);
		path.pop_back();
	}
	visited[u]--;
	if (!isBig[u] && visited[u] == 1) visitedTwice = false;
}

int main () {
	readInput();
	memset(visited, 0, sizeof visited);
	st = getNode("start");
	en = getNode("end");
	path.push_back(st);
	dfs(st);
	printf("%d\n", ans);
	return 0;
}
