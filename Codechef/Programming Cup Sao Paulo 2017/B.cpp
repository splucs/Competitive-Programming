#include <bits/stdc++.h>
using namespace std;

int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[8] = {-2, 2, -2, 2, -1, 1, -1, 1};
int dist[9][9];

bool valid(int x, int y) {
	return x >= 1 && y <= 8 && y >= 1 && y <= 8;
}

int main() {
	int Q, x1, x2, y1, y2;
	scanf("%d", &Q);
	while(Q --> 0) {
		char c1, c2;
		scanf(" %c%d %c%d", &c1, &y1, &c2, &y2);
		x1 = c1 - 'a' + 1;
		x2 = c2 - 'a' + 1;
		memset(&dist, -1, sizeof dist);
		queue<int> qx;
		queue<int> qy;
		qx.push(x1);
		qy.push(y1);
		dist[x1][y1] = 0;
		while(!qx.empty()) {
			int x = qx.front(); qx.pop();
			int y = qy.front(); qy.pop();
			if (x == x2 && y == y2) break;
			for(int k = 0; k < 8; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (!valid(nx, ny)) continue;
				if (dist[nx][ny] == -1) {
					dist[nx][ny] = 1 + dist[x][y];
					qx.push(nx);
					qy.push(ny);
				}
			}
		}
		printf("%d\n", dist[x2][y2]);
	}
	return 0;
}