#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

bool vis[MAXN][MAXN];
char s[MAXN];
int n, k;

bool bt(int i, int r) {
	if (vis[i][r]) return false;
	vis[i][r] = true;
	if (i == n) {
		return (r == 0);
	}
	if (s[i] == '?') {
		for(char c = (i == 0 ? '1' : '0'); c <= '9'; c++) {
			s[i] = c;
			if (bt(i+1, (10*r + s[i]-'0') % k)) return true;
		}
		s[i] = '?';
	}
	else return bt(i+1, (10*r + s[i]-'0') % k);
}

int main() {
	scanf(" %s %d", s, &k);
	n = strlen(s);
	if (bt(0, 0)) puts(s);
	else puts("*");
	return 0;
}