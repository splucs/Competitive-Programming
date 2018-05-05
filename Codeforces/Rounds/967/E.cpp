#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int greatestbit(ll num) {
	int cnt = 0;
	int ans = -1;
	while(num) {
		if (num & 1LL) ans = cnt;
		num >>= 1;
		cnt++;
	}
	return ans;
}

int n;
vector<ll> bit[100];
ll b[MAXN];

int main() {
	scanf("%d", &n);
	FOR(i, n) {
		scanf("%I64d", &b[i]);
		bit[greatestbit(b[i])].pb(b[i]);
	}

	bool ok = true;
	vector<ll> ans;
	for(int gb = 61; gb >= 0; gb--) {
		int y = 0;
		for(ll num : ans) {
			if (num & (1LL << gb)) y++;
		}
		int x = bit[gb].size();
		if (x > y+1) {
			ok = false;
			break;
		}
		int j = 0;
		vector<ll> cur;
		for(ll num : bit[gb]) {
			cur.pb(num);
			while(j < (int)ans.size() && !(ans[j] & (1LL << gb))) cur.pb(ans[j++]);
			if(j < (int)ans.size()) cur.pb(ans[j++]);
		}
		while(j < (int)ans.size()) {
			cur.pb(ans[j++]);
		}
		ans = cur;
	}
	
	if (ok) {
		printf("Yes\n");
		FOR(i, n) {
			printf("%I64d ", ans[i]);
		}
		printf("\n");
	}
	else printf("No\n");

	return 0;
}