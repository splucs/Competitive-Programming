#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXS 109

char buffer[MAXS];

vector<int> adjList[MAXN];
string name[MAXN], ans[MAXN];
int sz, par[MAXN], size[MAXN], W, npages;
bool closed[MAXN], possible;

bool comp(int i, int j) {
	return size[i] > size[j];
}

int dfs(int u) {
	size[u] = 1;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		size[u] += dfs(v);
	}
	sort(adjList[u].begin(), adjList[u].end(), comp);
	for(int i=0; i<(int)adjList[u].size() && size[u] > W; i++) {
		int v = adjList[u][i];
		size[u] -= size[v] - 1;
		npages++;
		closed[v] = true;
	}
	sort(adjList[u].begin(), adjList[u].end());
	if (size[u] > W) possible = false;
	return size[u];
}

void dfsans(int u, string & cur, int h) {
	for(int i=0; i<h; i++) cur = cur + "| ";
	cur = cur + name[u] + "\n";
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (closed[v]) {
			string cl = "+" + string(name[v].c_str()+1) + "\n";
			for(int i=0; i<h+1; i++) cl = "| " + cl;
			cur = cur + cl;
			dfsans(v, ans[v], 0);
		}
		else dfsans(v, cur, h+1);
	}
	if (closed[u]) cur = cur + "====================\n";
}

void printdfs(int u) {
	printf(ans[u].c_str());
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		printdfs(v);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	sz = 0;
	scanf("%d", &W);
	
	scanf(" %s", buffer);
	int last = 0, cur, u=++sz, v;
	name[u] = buffer;
	par[u] = -1;
	
	while(!feof(stdin)) {
		cur = 0;
		while(scanf(" %s ", buffer), strcmp(buffer, "|") == 0) cur++;
		v = ++sz;
		while (cur < last+1) {
			u = par[u];
			last--;
		}
		
		name[v] = buffer;
		par[v] = u;
		adjList[u].push_back(v);
		u = v;
		last = cur;
	}
	npages = 1;
	possible = true;
	dfs(1);
	if (possible) {
		closed[1] = true;
		dfsans(1, ans[1], 0);
		printf("%d\n", npages);
		printdfs(1);
	}
	else printf("IMPOSSIBLE\n");

	fclose(stdin);
	fclose(stdout);
	return 0;
}