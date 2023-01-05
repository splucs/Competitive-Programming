#include <bits/stdc++.h>
#define MAXN 59
#define INF 0x3f3f3f3f
#define FOR(x, n) for(int x=0; x<n; x++)
#define REP(x, n) for(int x=n-1; x>=0; x--)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define REP1(x, n) for(int x=n; x>0; x--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

int n, m;

string getMax(string a, string b) {
	if (a == "") return b;
	if (b == "") return a;
	return "(" + a + "|" + b + ")";
}

string getMin(string a, string b) {
	if (a == "") return b;
	if (b == "") return a;
	return "(" + a + "&" + b + ")";
}

string getx(int i) {
	if (i < 1 || i > n) return "";
	char str[5];
	sprintf(str, "x%d", i);
	return string(str);
}

string gety(int i) {
	if (i < 1 || i > m) return "";
	char str[5];
	sprintf(str, "y%d", i);
	return string(str);
}

int main() {	
	#ifdef ONLINE_JUDGE
	freopen("merge.in", "r", stdin);
	freopen("merge.out", "w", stdout);
	#endif

	scanf("%d %d", &n, &m);

	FOR1(k, n+m) {
		int i = 0, j = k;
		string ans;
		while(i <= k && j >= 0) {
			if (i <= n && j <= m)
				ans = getMin(ans, getMax(getx(i), gety(j)));
			i++; j--;
		}
		assert(ans.size() <= 2000u);
		printf("%s\n", ans.c_str());
	}
	return 0;
}