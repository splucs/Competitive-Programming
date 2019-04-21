#include <bits/stdc++.h>
#define MAXN 100009
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;
typedef long long int ll;

int arr[MAXN];
set<ll> all;

int main() {
	int n;
	scanf("%d", &n);
	ll s = 0;
	FOR(i, n) {
		all.insert(s);
		scanf("%d", &arr[i]);
		s += arr[i];
	}
	if (s%2 == 1) {
		puts("N"); return 0;
	}
	
	ll o = 0;
	bool ok = false;
	FOR(i, n) {
		if (o >= s/2) { break; }
		if (all.count((o + s/2)%s)) {
			if (ok) { puts("Y"); return 0; }
			ok = true;
		}
		o += arr[i];
	}
	puts("N");
	return 0;
}
