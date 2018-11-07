#include <bits/stdc++.h>
#define MAXN 20000009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define all(x) x.begin(), x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef vector<int> vi;

int a[MAXN], n;
int cnt[12];

int scale[12];
bool submask[MAXN];
void preprocess() {
	FOR(i, 12) {
		scale[i] = 0;
		FOR(j, 12) {
			int k = (j-i+12)%12;
			if (k == 0 || k == 2 || k == 4 || k == 5
				|| k == 7 || k == 9 || k == 11) scale[i] |= (1<<j);
		}
	}
	FOR(mask, (1<<12)) {
		submask[mask] = false;
		FOR(e, 12) if ((mask & scale[e]) == mask) submask[mask] = true;
	}
}

int dp[MAXN], st[MAXN], opt[MAXN];

int main() {
	preprocess();

	map<string, int> note;
	note["Do"] = 0;
	note["Do#"] = 1;
	note["Re"] = 2;
	note["Re#"] = 3;
	note["Mi"] = 4;
	note["Fa"] = 5;
	note["Fa#"] = 6;
	note["Sol"] = 7;
	note["Sol#"] = 8;
	note["La"] = 9;
	note["La#"] = 10;
	note["Si"] = 11;

	scanf("%d ", &n);
	int mask = 0;
	char str[5];
	FOR(j, n) {
		gets(str);
		int &k = a[j];
		switch(str[0]) {
			case 'D': k = str[2] ? 1 : 0;
			break;
			case 'R': k = str[2] ? 3 : 2;
			break;
			case 'M': k = 4;
			break;
			case 'F': k = str[2] ? 6 : 5;
			break;
			case 'S': k = str[2] ? (str[3] ? 8 : 7) : 11;
			break;
			case 'L': k = str[2] ? 10 : 9;
			break;
		}
		mask |= (1<<k);
	}
	if (submask[mask]) {
		printf("1\n");
		return 0;
	}

	int i = 0;
	mask = 0;
	int ans = INF;
	FOR(j, n<<1) {
		cnt[a[j%n]]++;
		if (cnt[a[j%n]] == 1) mask ^= (1<<a[j%n]);
		while(!submask[mask]) {
			cnt[a[i%n]]--;
			if (cnt[a[i%n]] == 0) mask ^= (1<<a[i%n]);
			i++;
		}
		opt[j] = i;
	}

	FOR(j, n<<1) {
		i = opt[j];
		if (i == 0) {
			dp[j] = 1;
			st[j] = j+n;
		}
		else {
			dp[j] = 1 + dp[i-1];
			st[j] = st[i-1];
		}

		if (opt[st[j]] <= j+1 && dp[j] < ans) ans = dp[j];
	}

	printf("%d\n", ans);
	return 0;
}