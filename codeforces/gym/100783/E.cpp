#include <bits/stdc++.h>
using namespace std;
#define MAXN 12

typedef pair<int, int> ii;

char board[MAXN][MAXN];
int R, C, L, nR;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
ii endpos;

struct state{
	ii pos[4];
};

bool operator < (const state & a, const state & b){
	for(int i=0; i<nR; i++){
		if (a.pos[i] != b.pos[i]) return a.pos[i] < b.pos[i];
	}
	return false;
}

ii operator +(ii a, ii b){
	return ii(a.first+b.first, a.second+b.second);
}

map<state, bool> dp[MAXN];

bool valid(ii pos, const state & s){
	int x = pos.first;
	int y = pos.second;
	if (x < 0 || x >= R) return false;
	if (y < 0 || y >= C) return false;
	if (board[x][y] == 'W') return false;
	for(int i=0; i<nR; i++){
		if (s.pos[i] == pos) return false;
	}
	return true;
}

bool DP(int l, const state s){
	if (dp[l].count(s)) return dp[l][s];
	if (l == 0) return dp[l][s] = (endpos == s.pos[0]);
	if (l < 0) return dp[l][s] = false;
	ii curpos;
	bool ans = false;
	state newstate;
	for(int i=0; i<nR; i++){
		for(int j=0; j<4; j++){
			newstate = s;
			curpos = newstate.pos[i];
			while(valid(curpos + ii(dx[j], dy[j]), s)){
				curpos = curpos + ii(dx[j], dy[j]);
			}
			newstate.pos[i] = curpos;
			ans = ans || DP(l-1, newstate);
			if (ans) return dp[l][s] = true;
		}
	}
	return dp[l][s] = false;
}

int main()
{
	char c;
	scanf("%d %d %d %d", &nR, &C, &R, &L);
	state initial;
	int r;
	for(int i=0; i<R; i++){
		for(int j=0; j<C; j++){
			scanf(" %c", &c);
			if (c == '.' || c == 'W') board[i][j] = c;
			else if (c == 'X'){
				endpos = ii(i, j);
				board[i][j] = '.';
			}
			else{
				r = c-'1';
				initial.pos[r] = ii(i, j);
				board[i][j] = '.';
			}
		}
	}
	for(int l=0; l<=L; l++){
		if (DP(l, initial)){
			printf("%d\n", l);
			return 0;
		}
	}
	printf("NO SOLUTION\n");
	return 0;
}