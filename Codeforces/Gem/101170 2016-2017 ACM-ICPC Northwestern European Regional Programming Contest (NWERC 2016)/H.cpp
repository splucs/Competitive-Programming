#include <bits/stdc++.h>
using namespace std;
#define MAXN 69

typedef long long ll;

ll rev_g(ll g) {
	ll n=0;
	for(; g; g>>=1) {
		n ^= g;
	}
	return n;
}

char s1[MAXN], s2[MAXN];
int N;

ll getnum(char * s) {
	ll n = 0, p=1;
	for(int i = N-1; i>=0; i--) {
		n += (s[i]-'0')*p;
		p <<= 1;
	}
	return n;
}

int main() {
	scanf("%d %s %s", &N, s1, s2);
	ll n1 = getnum(s1);
	ll n2 = getnum(s2);
	ll r1 = rev_g(n1);
	ll r2 = rev_g(n2);
	printf("%I64d\n", abs(r1-r2)-1);
	return 0;
}