#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int main() {
	int n;
	while(scanf(" 1 / %d", &n) != EOF) {
		n *= n;
		int ans = 1;
		for(int i = 1; i*i <= n; i++) {
			if (n%i != 0) continue;
			ans++;
			if (i != n/i) ans++;
		}
		ans /= 2;
		printf("%d\n", ans);
	}
	return 0;
}