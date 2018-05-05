#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define push_back pb
#define INF (1LL<<60)
typedef long long ll;
typedef pair<int, int> ii;

int main() {
	int n;
	scanf("%d", &n);
	if (n <= 5) printf("-1\n");
	else {
		printf("1 2\n");
		FOR(i, n-2) {
			if (i % 2 != 0) printf("1 %d\n", i+3);
			else printf("2 %d\n", i+3);
		}
	}
	FOR(i, n-1) {
		printf("%d %d\n", i+1, i+2);
	}
	return 0;
}