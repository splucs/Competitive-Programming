#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000001
#define INF (1<<30)

vector<int> primes[MAXN];
bool pr[MAXN];
bitset<32*MAXN> used;
int cur[MAXN], arr[MAXN], inv[MAXN];

int main() {
	memset(&pr, true, sizeof pr);
	used.reset();
	for(int i=2; i<MAXN; i++) {
		if (!pr[i]) continue;
		for(int j = i; j<MAXN; j += i) {
			primes[j].push_back(i);
			pr[j] = false;
		}
	}
	for(int i=0; i<MAXN; i++) cur[i] = i;
	arr[1] = 1;
	arr[2] = 2;
	used[1] = used[2] = true;
	int sz = 0;
	for(int i=3; i<MAXN; i++) {
		vector<int> & pp = primes[arr[i-1]];
		int ans = INF;
		for(int it=0; it<(int)pp.size(); it++) {
			int f = pp[it];
			while(used[cur[f]]) cur[f]+=f;
			ans = min(ans, cur[f]);
		}
		arr[i] = ans;
		sz = i;
		if (ans >= MAXN) break;
		used[ans] = true;
		//printf("%d\n", arr[i]);
	}
	for(int i=sz-1; i>=1; i--) inv[arr[i]] = i;
	int n;
	while(scanf("%d", &n), n) {
		printf("The number %d appears in location %d.\n", n, inv[n]);
	}
	return 0;
}