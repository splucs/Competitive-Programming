#include <bits/stdc++.h>
using namespace std;
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 100309
#define MAXM 309
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define ROF(x,n) for(int x=(n)-1; (x)>=0; (x)--)
#define ROF1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&(x), (y), sizeof(x));
typedef pair<int, int> ii;
typedef long long ll;

char str[MAXN];
int cnt[MAXM], ans[3];

int sim(int a, int n, int t) {
	if (n-a >= t) {
		return a+t;
	}
	else {
		int tl = t - (n-a);
		a = n;
		if (tl % 2 != 0 && t == 1) a--;
		return a;
	}
}

int main() {
	int t;
	scanf("%d", &t);

	FOR(i, 3) {
		scanf(" %s", str);
		int n = strlen(str);
		ans[i] = 0;
		mset(cnt, 0);
		FOR(j, n) {
			cnt[str[j]]++;
		}
		for(int j = 'a'; j <= 'z'; j++) {
			ans[i] = max(ans[i], sim(cnt[j], n, t));
		}
		for(int j = 'A'; j <= 'Z'; j++) {
			ans[i] = max(ans[i], sim(cnt[j], n, t));
		}
	}

	if (ans[0] > ans[1] && ans[0] > ans[2]) printf("Kuro\n");
	else if (ans[1] > ans[0] && ans[1] > ans[2]) printf("Shiro\n");
	else if (ans[2] > ans[1] && ans[2] > ans[0]) printf("Katie\n");
	else printf("Draw\n");
	return 0;
}