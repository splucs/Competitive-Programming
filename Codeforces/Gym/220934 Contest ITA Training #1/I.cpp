#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

int W, H, o1, o2;
vector<int> ans;
bool visx[MAXN], visy[MAXN];

bool intersect(int i, int j, int *x1, int *x2) {
	return !(x1[i] >= x2[j] || x1[j] >= x2[i]);
}

bool bt(int u, bool *vis, int *x1, int *x2, vector<int> *rec) {
	if (vis[u]) return false;
	vis[u] = true;
	if (o1 != u && intersect(o1, u, x1, x2)) return false;
	if (o2 != u && intersect(o2, u, x1, x2)) return false;
	if (x1[u] == 0) {
		ans.push_back(u);
		return true;
	}
	for(int j = 0; j < (int)rec[x1[u]].size(); j++) {
		int v = rec[x1[u]][j];
		if (bt(v, vis, x1, x2, rec)) {
			ans.push_back(u);
			return true;
		}
	}
	return false;
}

int x1[MAXN], x2[MAXN], y1[MAXN], y2[MAXN];
vector<int> recx[MAXN], recy[MAXN];

bool compx(int i, int j) {
	return x1[i] < x2[j];
}

bool compy(int i, int j) {
	return y1[i] < y2[j];
}

int main() {
	int N;
	scanf("%d %d %d", &W, &H, &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
		recx[x2[i]].push_back(i);
		recy[y2[i]].push_back(i);
	}
	scanf("%d %d", &o1, &o2);

	bool ok = false;
	for(int i = 0; i < (int)recx[W].size() && !ok; i++) {
		int u = recx[W][i];
		ok = ok || bt(u, visx, x1, x2, recx);
	}
	for(int i = 0; i < (int)recy[H].size() && !ok; i++) {
		int u = recy[H][i];
		ok = ok || bt(u, visy, y1, y2, recy);
	}

	if (ok) {
		printf("%u\n", ans.size());
		for(int i = 0; i < (int)ans.size(); i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	else printf("-1\n");

	return 0;
}