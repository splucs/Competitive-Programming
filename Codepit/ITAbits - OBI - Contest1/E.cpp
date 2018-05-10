#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 309
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pf push_front
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

int p[MAXN], n;
bool record[MAXN];

int main() {
	scanf("%d", &n);
	int prvmax = -1;
	int nrecords = 0;
	FOR1(i, n) {
		scanf("%d", &p[i]);
		if (p[i] > prvmax) {
			record[i] = true;
			prvmax = p[i];
			nrecords++;
		}
		else record[i] = false;
	}
	prvmax = -1;
	int ans;
	int increase = -1;
	FOR1(i, n) {
		int cur;
		if (record[i]) {
			cur = nrecords-1;
			for(int j = i+1; j <= n && !record[j]; j++) {
				if (p[j] > prvmax) {
					cur++;
					prvmax = p[j];
				}
			}
			prvmax = p[i];
		}
		else cur = nrecords;
		if (cur > increase) {
			increase = cur;
			ans = p[i];
		}
	}
	printf("%d\n", ans);
	return 0;
}