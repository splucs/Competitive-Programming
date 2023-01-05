#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x);
typedef long long ll;

int p[MAXN], s[MAXN];
int ans, n;

void release(int i) {
	if (i == 0 || p[i] == 0) return;
	release(p[i]);
	//printf("removing %d inside of %d\n", i, p[i]);
	s[p[i]] = 0;
	p[i] = 0;
	ans++;
}

int main() {
	while(scanf("%d", &n) != EOF) {
		mset(s, 0);
		FOR1(i, n) {
			scanf("%d", &p[i]);
			s[p[i]] = i;
		}
		ans = 0;
		FOR1(i, n) {
			int j;
			scanf("%d", &j);
			if (p[i] == j) continue;
			release(i);
			if (j == 0) continue;
			release(s[j]);
			release(j);
			ans++;
			//printf("putting %d inside of %d\n", i, j);
			p[i] = j;
			s[j] = i;
		}
		printf("%d\n", ans);
	}
	return 0;
}