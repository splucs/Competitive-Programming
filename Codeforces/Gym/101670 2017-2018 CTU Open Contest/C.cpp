#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
typedef long long ll;

int main() {
	int n;
	char op;
	while(scanf("%d %c", &n, &op) != EOF) {
		if (op == 'K') {
			printf("%d\n", n < 2 ? 1 : 4);
		}
		if (op == 'N') {
			printf("%d\n", n <= 2 ? 1 : 2);
		}
		if (op == 'R' || op == 'B') {
			printf("%d\n", n);
		}
	}
	return 0;
}