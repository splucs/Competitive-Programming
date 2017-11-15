#include <bits/stdc++.h>
using namespace std;
#define MAXN 509
#define MAXS 2000009

char board[MAXN][MAXN];
int pos[MAXN][MAXN][4][2];
vector<int> adjList[MAXS];
int N, M, nNodes;
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

#define UNVISITED -1
#define EXPLORED -2
#define VISITED -3

int num[MAXS], vis[MAXS], component[MAXS], low[MAXS];
int counter, numSCC;
stack<int> S;

void dfs(int u) {
	low[u] = num[u] = counter++;
	S.push(u);
	vis[u] = 1;
	int v;
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) dfs(v);
		if (vis[v]) low[u] = min(low[u], low[v]);
	}
	if (low[u] == num[u]) {
		while (true) {
			v = S.top(); S.pop(); vis[v] = 0;
			component[v] = numSCC;
			if (u == v) break;
		}
		numSCC++;
	}
}

void tarjan(){
	counter = numSCC = 0;
	for (int i = 0; i < nNodes; i++) num[i] = UNVISITED;
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 0; i < nNodes; i++){
		if (num[i] == UNVISITED)
			dfs(i);
	}
}

bool iswhite(int i, int j) {
	if (i < 0 || j < 0 || i >= N || j >= M) return false;
	return board[i][j] == 'W';
}

bool isblack(int i, int j) {
	if (i < 0 || j < 0 || i >= N || j >= M) return false;
	return board[i][j] == 'B';
}

typedef pair<int, int> ii;
vector<ii> getadj(int i, int j, int dir) {
	vector<ii> ans;
	ans.push_back(ii(i+di[dir], j+dj[dir]));
	ans.push_back(ii(i+di[(dir+1)%4], j+dj[(dir+1)%4]));
	return ans;
}

void black(const int i, const int j, const int dir) {
	if (board[i][j] != 'B') return;
	if (dir < 0 || dir >= 4) printf("error!\n");
	int ni = i + di[dir];
	int nj = j + dj[dir];
	int pu = pos[i][j][dir][1];
	int nu = pos[i][j][dir][0];
	if (!iswhite(ni, nj)) {
		adjList[pu].push_back(nu);
	}
	if (isblack(ni, nj) || iswhite(ni, nj)) {
		if ((dir+2)%4 < 0 || (dir+2)%4 >= 4) printf("error!\n");
		adjList[pu].push_back(pos[ni][nj][(dir+2)%4][1]);
		adjList[nu].push_back(pos[ni][nj][(dir+2)%4][0]);
	}
	adjList[pu].push_back(pos[i][j][(dir+2)%4][0]);
	adjList[nu].push_back(pos[i][j][(dir+2)%4][1]);
}

void white(const int i, const int j, const int dir) {
	if (board[i][j] != 'W') return;
	if (dir < 0 || dir >= 4) printf("error!\n");
	int ni = i + di[dir];
	int nj = j + dj[dir];
	int pu = pos[i][j][dir][1];
	int nu = pos[i][j][dir][0];
	if (!isblack(ni, nj)) {
		adjList[pu].push_back(nu);
	}
	if (isblack(ni, nj) || iswhite(ni, nj)) {
		if ((dir+2)%4 < 0 || (dir+2)%4 >= 4) printf("error!\n");
		adjList[pu].push_back(pos[ni][nj][(dir+2)%4][1]);
		adjList[nu].push_back(pos[ni][nj][(dir+2)%4][0]);
	}
	for(int k=0; k<4; k++) {
		if (k == dir) continue;
		adjList[pu].push_back(pos[i][j][k][0]);
	}
}

int main() {
	int T, nWhite, nBlack;
	scanf(" %d", &T);
	while(T --> 0) {
		scanf(" %d %d", &N, &M);
		nWhite = nBlack = nNodes = 0;
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				scanf(" %c", &board[i][j]);
				if (board[i][j] == 'B') nBlack++;
				if (board[i][j] == 'W') nWhite++;
				for(int k=0; k<4; k++) pos[i][j][k][0] = pos[i][j][k][1] = -1;
				if(board[i][j] != '.') for(int k=0; k<4; k++) {
					pos[i][j][k][0] = nNodes++;
					pos[i][j][k][1] = nNodes++;
				}
			}
		}
		
		for(int u=0; u<nNodes; u++) adjList[u].clear();
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				if(board[i][j] == 'B') {
					for(int k=0; k<4; k++) black(i, j, k);
				}
				if(board[i][j] == 'W') {
					for(int k=0; k<4; k++) white(i, j, k);
				}
			}
		}
		
		tarjan();
		bool ok = true;
		if (2*nBlack != nWhite) ok = false;
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				if(board[i][j] == 'B' || board[i][j] == 'W') {
					for(int k=0; k<4; k++) {
						if (component[pos[i][j][k][1]] == component[pos[i][j][k][0]]) ok = false;
					}
				}
			}
		}
		
		if (ok) printf("YES\n");
		else printf("NO\n");
	}
	
	return 0;
}