#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define ub upper_bound
#define lb lower_bound
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

char s[MAXN];

int main() {
	int n;
	scanf("%d %s", &n, s);
	int nz = 0, no = 0;
	FOR(i, n) {
		if (s[i] == '0') nz++;
		if (s[i] == '1') no++;
	}
	if (no > 0) printf("1");
	FOR(i, nz) printf("0");
	printf("\n");
	return 0;
}