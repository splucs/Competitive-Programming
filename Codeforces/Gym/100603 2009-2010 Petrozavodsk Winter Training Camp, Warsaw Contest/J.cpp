#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007LL
#define P 29LL
#define MAXL 109
#define MAXN 1009

typedef long long ll;
ll pow1[MAXL], hsh[MAXN];
char s[MAXN][MAXL];
int N, L, M, ans[MAXN];
map<ll, set<int> > amount;

int main() {
	pow1[0] = 1;
	for(int i=1; i<MAXL; i++) pow1[i] = (P*pow1[i-1])%MOD;
	
	scanf("%d %d %d", &N, &L, &M);
	for(int i=0; i<N; i++) {
		scanf(" %s ", s[i]);
		hsh[i] = 0;
		for(int j=0; j<L; j++) {
			hsh[i] = (hsh[i] + (s[i][j] - 'a')*pow1[j])%MOD;
		}
		amount[hsh[i]].insert(i);
	}
	for(int i=0; i<N; i++) {
		ans[i] = amount[hsh[i]].size();
	}
	int i1, i2, j1, j2;
	ll P1, P2;
	while(M--) {
		scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
		i1--; i2--;
		j1--; j2--;
		P1 = hsh[i1];
		P2 = hsh[i2];
		amount[hsh[i1]].erase(i1);
		amount[hsh[i2]].erase(i2);
		hsh[i1] = (hsh[i1] - (pow1[j1]*(s[i1][j1]-(ll)'a'))%MOD + MOD) % MOD;
		hsh[i2] = (hsh[i2] - (pow1[j2]*(s[i2][j2]-(ll)'a'))%MOD + MOD) % MOD;
		swap(s[i1][j1], s[i2][j2]);
		hsh[i1] = (hsh[i1] + (pow1[j1]*(s[i1][j1]-(ll)'a'))%MOD + MOD) % MOD;
		hsh[i2] = (hsh[i2] + (pow1[j2]*(s[i2][j2]-(ll)'a'))%MOD + MOD) % MOD;
		amount[hsh[i1]].insert(i1);
		amount[hsh[i2]].insert(i2);
		if (hsh[i1] != P1) {
			for(set<int>::iterator it = amount[hsh[i1]].begin(); it != amount[hsh[i1]].end(); it++) {
				ans[*it] = max(ans[*it], (int)amount[hsh[i1]].size());
			}
		}
		if (hsh[i2] != P2) {
			for(set<int>::iterator it = amount[hsh[i2]].begin(); it != amount[hsh[i2]].end(); it++) {
				ans[*it] = max(ans[*it], (int)amount[hsh[i2]].size());
			}
		}
	}
	for(int i=0; i<N; i++) printf("%d\n", ans[i]);
	return 0;
}