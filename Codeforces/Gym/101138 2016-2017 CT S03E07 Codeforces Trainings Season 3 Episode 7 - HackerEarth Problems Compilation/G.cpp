#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007LL
#define MAXN 

typedef long long ll;
set<ll> fac;
int n;
ll a, b, x;


int main() {
	scanf("%d %lld %lld %lld", &n, &a, &b, &x);
	for(ll i=1; i*i <= x; i++) {
		if (x%i == 0) {
			fac.insert(i);
			fac.insert(x/i);
		}
	}
	while((*fac.begin()) < a) fac.erase(fac.begin());
	while((*fac.rbegin()) > b) fac.erase(fac.rbegin());
	int m = fac.size();
	for(int i=0; i<n+m+1; i++) {
	}
}