#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1LL << 30)

typedef long long int ll;

ll a[MAXN], p, q;
int n;

bool solve(ll k){
	ll count = 0;
	for(int i=0; i<n; i++){
		if (p == q){
			if (a[i] > k*q) return false;
		}
		else{
			if (a[i]-k*q <= 0) continue;
			if ((a[i]-k*q)%(p-q) == 0) count += (a[i]-k*q)/(p-q);
			else count += (a[i]-k*q)/(p-q) + 1;
		}
	}
	return count <= k;
}

int main(){
	scanf("%d %I64d %I64d", &n, &p, &q);
	for(int i=0; i<n; i++){
		scanf("%I64d", &a[i]);
	}
	ll hi = INF, lo = 0, mid;
	while(hi > lo+1){
		mid = (hi+lo)/2;
		if (solve(mid)) hi = mid;
		else lo = mid;
	}
	printf("%I64d\n", hi);
	return 0;
}