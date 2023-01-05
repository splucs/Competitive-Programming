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
#define MAXN 100009
#define MAXM 300009
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

void process(char s[], int ta[], int cb[]) {
	int n = strlen(s);
	FOR(i, n) {
		if (s[i] == 'C') s[i] = 'B';
		ta[i] = 0;
		cb[i] = 0;
		if (i > 0) cb[i] += cb[i-1];
		if (s[i] == 'A') {
			ta[i] = 1;
			if (i > 0) ta[i] += ta[i-1];
		}
		if (s[i] == 'B') {
			cb[i]++;
		}
	}
}

char S[MAXN], T[MAXN];
int tas[MAXN], tat[MAXN], cbs[MAXN], cbt[MAXN];

bool check(int i1, int j1, int i2, int j2) {
	int ta1 = min(tas[j1], j1-i1+1);
	int ta2 = min(tat[j2], j2-i2+1);
	int cb1 = cbs[j1] - (i1 > 0 ? cbs[i1-1] : 0);
	int cb2 = cbt[j2] - (i2 > 0 ? cbt[i2-1] : 0);
	
	if (cb1 == cb2) {
		if (ta1 < ta2 || (ta1 - ta2) % 3 != 0) return false;
		return true;
	}
	else if (cb1 > cb2) return false;
	else {
		if ((cb2 - cb1) % 2 != 0) return false;
		if (ta1 > ta2) return true;
		if (ta1 == ta2) return cb1 != 0;
		if (ta1 < ta2) return false;
	}
}

int main() {
	scanf(" %s %s", S, T);
	process(S, tas, cbs);
	process(T, tat, cbt);
	int Q;
	scanf("%d", &Q);
	while(Q --> 0) {
		int i1, j1, i2, j2;
		scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
		i1--; j1--; i2--; j2--;
		if (check(i1, j1, i2, j2)) printf("1");
		else printf("0");
	}
	printf("\n");
	return 0;
}