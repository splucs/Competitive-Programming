#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN];
bool vis[MAXN];
int m, n;
///Vértices enumerados de 1 a m em U e de 1 a n em V!!!!

bool dfs(int u)
{
    vis[u] = true;
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i){
        v = adjU[u][i];
        if (!vis[pairV[v]] && dfs(pairV[v])){
            pairV[v] = u; pairU[u] = v;
            return true;
        }
    }
    return false;
}

//O(E*V)
int hungarian()
{
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    for (int u = 1; u <= m; u++){
        memset(&vis, false, sizeof vis);
        if (pairU[u]==0 && dfs(u))
            result++;
    }
    return result;
}

int N, M, ctimes, cplus;
char board[MAXN][MAXN];
bool plusboard[MAXN][MAXN], timesboard[MAXN][MAXN];
set<int> row, col, pdiag, sdiag;

void timessolve(){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if (!row.count(i) && !col.count(j)){
				row.insert(i);
				col.insert(j);
				timesboard[i][j] = true;
				ctimes++;
			}
		}
	}
}

void plussolve(){
	map<int, int> pdiag2node, sdiag2node;
	int node2pdiag[MAXN], node2sdiag[MAXN];
	n = m = 0;
	for(int u=0; u<MAXN; u++) adjU[u].clear();
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if (!pdiag.count(i+j) && !sdiag.count(i-j)){
				if (!pdiag2node.count(i+j)){
					pdiag2node[i+j] = ++m;
					node2pdiag[m] = i+j;
				}
				int u = pdiag2node[i+j];
				if (!sdiag2node.count(i-j)){
					sdiag2node[i-j] = ++n;
					node2sdiag[n] = i-j;
				}
				int v = sdiag2node[i-j];
				adjU[u].push_back(v);
			}
		}
	}
	hungarian();
	for(int u=1, v; u<=m; u++){
		v = pairU[u];
		if (v == 0) continue;
		int pd = node2pdiag[u];
		int sd = node2sdiag[v];
		int i = (pd+sd)/2;
		int j = (pd-sd)/2;
		plusboard[i][j] = true;
		cplus++;
	}
}

struct change{
	char c; int i; int j;
	change(char _c, int _i, int _j) : c(_c), i(_i), j(_j) {}
};
vector<change> changes;

void makechanges()
{
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if (timesboard[i][j] && plusboard[i][j]){
				if (board[i][j] != 'o') changes.push_back(change('o', i, j));
			}
			else if (timesboard[i][j]){
				if (board[i][j] != 'x') changes.push_back(change('x', i, j));
			}
			else if (plusboard[i][j]){
				if (board[i][j] != '+') changes.push_back(change('+', i, j));
			}
		}
	}
}

int main()
{
	int T, i, j;
	char c;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++){
		memset(&board, '.', sizeof board);
		memset(&timesboard, false, sizeof timesboard);
		memset(&plusboard, false, sizeof plusboard);
		scanf("%d %d", &N, &M);
		cplus = ctimes = 0;
		while (M--){
			scanf(" %c %d %d", &c, &i, &j);
			i--; j--;
			board[i][j] = c;
			if (c == 'o' || c == 'x'){
				timesboard[i][j] = true;
				row.insert(i);
				col.insert(j);
				ctimes++;
			}
			if (c == 'o' || c == '+'){
				plusboard[i][j] = true;
				pdiag.insert(i+j);
				sdiag.insert(i-j);
				cplus++;
			}
		}
		plussolve();
		timessolve();
		makechanges();
		printf("Case #%d: %d %d\n", caseNo, ctimes+cplus, changes.size());
		for(i=0; i<(int)changes.size(); i++){
			printf("%c %d %d\n", changes[i].c, changes[i].i+1, changes[i].j+1);
		}
		row.clear(); col.clear(); pdiag.clear(); sdiag.clear();
		changes.clear();
	}
	return 0;
}