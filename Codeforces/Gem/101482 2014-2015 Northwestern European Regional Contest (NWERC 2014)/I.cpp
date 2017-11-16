#include <bits/stdc++.h>
using namespace std;
#define MAXN 14

typedef long long ll;
ll dist[MAXN][MAXN], L;
int N;

bool simulate(int s, int t) {
	int m1 = (N-2)/2;
	int m2 = (N-2) - m1;
	
	for(int mask=0; mask<(1<<N); mask++) {
		if (mask & (1<<s)) continue;
		if (mask & (1<<t)) continue;
		int cb = __builtin_popcount(mask);
		if (cb != m1 && cb != m2) continue;
		
		vector<ll> v[2];
		vector<int> a[2];
		
		a[0].push_back(s); a[1].push_back(s);
		for(int i=0; i<N; i++) {
			if (mask & (1<<i)) a[0].push_back(i);
			else if (i != s && i != t) a[1].push_back(i);
		}
		a[0].push_back(t); a[1].push_back(t);
		
		for(int k=0; k<2; k++) {
			do {
				ll cost = 0;
				for(int it=1; it<(int)a[k].size(); it++) {
					cost += dist[a[k][it-1]][a[k][it]];
				}
				v[k].push_back(cost);
			} while(next_permutation(a[k].begin()+1, a[k].end()-1));
		}
		
		sort(v[0].begin(), v[0].end());
		sort(v[1].begin(), v[1].end());
		for(int i=0, j=v[1].size()-1; i<(int)v[0].size(); i++) {
			while(j>=0 && v[0][i] + v[1][j] > L) j--;
			if (j>=0 && v[0][i] + v[1][j] == L) return true;
		}
	}
	
	return false;
}

int main() {
	scanf("%d %I64d", &N, &L);
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			scanf("%I64d", &dist[i][j]);
		}
	}
	
	bool ok = false;
	for(int i=1; i<N && !ok; i++) {
		ok = simulate(0, i);
	}
	
	if (ok) printf("possible\n");
	else printf("impossible\n");
	return 0;
}