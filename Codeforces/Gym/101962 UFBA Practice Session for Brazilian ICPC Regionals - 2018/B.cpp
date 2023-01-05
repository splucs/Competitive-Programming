#include <bits/stdc++.h>
#define MAXN 2009
#define MAXM 50009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int n, m;
char s[MAXN];

bool test(int st, char t[]) {
	char reduce[2] = {0, 0};
	FOR(i, m) {
		if (i+st >= n) return false;
		if (reduce[t[i]-'0']) {
			if (reduce[t[i]-'0'] != s[i+st]) return false;
		}
		else {
			reduce[t[i]-'0'] = s[i+st];
		}
	}
	return true;
}

char t1[MAXN], t2[MAXN];

int main() {
	scanf(" %s %s", s, t1);
	n = strlen(s);
	m = strlen(t1);
	strcpy(t2, t1);
	reverse(t2, t2+m);
	int ans = 0;
	FOR(i, n) {
		if (test(i, t1) || test(i, t2)) ans++;
	}
	printf("%d\n", ans);
	return 0;
}