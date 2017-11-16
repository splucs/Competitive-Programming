#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXK 40

typedef long long ll;

int gcd(int x, int y) {
	if (y == 0) return x;
	else return gcd(y, x%y);
}

struct number {
	int p[MAXK], e[MAXK];
	int sz;
	number() : sz(0) {}
};

bool operator <(number a, number b) {
	if (a.sz != b.sz) return a.sz < b.sz;
	for(int i=0; i<a.sz; i++) {
		if (a.p[i] != b.p[i]) return a.p[i] < b.p[i];
		if (a.e[i] != b.e[i]) return a.e[i] < b.e[i];
	}
	return false;
}

void printnum(const number & n) {
	printf("[1");
	for(int i=0; i<n.sz; i++) printf("*%d^%d", n.p[i], n.e[i]);
	printf("]");
}

bitset<MAXN> pr;
number num[MAXN];
vector<int> divisors[MAXN];
int maxexp[MAXN];

void sieve() {
	pr.set();
	pr[1] = false;
	for(int i=1; i<MAXN; i++) maxexp[i] = 1;
	for(int i=1; i<MAXN; i++) {
		for(int j=i; j<MAXN; j+=i) {
			if (pr[i]) {
				if (j > i) pr[j] = false;
				int cnt = 0;
				int n = j;
				num[j].p[num[j].sz] = i;
				while(n%i == 0) cnt++, n/=i;
				num[j].e[num[j].sz++] = cnt;
				if (cnt == 0) printf("error!\n");
			}
			divisors[j].push_back(i);
		}
		ll p = i;
		int cnt = 1;
		while(p < MAXN && i != 1) {
			maxexp[p] = max(maxexp[p], cnt);
			p *= i; cnt++;
		}
	}
}

void multiply(const number a, const number b, number & c) {
	int & n = c.sz;
	n = 0;
	int i = 0, j = 0;
	while(i < a.sz || j < b.sz) {
		if (i == a.sz || a.p[i] > b.p[j]) {
			c.p[n] = b.p[j];
			c.e[n++] = b.e[j++];
		}
		else if (j == b.sz || a.p[i] < b.p[j]) {
			c.p[n] = a.p[i];
			c.e[n++] = a.e[i++];
		}
		else {
			c.p[n] = a.p[i];
			c.e[n] = a.e[i] + b.e[j];
			i++; j++; n++;
		}
	}
	
}

map<pair<number, int>, ll> dp;

ll solve(const number & n, int layers) {
	if (n.sz == 0) {
		if (layers <= 0) return 1;
		else return 0;
	}
	
	if (dp.count(make_pair(n, layers)))
		return dp[make_pair(n, layers)];
	
	int e = 0;
	for(int i=0; i<n.sz; i++) {
		e = gcd(e, n.e[i]);
	}
	const vector<int> & dive = divisors[e];
	ll ans = 0;
	for(int i=0; i<(int)dive.size(); i++) {
		ans += solve(num[dive[i]], layers-1);
	}
	
	printf("answer for ");
	printnum(n);
	printf(" for %d layers is %I64d\n", layers, ans);
	
	return dp[make_pair(n, layers)] = ans;
}

number fix(number n) {
	int k = 0;
	for(int i=0; i<n.sz; i++) {
		if(n.e[i] > 0) {
			n.p[k] = n.p[i];
			n.e[k++] = n.e[i];
		}
	}
	n.sz = k;
	return n;
}

ll bt(const number & n, number & cur, int i) {
	if (i == n.sz) {
		return solve(fix(cur), 2);
	}
	
	ll ans = 0;
	for(ll k=0; k<=n.e[i]; k++) {
		cur.e[i] = k;
		ans += bt(n, cur, i+1);
	}
	return ans;
}

int main() {
	sieve();
	
	printf("started\n");
	
	int a, b, c;
	while(scanf("%d^%d^%d", &a, &b, &c) != EOF) {
		
		number nb = num[b];
		for(int it = 0; it < nb.sz; it++) {
			nb.e[it] *= c;
		}
		
		a = maxexp[a];
		number na = num[a];
		multiply(na, nb, nb);
		number cur = nb;
		
		ll ans = bt(nb, cur, 0);
		
		printf("%I64d\n", ans);
	}
	
	return 0;
}