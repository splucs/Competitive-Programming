#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXLOGN 25
#define INF (1LL<<60)

typedef long long ll;
typedef pair<ll, int> ii;
int N;
ll S, dt;

struct contest {
	int d, id;
	ii et, mmt;
	ll l, h, hef;
	contest(int _d, ll _l, ll _h, int _id) : d(_d), l(_l), h(_h), id(_id) {}
	bool operator < (contest & other) {
		return hef < other.hef;
	}
};

vector<contest> adj[MAXN];
int back[MAXN];
ii Mhef[MAXN];

int main() {
	ll h, l;
	scanf("%d %I64d %I64d", &N, &S, &dt);
	for(int i=1, d; i<=N; i++) {
		scanf("%d %I64d %I64d", &d, &l, &h);
		adj[d].push_back(contest(d, l, h, i));
	}
	Mhef[0] = ii(S, -1);
	for(int i=1; i<MAXN; i++) {
		for(int it = 0; it < (int)adj[i].size(); it++) {
			contest & c = adj[i][it];
			ii mint = ii(INF, -1);
			if (i > MAXLOGN && Mhef[i-MAXLOGN].first >= c.l) {
				mint = ii(0, Mhef[i-MAXLOGN].second);
			}
			if (S >= c.l) {
				mint = ii(0, -1);
			}
			for(int j=i-1; j>i-MAXLOGN && j > 0; j--) {
				int hi = adj[j].size();
				int lo = -1;
				while(hi > lo+1) {
					int mid = (hi+lo) / 2;
					if (adj[j][mid].hef >= c.l) hi = mid;
					else lo = mid;
				}
				if (hi < (int)adj[j].size()) {
					mint = min(mint, ii(adj[j][hi].mmt.first >> (i-j-1), adj[j][hi].mmt.second));
				}
			}
			c.et = ii(mint.first + dt, mint.second);
			c.hef = c.h - mint.first;
			back[c.id] = c.et.second;
		}
		if (!adj[i].empty()) {
			sort(adj[i].begin(), adj[i].end());
			adj[i].back().mmt = ii(adj[i].back().et.first, adj[i].back().id);
		}
		for(int it = ((int)adj[i].size())-2; it>=0; it--) {
			adj[i][it].mmt = min(ii(adj[i][it].et.first, adj[i][it].id), adj[i][it+1].mmt);
		}
		Mhef[i] = adj[i].empty() ? Mhef[i-1] : max(Mhef[i-1], ii(adj[i].back().hef, adj[i].back().id));
	}
	int c = Mhef[MAXN-1].second;
	stack<int> ans;
	while(c != -1) {
		ans.push(c);
		c = back[c];
	}
	printf("%I64d %u\n", Mhef[MAXN-1].first, ans.size());
	while(!ans.empty()) {
		printf("%d ", ans.top());
		ans.pop();
	}
	printf("\n");
	return 0;
}