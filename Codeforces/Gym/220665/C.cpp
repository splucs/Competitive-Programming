#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define ALFA 27

int adjList[MAXN][ALFA], sons[MAXN], mex[MAXN], sz;
const int root = 1;

void insert(int u, char *str) {
	if (!str[0]) return;
	int n = str[0] - 'a';
	if (!adjList[u][n]) {
		adjList[u][n] = ++sz;
		sons[sz] = 0;
		sons[u]++;
	}
	insert(adjList[u][n], str+1);
}

char str[MAXN];

int Mex(int u) {
	if (mex[u] != -1) return mex[u];
	set<int> s;
	for(int i = 0; i < ALFA; i++) {
		if (adjList[u][i]) {
			s.insert(Mex(adjList[u][i]));
		}
	}
	mex[u] = 0;
	while(s.count(mex[u])) mex[u]++;
	return mex[u];
}

int main() {
	int N, K;
	scanf("%d %d", &N, &K);

	memset(&adjList, 0, sizeof adjList);
	sz = root;
	sons[root] = 0;
	while(N --> 0) {
		scanf(" %s", str);
		insert(root, str);
	}
	
	//force win
	memset(&mex, -1, sizeof mex);
	for(int u = 1; u <= sz; u++) {
		if (sons[u] == 0) mex[u] = 0;
	}
	bool forceWin = Mex(root) > 0;
	
	//force lose
	memset(&mex, -1, sizeof mex);
	for(int u = 1; u <= sz; u++) {
		if (sons[u] == 0) mex[u] = 1;
	}
	bool forceLose = Mex(root) > 0;

	if (!forceWin) printf("Second\n");
	else if (forceLose) printf("First\n");
	else {
		if (K % 2 == 0) printf("Second\n");
		else printf("First\n");
	}

	return 0;
}