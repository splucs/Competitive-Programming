#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXLOGN 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> ii;

vector<ii> ans;
int arr[MAXN], inv[MAXN];

void move(int l, int r) {
	assert((r-l) % 2 != 0);
	int m = (r - l + 1) / 2;
	int tmp;
	for(int i = l; i < l+m; i++) {
		tmp = arr[i];
		arr[i] = arr[i+m];
		arr[i+m] = tmp;
		inv[arr[i]] = i;
		inv[arr[i+m]] = i+m;
	}
	ans.pb({l, r});
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n;
		scanf("%d", &n);
		FOR1(i, n) {
			scanf("%d", &arr[i]);
			inv[arr[i]] = i;
		}
		ans.clear();
		FOR1(l, n) {
			while(true) {
				int i = inv[l];
				if (i == l) break;
				int s = i-1;
				int t = i;
				while(s > l && t < n) {
					s--; t++;
				}
				move(s, t);
			}
		}
		printf("%u\n", ans.size());
		for(ii pp : ans) printf("%d %d\n", pp.fi, pp.se);
		//FOR1(i, n) printf("%d ", arr[i]);
	}
	return 0;
}