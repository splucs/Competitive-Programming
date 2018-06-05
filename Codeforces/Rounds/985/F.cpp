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
#define ALFA 27
#define NP 1

class RabinKarp {
	ll m;
	vector<ll> pw, hsh;
public:
	RabinKarp() {}
	RabinKarp(char str[], ll p, ll _m) : m(_m) {
		int n = strlen(str);
		pw.resize(n); hsh.resize(n);
		hsh[0] = str[0]; pw[0] = 1;
		for(int i = 1; i < n; i++) {
			hsh[i] = (hsh[i-1] * p + str[i]) % m;
			pw[i] = (pw[i-1] * p) % m;	
		}
	}
	ll hash(int i, int j) {
		ll ans = hsh[j];
		if (i > 0) ans = (ans - ((hsh[i-1]*1ll*pw[j-i+1])%m) + m) % m;
		return ans;
	}
};

int n, Q;
char s[MAXN], ch[ALFA][MAXN];
RabinKarp rk[ALFA][NP];
ll p[5] = {1000000007LL, 1000000009LL, 1004535809LL, 1092616193LL, 998244353LL};

bool comp(vector<ll> & vx, vector<ll> & vy) {
	FOR(k, 5) if (vx[k] != vy[k]) return vx[k] < vy[k];
	return false;
}

int main() {
	scanf("%d %d %s", &n, &Q, s);
	mset(ch, '0');
	FOR(i, n) {
		ch[s[i]-'a'][i] = '1';
	}
	FOR(j, ALFA) {
		ch[j][n] = 0;
		FOR(k, NP) rk[j][k] = RabinKarp(ch[j], 2, p[k]);
	}
	ll hx[ALFA], hy[ALFA];
	while(Q --> 0) {
		int x, y, len;
		scanf("%d %d %d", &x, &y, &len);
		x--; y--;
		FOR(j, ALFA) {
			ll curx = 0, cury = 0;
			FOR(k, NP) {
				curx = ((curx * p[0]) + rk[j][k].hash(x, x+len-1) ) % p[1];
				cury = ((cury * p[0]) + rk[j][k].hash(y, y+len-1) ) % p[1];
			}
			hx[j] = curx; hy[j] = cury;
		}
		sort(hx, hx+ALFA);
		sort(hy, hy+ALFA);
		bool ok = true;
		FOR(j, ALFA) {
			ok = ok && hx[j] == hy[j];
		}
		if (ok) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
