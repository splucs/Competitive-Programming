#include <bits/stdc++.h>
#define MAXN 100009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
using namespace std;

char s[MAXN];
int cnt[MAXN];

int main() {
	while(scanf(" %s", s) != EOF) {
		int n = strlen(s);
		int prv = 0;
		bool ok = true;
		REP(i, n) {
			s[i] -= '0';
			cnt[i] = s[i]^prv;
			prv ^= s[i];
		}
		int cur = 0;
		FOR(i, n) {
			if (cnt[i] != cur) ok = false;
			cur ^= s[i];
		}
		puts(ok ? "YES" : "NO");
	}
	return 0;
}