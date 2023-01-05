#include <bits/stdc++.h>
using namespace std;

char board[8][8];

int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dist[8][8];

inline bool valid(int i, int j) {
	if (i < 0 || j < 0 || i >= 8 || j >= 8) return false;
	if (board[i][j] == 'X') return false;
	return true;
}

int main() {
	int si, sj, ti, tj;
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			scanf(" %c", &board[i][j]);
			dist[i][j] = 70;
			if (board[i][j] == 'I') {
				si = i;
				sj = j;
			}
			if (board[i][j] == 'F') {
				ti = i;
				tj = j;
			}
		}
	}
	queue<int> qi, qj;
	dist[si][sj] = 0;
	qi.push(si);
	qj.push(sj);
	while(!qi.empty()) {
		int i = qi.front();
		int j = qj.front();
		qi.pop(); qj.pop();
		for(int k=0; k<8; k++) {
			int ni = i+dx[k];
			int nj = j+dy[k];
			if (!valid(ni, nj)) continue;
			if (dist[ni][nj] > 1 + dist[i][j]) {
				dist[ni][nj] = 1 + dist[i][j];
				qi.push(ni);
				qj.push(nj);
			}
		}
	}
	if (dist[ti][tj] == 70) printf("Impossivel ir de I a F\n");
	else printf("Numero minino de movimentos: %d\n", dist[ti][tj]);
	return 0;
}