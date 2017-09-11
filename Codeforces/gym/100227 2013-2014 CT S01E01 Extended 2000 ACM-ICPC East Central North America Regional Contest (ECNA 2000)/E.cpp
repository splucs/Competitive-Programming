#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

int board[MAXN][MAXN], pos[MAXN][MAXN], N;
int x[MAXN], y[MAXN];

int tr(int u) {
	int i = x[u], j = y[u], di;
	di = (board[i][j] > 0 ? 1:-1);
	if (i+di >= 0 && i+di < 8 && j+1 < 8) return pos[i+di][j+1];
	return 5;
}

int tl(int u) {
	int i = x[u], j = y[u], di;
	di = (board[i][j] > 0 ? 1:-1);
	if (i+di >= 0 && i+di < 8 && j-1 >= 0) return pos[i+di][j-1];
	return 5;
}

int br(int u) {
	int i = x[u], j = y[u], di;
	di = (board[i][j] > 0 ? -1:1);
	if (i+di >= 0 && i+di < 8 && j+1 < 8) return pos[i+di][j+1];
	return 5;
}

int bl(int u) {
	int i = x[u], j = y[u], di;
	di = (board[i][j] > 0 ? -1:1);
	if (i+di >= 0 && i+di < 8 && j-1 >= 0) return pos[i+di][j-1];
	return 5;
}

int value(int u) {
	return board[x[u]][y[u]];
}

bool checksingle(int u, int v) {
	if (value[])
	if (abs(value(u)) == 2 && (br(u) == v || bl(u) == v)) return true;
	return tr(u) == v || tl(u) == v;
}

bool checkdouble(int u, int v) {
	if (abs(value(u)) == 2) {
		if (x[u])
	}
}

int main() {
	for(int i=0; i<8; i++)
}