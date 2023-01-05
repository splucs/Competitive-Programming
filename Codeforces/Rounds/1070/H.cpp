#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
typedef long long ll;

int main() {
	int n, q;
	cin >> n;
	map<string, int> cnt;
	map<string, string> match;
	FOR(i, n) {
		string str;
		cin >> str;
		set<string> used;
		int m = str.size();
		FOR1(j, m) FOR(i, j) {
			string sub = str.substr(i, j-i);
			if (used.count(sub)) continue;
			used.insert(sub);
			cnt[sub]++;
			match[sub] = str;
		}
	}
	cin >> q;
	string query;
	FOR(i, q) {
		cin >> query;
		if (!cnt.count(query)) cout << "0 -\n";
		else cout << cnt[query] << " " << match[query] << endl;
	}
	return 0;
}