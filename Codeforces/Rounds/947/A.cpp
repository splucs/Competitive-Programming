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
#define EPS 1e-9

bitset<MAXN> bs;
vector<int> primes[MAXN];

void sieve() {
	bs.set();
	bs[0] = bs[1] = 0;
	for(int i = 2; i < MAXN; i++) {
		if (bs[i]) {
			primes[i].pb(i);
			for(int j = 2*i; j < MAXN; j += i) {
				primes[j].pb(i);
				bs[j] = 0;
			}
		}
	}
}

int main() {
	sieve();
	int X2;
	scanf("%d", &X2);
	int minX1 = INF, minX0 = INF;
	for(int p : primes[X2]) {
		int cur = X2 - p + 1;
		//printf("[%d,%d]->%d->%d\n", cur, X2, p, X2);
		minX1 = min(cur, minX1);
	}
	//printf("%d\n", minX1);
	for(int X1 = minX1; X1 <= X2; X1++) {
		for(int p : primes[X1]) {
			int cur = X1 - p + 1;
			//printf("[%d,%d]->%d->%d\n", cur, X1, p, X1);
			if (cur >= 3) minX0 = min(cur, minX0);
		}
	}
	printf("%d\n", minX0);
	return 0;
}