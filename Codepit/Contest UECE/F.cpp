#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

typedef long long ll;
int xconv[MAXN], yconv[MAXN], xinv[MAXN], yinv[MAXN];
set<int> sx, sy;
int bx[30], by[30], cx, cy;
int board[30][30];

ll botright(ll p, int x, int y, int mx, int my) {
	ll ans = 0, d;
	for(int yt = y+1; yt < my; yt++) {
		d = 0;
		for(int xt = x+1; xt <= mx; xt++) {
			if (board[xt][yt] || xt == mx) {
				mx = xt;
				d += p*(yinv[yt+1] - yinv[yt])*(xinv[mx] - xinv[x+1]);
				break;
			}
		}
		ans += d;
	}
	return ans;
}

int main() {
	int T, N, M, K;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d %d", &N, &M, &K);
		sx.clear();
		sy.clear();
		for(int i=1; i<=K; i++) {
			scanf("%d %d", &bx[i], &by[i]);
			sx.insert(bx[i]);
			sy.insert(by[i]);
		}
		sx.insert(1);
		sy.insert(1);
		cx = 0;
		for(set<int>::iterator it = sx.begin(); it != sx.end(); it++) {
			xconv[*it] = ++cx; xinv[cx] = *it;
		}
		cy = 0;
		for(set<int>::iterator it = sy.begin(); it != sy.end(); it++) {
			yconv[*it] = ++cy; yinv[cy] = *it;
		}
		memset(&board, 0, sizeof board);
		for(int i=1; i<=K; i++) {
			board[xconv[bx[i]]][yconv[by[i]]] = 1;
		}
		ll ans = 0, d;
		for(int x=0; x<=cx+1; x++) board[x][0] = board[x][cy+1] = 1;
		for(int y=0; y<=cy+1; y++) board[0][y] = board[cx+1][y] = 1;
		xinv[0] = 0; xinv[cx+1] = N+1;
		yinv[0] = 0; yinv[cy+1] = M+1;
		for(int x=1; x<=cx; x++) {
			for(int y=1; y<=cy; y++) {
				
				//top-left point
				int mx = x+1, my = y+1;
				ll dx = xinv[x+1] - xinv[x];
				ll dy = yinv[y+1] - yinv[y];
				while(board[x][my] == 0) my++;
				while(board[mx][y] == 0) mx++;
				d = 0;
				if (board[x][y] == 0) {
					d += dx*(yinv[my] - yinv[y+1]);
					d += dy*(xinv[mx] - xinv[x+1]);
					d += dx*dy;
					d += botright(1, x, y, mx, my);
					ans += d;
				}
				
				//top strip
				d = 0;
				d += (dy - 1)*(yinv[my] - yinv[y+1])*dx;
				d += (dy - 1)*dy*(xinv[cx+1] - xinv[x])/2ll;
				d += botright(dy - 1, x, y, cx+1, my);
				ans += d;
				
				//left strip
				d = 0;
				d += (dx - 1)*(xinv[mx] - xinv[x+1])*dy;
				d += (dx - 1)*dx*(yinv[cy+1] - yinv[y])/2ll;
				d += botright(dx - 1, x, y, mx, cy+1);
				ans += d;
				
				//bot-right square
				d = 0;
				d += (dx - 1)*dx*(dy - 1)*dy/4ll;
				d += (dx - 1)*dx*(dy - 1)*(yinv[cy+1] - yinv[y+1])/2ll;
				d += (dy - 1)*dy*(dx - 1)*(xinv[cx+1] - xinv[x+1])/2ll;
				d += botright((dx-1)*(dy-1), x, y, cx+1, cy+1);
				ans += d;
			}
		}
		printf("%I64d\n", ans);
	}
	return 0;
}