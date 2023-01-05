#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define EPS 1e-9
#define FOR(x, n) for(int x = 0; x < n; x++)

long long sol[35];

int main() {
	int n;
	scanf("%d", &n);
	sol[0] = 1;
	
	long long acum = 1;
	for (int i = 1; i <= 30; i++) {
		acum *= 2;
		sol[i] = sol[i-1] + acum;
	}
	
	printf("%I64d\n", sol[n]);
}