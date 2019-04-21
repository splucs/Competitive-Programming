#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009
#define MAXLOGN 20
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

int vsum[MAXN];
char s[MAXN];

bool isVowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int sum(int i, int j) {
	int ans = vsum[j];
	if (i > 0) ans -= vsum[i-1];
	return ans;
}

ll solve(int l, int r, int d) {
	if (r == l || sum(l, r) == 0) return 1;
	ll ans = 0;
	if (d == 0) {
		if (!isVowel(s[l])) return 0;
		ans = solve(l+1, r, 1);
		if (!isVowel(s[r])) ans += solve(l, r-1, 0);
	}
	else {
		if (!isVowel(s[r])) return 0;
		ans = solve(l, r-1, 0);
		if (!isVowel(s[l])) ans += solve(l+1, r, 1);
	}
	return ans;
}

int main() {
	scanf(" %s", s);
	int n = strlen(s);
	int acum = 0;
	FOR(i, n) {
		acum += isVowel(s[i]);
		vsum[i] = acum;
	}
	printf("%lld\n", solve(0, n-1, 0));
	return 0;
}