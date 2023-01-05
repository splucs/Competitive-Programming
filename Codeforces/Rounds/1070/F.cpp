#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef long long ll;

int read() {
	char c1, c2;
	scanf(" %c %c", &c1, &c2);
	int ans = 0;
	if (c1 == '1') ans += 2;
	if (c2 == '1') ans += 1;
	return ans;
}

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		vector<int> v[4];
		FOR(i, n) {
			int k = read();
			int x;
			scanf("%d", &x);
			v[k].pb(x);
		}
		int m = 0;
		ll ans = 0;
		int a = 0, b = 0;
		sort(all(v[1]));
		while(!v[3].empty()) {
			m++; a++; b++;
			ans += v[3].back();
			v[3].pop_back();
		}
		sort(all(v[2]));
		sort(all(v[3]));
		while(!v[1].empty() && !v[2].empty()) {
			m += 2; a++; b++;
			ans += v[1].back() + v[2].back();
			v[1].pop_back();
			v[2].pop_back();
		}
		v[0].insert(v[0].end(), all(v[1]));
		v[0].insert(v[0].end(), all(v[2]));
		sort(all(v[0]));
		while(!v[0].empty() && 2*a >= m+1 && 2*b >= m+1) {
			m++;
			ans += v[0].back();
			v[0].pop_back();
		}
		printf("%lld\n", ans);
	}
	return 0;
}