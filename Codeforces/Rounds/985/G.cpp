/*
             /\\
              .\\\..
              \\   \\
              \ (o) /
              (/    \
               /\    \
              ///     \
             ///|     |
            ////|     |
           //////    /
           |////    /
          /|////--V/  Stephen Morgana
         //\//|   |
     ___////__\___\__________
    ()_________'___'_________)
        \\\\
          \\\
            \\
*/

#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 200009
#define MAXM 900009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

vector<ull> g[MAXN];
ull n, m;
ull A, B, C;

ull solve0() {
	ull ans = 0;
	for(ull u = 0; u < n; u++) {
		ans += A*u*((n-u-1)*(n-u-2)/2);
		ans += B*u*u*(n-u-1);
		ans += C*u*(u*(u-1)/2);
	}
	//printf("s0 = %llu\n", ans);
	return ans;
}

ull solve1() {
	ull ans = 0;
	for(ull u = 0; u < n; u++) {
		for(ull v : g[u]) {
			if (v < u) continue;
			ans += A*((u-1)*u/2) + B*u*u + C*v*u;
			ans += A*(v-u-1)*u + B*((v+u)*(v-u-1)/2) + C*(v-u-1)*v;
			ans += A*(n-v-1)*u + B*(n-v-1)*v + C*((v+n)*(n-v-1)/2);
		}
	}
	//printf("s1 = %llu\n", ans);
	return ans;
}

ull sum[MAXN];

ull solve2() {
	ull ans = 0;
	for(ull u = 0; u < n; u++) {
		sum[0] = 0;
		ull big = 0;
		FOR(i, g[u].size()) {
			ull v = g[u][i];
			if (v < u) big++;
			sum[i+1] = v + sum[i];
			if (i >= big) {
				ans += A*sum[big] + B*u*big + C*v*big;
				ans += A*(ull(i) - big)*u + B*(sum[i] - sum[big]) + C*(ull(i) - big)*v;
			}
			else {
				ans += A*sum[i] + B*ull(i)*v + C*ull(i)*u;
			}
		}
	}
	//printf("s2 = %llu\n", ans);
	return ans;
}

bool app[MAXN];

ull solve3() {
	ull ans = 0;
	mset(app, false);
	for(ull u = 0; u < n; u++) {
		for(int v : g[u]) app[v] = true;
		for(int v : g[u]) {
			if (v < u) continue;
			for(int w : g[v]) {
				if (w < v || !app[w]) continue;
				ans += A*u + B*v + C*w;
			}
		}
		for(int v : g[u]) app[v] = false;
	}
	//printf("s3 = %llu\n", ans);
	return ans;
}

int main() {
	scanf("%llu %llu %llu %llu %llu", &n, &m, &A, &B, &C);
	FOR(j, m) {
		ull u, v;
		scanf("%llu %llu", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	for(ull u = 0; u < n; u++) sort(all(g[u]));
	ull ans = 0;
	ans += solve0();
	ans -= solve1();
	ans += solve2();
	ans -= solve3();
	printf("%llu\n", ans);
	return 0;
}