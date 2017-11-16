#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1<<29)

int M, c[MAXN], s[3], x[3];
typedef pair<int, int> ii;
vector<ii> pos;

bool comp(ii a, ii b) {
	return s[a.first] + s[a.second] < s[b.first] + s[b.second];
}

bool check(int v) {
	int y[3];
	y[0] = x[0], y[1] = x[1], y[2] = x[2];
	for(int jt=0; jt<M; jt++) {
		bool ok = false;
		for(int it=0; it<(int)pos.size() && !ok; it++) {
			int i = pos[it].first;
			int j = pos[it].second;
			if (i != j) {
				if (y[i] > 0 && y[j] > 0 && c[jt]*(s[i]+s[j]) >= v) {
					ok = true;
					y[i]--; y[j]--;
				}
			}
			else {
				if (y[i] > 1 && y[j] > 1 && c[jt]*(s[i]+s[j]) >= v) {
					ok = true;
					y[i]--; y[j]--;
				}
			}
		}
		if (!ok) return false;
	}
	return true;
}

int main() {
	scanf("%d %d %d", &x[0], &x[1], &x[2]);
	scanf("%d %d %d", &s[0], &s[1], &s[2]);
	M = (x[0]+x[1]+x[2])/2;
	for(int j=0; j<M; j++) {
		scanf("%d", &c[j]);
	}
	sort(c, c+M);
	
	for(int i=0; i<3; i++)
		for(int j=i; j<3; j++)
			pos.push_back(ii(i, j));
	sort(pos.begin(), pos.end(), comp);
	
	int lo = 0;
	int hi = INF;
	while(hi > lo + 1) {
		int mid = (hi + lo) / 2;
		if (check(mid)) lo = mid;
		else hi = mid;
	}
	
	printf("%d\n", lo);
	
	return 0;
}