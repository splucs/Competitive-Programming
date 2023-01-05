#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

typedef long long ll;

long long L, R;
int M, id[MAXN][MAXN], par[2*MAXN*MAXN], tcnt, s, t;

ll count(ll j) {
	if (j < 0) return 0;
	if (j < s) return par[j];
	ll i = j - (j-s)%t;
	return par[j-i+s] + tcnt*((i-s)/t);
}

int main() {
	while(scanf("%d %lld %lld", &M, &L, &R) != EOF) {
		
		if (M == 1) {
			printf("%lld\n", R-L+1);
			continue;
		}
		
		memset(&id, -1, sizeof id);
		par[0] = par[1] = 1;
		int f0 = 0;
		int f1 = 1;
		id[0][1] = 1;
		for(int i=2; true; i++) {
			int f2 = (f1+f0)%M;
			f0 = f1;
			f1 = f2;
			par[i] = par[i-1] + (f1 == 0 ? 1 : 0);
			if (id[f0][f1] != -1) {
				s = id[f0][f1];
				t = i - s;
				tcnt = par[i] - par[s];
				break;
			}
		}
		
		printf("%lld\n", count(R) - count(L-1));
	}
	
	return 0;
}