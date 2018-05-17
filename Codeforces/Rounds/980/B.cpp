#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define MAXM (30*MAXN)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

char city[4][MAXN];
int n, k;

int main() {
	while(scanf("%d %d", &n, &k)!=EOF) {
		memset(&city, '.', sizeof city);
		bool ok = true;
		int c = n/2;
		int i = 1, j = n-2;
		while(k > 1 && j > i) {
			for(int r = 1; r <= 2 && k > 1; r++) {
				if (city[r][i] == '.') {
					city[r][i] = '#';
					k--;
				}
				if (city[r][j] == '.') {
					city[r][j] = '#';
					k--;
				}
			}
			i++;
			j--;
		}
		if (k >= 1) {
			city[2][n/2] = '#';
			k--;
		}
		if (k >= 1) {
			city[1][n/2] = '#';
			k--;
		}
		if (k != 0) ok = false;
		if (ok) {
			printf("YES\n");
			FOR(i, 4) {
				FOR(j, n) printf("%c", city[i][j]);
				printf("\n");
			}
		}
		else printf("NO\n");
	}
	return 0;
}