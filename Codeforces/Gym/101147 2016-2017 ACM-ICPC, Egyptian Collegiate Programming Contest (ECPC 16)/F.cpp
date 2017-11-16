#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define OFFSET 100004

typedef long long ll;
typedef pair<ll, ll> ii;
vector<ii> pdiag[MAXN], sdiag[MAXN];
int ans[MAXN];

bool comp(ii a, ii b) {
	if (a.second != b.second) return a.second < b.second;
	return a < b;
}

int process(vector<ii> & v) {
	if (v.empty()) return 0;
	sort(v.begin(), v.end(), comp);
	int ans = 1, last = 0;
	for(int i=1; i<(int)v.size(); i++) {
		if (v[i].first > v[last].second) {
			last = i;
			ans++;
		}
	}
	return ans;
}

int main() {
	freopen("bishops.in", "r", stdin);
	
	int T, N, M, x, y;
	scanf("%d", &T);
	ll p, C;
	while(T-->0) {
		for(int i=0; i<MAXN; i++) {
			pdiag[i].clear(); sdiag[i].clear();
		}
		scanf("%d %d %I64d", &N, &M, &C);
		for(int i=0; i<M; i++) {
			scanf("%d %d %I64d", &x, &y, &p);
			pdiag[x+y].push_back(ii(x - p*p + 1, x + p*p - 1 + C));
			sdiag[x-y+OFFSET].push_back(ii(x - p*p + 1, x + p*p - 1 + C));
		}
		int ans = 1;
		for(int i=0; i<MAXN; i++) {
			ans = max(ans, process(pdiag[i]));
			ans = max(ans, process(sdiag[i]));
		}
		printf("%d\n", ans);
	}
	
	fclose(stdin); 
	return 0;
}