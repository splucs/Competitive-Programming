#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int N, cnt[MAXM];
char str[MAXN];

int main() {
	scanf("%s", str);
	N = strlen(str);
	memset(&cnt, 0, sizeof cnt);
	int diff = 0, bigz = 0;
	FOR(i, N) {
		if (cnt[str[i]] == 0) {
			diff++;
		}
		cnt[str[i]]++;
		if (cnt[str[i]] == 2) {
			bigz++;
		}
	}
	bool ok;
	if (diff > 4) ok = false;
	else if (diff == 4) ok = true;
	else if (diff == 3) {
		ok = bigz > 0;
	}
	else if (diff == 2) {
		ok = bigz == 2;
	}
	else if (diff == 1) ok = false;
	if (ok) printf("Yes\n");
	else printf("No\n");
	return 0;
}