#include <bits/stdc++.h>
using namespace std;
#define INF 100000009
#define MAXN 1009

int cost[MAXN][MAXN], N;
int lx[MAXN], ly[MAXN], xy[MAXN], yx[MAXN], slack[MAXN], slackx[MAXN];
bool S[MAXN], T[MAXN];
int prv[MAXN];

void init_labels() {
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			lx[x] = max(lx[x], cost[x][y]);
		}
	}
}
void update_labels() {
	int delta = INF;
 	for (int y = 0; y < N; y++) {
 		if (!T[y]) delta = min(delta, slack[y]);
 	}
 	for (int x = 0; x < N; x++) {
 		if (S[x]) lx[x] -= delta;
 	}
	for (int y = 0; y < N; y++) {
 		if (T[y]) ly[y] += delta;
		if (!T[y]) slack[y] -= delta;
 	}
}
void add_to_tree(int x, int prvx)  {
	S[x] = true;
    prv[x] = prvx;
	for (int y = 0; y < N; y++) {
		if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
 			slack[y] = lx[x] + ly[y] - cost[x][y];
 			slackx[y] = x;
 		}
 	}
}
void augment(int max_match) {
	if (max_match == N) return;
	int x, y, root = 0;
 	queue<int> q;
	memset(S, false, sizeof(S));
	memset(T, false, sizeof(T));
	memset(prv, -1, sizeof(prv));
 	for (x = 0; x < N; x++) {
		if (xy[x] == -1) {
			q.push(x); root = x;
			prv[x] = -2; S[x] = true;
 			break;
 		}
 	}
 	for (y = 0; y < N; y++) {
		slack[y] = lx[root] + ly[y] - cost[root][y];
		slackx[y] = root;
	}
	while (true) {
 		while (!q.empty()) {
			x = q.front(); q.pop();
			for (y = 0; y < N; y++) {
				if (cost[x][y] == lx[x] + ly[y] && !T[y]) {
					if (yx[y] == -1) break;
					T[y] = true;
 					q.push(yx[y]);
					add_to_tree(yx[y], x);
				}
			}
 			if (y < N) break;
 		}
 		if (y < N) break;
 		update_labels();
		while (!q.empty()) q.pop(); 
		for (y = 0; y < N; y++) {
			if (!T[y] && slack[y] == 0) {
				if (yx[y] == -1) {
 					x = slackx[y]; break;
 				} else {
 					T[y] = true;
 					if (!S[yx[y]]) {
 						q.push(yx[y]);
						add_to_tree(yx[y], slackx[y]);
					}
 				}
 			}
 		}
 		if (y < N) break;
 	}
 	if (y < N) {
 		for (int cx = x, cy = y, ty; cx != -2; cx = prv[cx], cy = ty) {
 			ty = xy[cx];
			yx[cy] = cx; xy[cx] = cy;
 		}
		augment(max_match+1);
 	}
}
int maximumWeightedMatching() {
	memset(xy, -1, sizeof(xy)); 
	memset(yx, -1, sizeof(yx));
 	init_labels();
 	augment(0);
 	int ret = 0;
	for (int x = 0; x < N; x++) ret += cost[x][xy[x]];
 	return ret;
}

int main() {
	int T, M;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d", &N, &M);
		N = M = max(N, M);
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				cost[i][j] = 0;
			}
		}
		int u, v ,w;
		while(scanf("%d %d %d", &u, &v, &w), u, v, w) {
			cost[u-1][v-1] = w;
		}
		printf("%d\n", maximumWeightedMatching());
	}
	return 0;
}