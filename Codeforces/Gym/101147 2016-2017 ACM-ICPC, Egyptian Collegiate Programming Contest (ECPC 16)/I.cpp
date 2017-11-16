#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define MAXN 200009

typedef long long ll;
typedef pair<ll, ll> ii;

int main() {
	freopen("walk.in", "r", stdin);
	
	int T, N;
	ll x, y, M, R;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %I64d", &N, &M);
		map<double, ii> pos;
		for(int i=0; i<N; i++) {
			scanf("%I64d %I64d %I64d", &x, &y, &R);
			if (abs(R - M) < abs(y) || R > M) {
				continue;
			}
			double dx = sqrt((R - M)*1.0*(R - M) - y*1.0*y);
			if (!pos.count(x-dx)) pos[x-dx] = ii(0, 0);
			if (!pos.count(x+dx)) pos[x+dx] = ii(0, 0);
			pos[x-dx].first += R;
			pos[x+dx].second += R;
		}
		ll cur = 0, ans = 0;
		for(map<double, ii>::iterator it = pos.begin(); it != pos.end(); it++) {
			cur += it->second.first;
			ans = max(ans, cur);
			cur -= it->second.second;
		}
		printf("%I64d\n", ans);
	}
	
	fclose(stdin);
	return 0;
}