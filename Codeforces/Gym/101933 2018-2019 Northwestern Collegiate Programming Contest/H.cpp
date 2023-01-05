#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;

int l, m;

bool check(int c, int t, int r) {
	ll cut = c*10080LL*t;
	ll lawn = (t+r)*1LL*l;
	return cut >= lawn;
}

bool valid(int i, string &str) {
	return i < sz(str) && str[i] != ',';
}

void parse(string str, string &name, int &p, int &c, int &t, int &r) {
	//cout << "parsing " << str << endl;

	int last = 0;
	int i = 0;

	while(valid(i, str)) i++;
	name = str.substr(last, i-last);
	while (!valid(i, str)) i++;
	last = i;

	while(valid(i, str)) i++;
	sscanf(str.substr(last, i-last).c_str(), "%d", &p);
	last = i = i+1;

	while(valid(i, str)) i++;
	sscanf(str.substr(last, i-last).c_str(), "%d", &c);
	last = i = i+1;
	
	while(valid(i, str)) i++;
	sscanf(str.substr(last, i-last).c_str(), "%d", &t);
	last = i = i+1;
	
	while(valid(i, str)) i++;
	sscanf(str.substr(last, i-last).c_str(), "%d", &r);

	assert(i == sz(str));
}

char buffer[MAXN];

int main() {
	char c;
	while(scanf(" %d %d ", &l, &m) != EOF) {
		int lowprice = INF;
		vector<string> ans;
		FOR(j, m) {
			string name;
			int p, c, t, r;
			gets(buffer); scanf(" ");
			parse(string(buffer), name, p, c, t, r);
			if (!check(c, t, r)) continue;
			//printf("ok %s %d %d %d %d\n", name.c_str(), p, c, t, r);
			if (lowprice > p) {
				lowprice = p;
				ans.clear();
			}
			if (lowprice == p) {
				ans.pb(name);
			}
		}
		if (lowprice == INF) cout << "no such mower" << endl;
		else for(string s : ans) cout << s << endl;
	}
	return 0;
}