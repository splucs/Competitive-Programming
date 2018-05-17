#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 200009
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=(n)-1; (x)>=0; (x)--)
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

char s[MAXN];
int n, cnt[10];

int match() {
	int ans = 0;
	FOR(i, 10) if (cnt[i] != 0) ans++;
	return ans;
}

int minleft() {
	int ans = INF;
	FOR(i, 10) if (cnt[i] != 0) ans = min(ans, i);
	return ans;
}

bool bt(int i, bool less, bool zero) {
	int nm = match();

	if (i == n) {
		if (!less || zero || nm != 0) return false;
		return true;
	}

	if (i % 2 != 0 && zero) {
		char prv = s[i];
		s[i] = '0';
		return bt(i+1, less || (s[i] < prv), true);
	}

	if (n-i < nm) return false;

	for(char c = less ? '9' : s[i]; c >= '0'; c--) {

		//printf("trying s[%d] = %c\n", i, c);

		if (!zero || c != '0') cnt[c-'0'] ^= 1;

		if (bt(i+1, less || (c < s[i]), zero && (c == '0'))) {
			s[i] = c;
			return true;
		}

		if (!zero || c != '0') cnt[c-'0'] ^= 1;
	}

	return false;
}

int main() {
	int q;
	scanf("%d", &q);
	while(q --> 0) {
		scanf(" %s", s);
		mset(cnt, 0);
		n = strlen(s);
		if (bt(0, false, true)) {
			bool zero = true;
			FOR(i, n) {
				if (s[i] != '0') zero = false;
				if (!zero) printf("%c", s[i]);
			}
			printf("\n");
		}
		else printf("-1\n");
	}
	return 0;
}