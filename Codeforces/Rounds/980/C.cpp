#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define MAXM 300
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

int key[MAXM], nxt[MAXM], n, k;

int find(int i) {
	if (key[i] == -1) return i;
	else return nxt[i] = find(nxt[i]);
}

int main() {
	scanf("%d %d", &n, &k);
	FOR(i, MAXM) key[i] = -1, nxt[i] = i+1;
	FOR(i, n) {
		int p;
		scanf("%d", &p);
		if (key[p] == -1) {
			for(int b = max(p-k+1, 0); b <= p; b++) {
				if (key[b] != -1) {
					if (p-key[b] < k) {
						for(int i = b; i <= p; i=find(i)) key[i] = key[b];
						break;
					}
				}
				else {
					for(int i = b; i <= p; i=find(i)) key[i] = b;
					break;
				}
			}
		}
		printf("%d ", key[p]);
	}
	return 0;
}