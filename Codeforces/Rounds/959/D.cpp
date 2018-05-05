#include <bits/stdc++.h>
using namespace std;
#define MAXN 5000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define INF (1LL<<60)
typedef long long ll;
typedef pair<int, int> ii;

bitset<MAXN> pres, bs;

vector<int> p;
void sieve() {
	bs.set();
	bs[1] = 0;
	for(int i = 2; i < MAXN; i++) {
		if (bs[i]) {
			p.pb(i);
			for(int j = 2*i; j < MAXN; j += i) {
				bs[j] = 0;
			}
		}
	}
}

void cutmultiples(int n) {
	if (!pres[n]) return;
	for(int i = n; i < MAXN; i += n) {
		pres[i] = 0;
	}
}

void process(int n) {
	for(int i = 0; i < int(p.size()) && p[i]*1ll*p[i] <= n && n > 1; i++) {
		if (n % p[i] == 0) {
			cutmultiples(p[i]);
			while(n % p[i] == 0) n /= p[i];
		}
	}
	if (n > 1) cutmultiples(n);
}

int nxt[MAXN];
int find(int i) {
	if (pres[i]) {
		process(i);
		return i;
	}
	return nxt[i] = find(nxt[i]);
}

int main() {
	sieve();
	pres.set();
	int n, x;
	scanf("%d", &n);
	FOR(i, MAXN) nxt[i] = i+1;
	bool great = false;
	FOR(i, n) {
		scanf("%d", &x);
		int y = find(great ? 2 : x);
		if (x != y) great = true;
		printf("%d ", y);
	}
	printf("\n");
	return 0;
}