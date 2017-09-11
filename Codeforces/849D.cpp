#include <bits/stdc++.h>
using namespace std;
#define MAXN 200019
#define OFFSET 100009

int N, W, H;
typedef pair<int, int> ii;
vector<ii> hor[MAXN], ver[MAXN];
ii ans[MAXN];

int main() {
	scanf("%d %d %d", &N, &W, &H);
	int g, p, t;
	for(int i=1; i<=N; i++) {
		scanf("%d %d %d", &g, &p, &t);
		if (g == 1) ver[t-p+OFFSET].push_back(ii(p, i));
		else hor[t-p+OFFSET].push_back(ii(p, i));
	}
	for(p=0; p<MAXN; p++) {
		sort(ver[p].begin(), ver[p].end());
		sort(hor[p].begin(), hor[p].end());
		vector<ii> cur;
		for(int i=0; i<(int)ver[p].size(); i++) {
			cur.push_back(ii(ver[p][i].first, H));
		}
		for(int i=((int)hor[p].size())-1; i>=0; i--) {
			cur.push_back(ii(W, hor[p][i].first));
		}
		int k = 0;
		for(int i=((int)hor[p].size())-1; i>=0; i--) {
			ans[hor[p][i].second] = cur[k++];
		}
		for(int i=0; i<(int)ver[p].size(); i++) {
			ans[ver[p][i].second] = cur[k++];
		}
	}
	for(int i=1; i<=N; i++) printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}