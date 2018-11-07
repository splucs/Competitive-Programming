#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
typedef long long ll;

char s[MAXN];

int main() {
	ll res;
	scanf(" %s %lld", s, &res);
	int n = strlen(s);

	ll res1 = 0;
	for(int i = 0; i < n; i += 2) {
		ll cur = s[i] - '0';
		while(i+1 < n && s[i+1] == '*') {
			i += 2;
			cur *= s[i] - '0';
			if (cur > res) cur = res+1;
		}
		res1 += cur;
		if (res1 > res) res1 = res+1;
	}

	ll res2 = s[0]-'0';
	for(int i = 2; i < n; i += 2) {
		if (s[i-1] == '+') res2 += s[i]-'0';
		else res2 *= s[i]-'0';
		if (res2 > res) res2 = res+1;
	}

	if (res == res2 && res == res1) printf("U\n");
	else if (res == res1) printf("M\n");
	else if (res == res2) printf("L\n");
	else printf("I\n");
	return 0;
}