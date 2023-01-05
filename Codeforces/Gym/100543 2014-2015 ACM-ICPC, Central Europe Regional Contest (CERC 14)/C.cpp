#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef vector<int> vi;

int n;

bool check(int m) {
	if (m == 1 || n % m != 0) return false;;
	if ((n/m + 1 - m) % 2 != 0) return false;
	int a1 = (n/m - (m-1))/2;
	if (a1 <= 0) return false;
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d", &n);
		if (n == (n&-n)) {
			printf("IMPOSSIBLE\n");
			continue;
		}
		n *= 2;
		vector<int> di;
		int lo = int((-1.0-sqrt(1 + 4.0*n))/2.0);
		if (lo < 1) lo = 1;
		int hi = 1 + int((-1.0+sqrt(1 + 4.0*n))/2.0);
		int f = INF;
		for(int m = lo; m <= hi; m++) {
			if (check(m)) {
				f = min(f, m);
				break;
			}
		}
		if (f == INF) printf("IMPOSSIBLE\n");
		else {
			int a1 = (n/f - (f-1))/2;
			printf("%d = %d", n/2, a1);
			FOR(i, f-1) printf(" + %d", ++a1);
			printf("\n");
		}
	}
	return 0;
}