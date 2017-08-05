#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MOD 1000000007LL

char str[MAXN];
int v[MAXN], sum[MAXN], ans[MAXN], N, b;
typedef long long ll;

int main() {
	scanf("%s", str);
	N = strlen(str);
	for(int i=0; i<N; i++) {
		v[i] = str[i] - 'A';
		sum[i] = ((i+1)*v[i]) % MOD;
		if (i > 0) sum[i] = (sum[i] + sum[i-1]) % MOD;
	}
	ll ans = 0, p = 1;
	for(int i=N-1; i>=0; i--) {
		ans = (ans + sum[i]*p) % MOD;
		p = (p*26) % MOD;
	}
	stack<char> s;
	while(ans > 0) {
		s.push(ans%26 + 'A');
		ans /= 26;
	}
	if (s.empty()) printf("A");
	while(!s.empty()) {
		printf("%c", s.top());
		s.pop();
	}
	printf("\n");
	return 0;
}