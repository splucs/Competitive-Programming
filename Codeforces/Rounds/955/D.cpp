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
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

char s[MAXN], t[MAXN], buf[MAXN];
int lpos[MAXN], rpos[MAXN], z[MAXN];

void zfunction (char* s, int* z) {
	int n = strlen(s);
	fill(z, z+n, 0);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min(r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
}

int main() {
	int n, m, k;
	scanf("%d %d %d %s %s", &n, &m, &k, s, t);
	bool ok = false;
	int i1, i2;

	strcpy(buf, t);
	strcat(buf, s);
	zfunction(buf, z);
	FOR(i, n+m) {
		if (i >= m && z[i] >= m) {
			ok = true;
			i1 = i-m;
			i2 = i1+k;
			if (i2+k >= n) {
				int d = i2+k - n;
				i2 -= d;
				i1 -= d;
			}
			i1++; i2++;
		}
		z[i] = min(z[i], min(m, k));
	}
	FOR(i, n) lpos[i] = INF;
	lpos[0] = 0;
	for(int i = m; i < n+m; i++) {
		int x = z[i];
		int j = i-m + x - k;
		if (j >= 0 && j+k <= n) lpos[x] = min(lpos[x], j);
	}
	for(int x = n-1; x >= 0; x--) {
		if (lpos[x+1]-1 >= 0 && lpos[x+1] < INF) {
			lpos[x] = min(lpos[x], lpos[x+1]-1);
		}
	}
	//FOR(x, m+1) printf("lpos[%d] = %d\n", x, lpos[x]);

	reverse(s, s+n);
	reverse(t, t+m);
	strcpy(buf, t);
	strcat(buf, s);
	zfunction(buf, z);
	FOR(i, n+m) z[i] = min(z[i], min(m, k));
	FOR(i, n) rpos[i] = -1;
	for(int i = m; i < n+m; i++) {
		int x = z[i];
		int j = n-1-(i-m) - x + 1;
		if (j >= 0 && j+k <= n) rpos[x] = max(rpos[x], j);
	}
	for(int x = min(m, k)-1; x >= 0; x--) {
		if (lpos[x+1]+k < n) {
			rpos[x] = max(rpos[x], rpos[x+1]+1);
		}
	}
	//FOR(x, m+1) printf("rpos[%d] = %d\n", x, rpos[x]);
	FOR(x, k+1) {
		if (ok) break;
		if (lpos[x]+k <= rpos[m-x]) {
			ok = true;
			i1 = lpos[x]+1;
			i2 = rpos[m-x]+1;
		}
	}
	if (ok) printf("Yes\n%d %d\n", i1, i2);
	else printf("No\n");
	return 0;

}