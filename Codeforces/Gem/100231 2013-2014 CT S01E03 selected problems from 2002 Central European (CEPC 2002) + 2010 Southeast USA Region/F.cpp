#include <bits/stdc++.h>
using namespace std;
#define MAXN 17000009

bool freeslot(int x0, int y0, int* x, int* y) {
	if (x0 < 0 || x0 >= 8 || y0 < 0 || y0 >= 8) return false;
	for(int i=0; i<4; i++) {
		if (x[i] == x0 && y[i] == y0) return false;
	}
	return true;
}

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void mask2xy(int mask, int* x, int* y) {
	for(int i=0; i<4; i++) {
		x[i] = mask%8;
		mask >>= 3;
		y[i] = mask%8;
		mask >>= 3;
	}
}

int xy2mask(int* x, int* y) {
	int p = 1, mask = 0;
	for(int i=0; i<4; i++) {
		mask |= (x[i]*p);
		p <<= 3;
		mask |= (y[i]*p);
		p <<= 3;
	}
	return mask;
}

int fixmask(int mask) {
	int r[4], p = 1;
	for(int i=0; i<4; i++) {
		r[i] = mask%64;
		mask >>= 6;
	}
	sort(r, r+4);
	mask = 0;
	for(int i=0; i<4; i++) {
		mask |= (r[i]*p);
		p <<= 6;
	}
	return mask;
}

int startstate, endstate;
bool vis[MAXN][9];

bool search(const int rawmask, const int h) {
	const int mask = fixmask(rawmask);
	if (h > 8) return false;
	if (vis[mask][h]) return false;
	vis[mask][h] = true;
	if (mask == endstate) return true;
	int x[4], y[4], nmask;
	mask2xy(mask, x, y);
	for(int i=0; i<4; i++) {
		for(int d=0; d<4; d++) {
			int nx = x[i] + dx[d];
			int ny = y[i] + dy[d];
			if (!freeslot(nx, ny, x, y)) {
				nx += dx[d];
				ny += dy[d];
			}
			if (!freeslot(nx, ny, x, y)) continue;
			swap(x[i], nx);
			swap(y[i], ny);
			nmask = xy2mask(x, y);
			swap(x[i], nx);
			swap(y[i], ny);
			if (search(nmask, h+1)) return true;
		}
	}
	return false;
}

int main() {
	
	int x[4], y[4];
	for(int i=0; i<4; i++) {
		scanf("%d %d", &x[i], &y[i]);
		x[i]--;
		y[i]--;
	}
	startstate = fixmask(xy2mask(x, y));
	for(int i=0; i<4; i++) {
		scanf("%d %d", &x[i], &y[i]);
		x[i]--;
		y[i]--;
	}
	endstate = fixmask(xy2mask(x, y));
	
	//memset(&dp, 0, sizeof dp);
	
	if (search(startstate, 0)) printf("YES\n");
	else printf("NO\n");
	
	return 0;
}