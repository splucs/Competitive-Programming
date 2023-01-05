#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define INF 1000000000000000000ULL

const char f0[MAXN] = "What are you doing at the end of the world? Are you busy? Will you save us?";
const char f11[MAXN] = "What are you doing while sending \"";
const char f12[MAXN] = "\"? Are you busy? Will you send \"";
const char f13[MAXN] = "\"?";
typedef unsigned long long ll;

int s0, s11, s12, s13, s1, maxi;
ll p2[MAXN], sf[MAXN];

char solve(int n, ll k) {
	//printf("solve(%d,%I64u)\n", n, k);
	if (n == 0) {
		if (k <= s0) return f0[k-1];
		else return '.';
	}
	if (n > maxi && k <= (n-maxi)*1ULL*s11) return f11[(k-1)%s11];
	if (n > maxi) return solve(maxi, k - (n-maxi)*s11);
	if (k <= s11) return f11[k-1];
	if (k <= s11 + sf[n-1]) return solve(n-1, k-s11);
	if (k <= s11 + sf[n-1] + s12) return f12[k-1-s11-sf[n-1]];
	if (k <= s11 + 2*sf[n-1] + s12) return solve(n-1, k - s11 - s12 - sf[n-1]);
	if (k <= s11 + 2*sf[n-1] + s12 + s13) return f13[k-1-s11-s12-2*sf[n-1]];
	return '.';
}

int main() {
	sf[0] = s0 = strlen(f0);
	s11 = strlen(f11);
	s12 = strlen(f12);
	s13 = strlen(f13);
	s1 = s11 + s12 + s13;
	p2[0] = 1;
	maxi = 1;
	for(int i=1; i<MAXN; i++) {
		p2[i] = p2[i-1] << 1;
		sf[i] = p2[i]*(s0+s1) - s1;
		if (sf[i] < INF) maxi++;
		else break;
	}
	int Q;
	scanf("%d", &Q);
	while(Q --> 0) {
		int n;
		ll k;
		scanf("%d %I64u", &n, &k);
		printf("%c", solve(n, k));
	}
	printf("\n");
	return 0;
}