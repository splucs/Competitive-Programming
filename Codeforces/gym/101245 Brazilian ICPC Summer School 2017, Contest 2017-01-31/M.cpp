#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009

typedef long long ll;
ll sievesize;
bitset<MAXN> bs;
ll dp[50][MAXN];
int n;
int v[50], va[50], am[50];

void sieve(ll n) {
	sievesize = n + 1;
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= sievesize; i++) {
		if (bs[i]) {
			for (ll j = 2*i; j <= (ll)sievesize; j += i) bs[j] = 0;
		}
	}
}

ll recurse(int index,int qtt){
    ll ans=0;
    if (index==n)return bs[qtt];
    if (dp[index][qtt]!=-1)return dp[index][qtt];
    for(int k=0; k<=am[index];k++) ans+=recurse(index+1,qtt+k*v[index]);
    return dp[index][qtt]=ans;
}

int main() {
	sieve(MAXN);
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", &va[i]);
	sort(va, va+n);
	int k=0;
	v[k] = va[k];
	am[k] = 1;
	for(int i=1; i<n; i++){
		if (va[i] == va[i-1]) am[k]++;
		else {
			v[++k] = va[i];
			am[k] = 1;
		}
	}
	n = k+1;
	memset(dp,-1,sizeof(dp));

	cout<<recurse(0,0)<<endl;
	return 0;
}