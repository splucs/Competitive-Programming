#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define INF 0x3f3f3f3f
#define MAXN 100009
#define MAXM 29
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;

vector<string> parse(char path[]) {
	int len = strlen(path);
	vector<string> ans;
	path[len++] = '/';
	int last = 0;
	FOR1(i, len-1) {
		if (path[i] == '/') {
			ans.pb(string(path+last+1, i-last-1));
			last = i;
		}
	}
	ans.pop_back();
	//printf("parse:");
	//for(string s : ans) printf(" %s", s.c_str());
	//printf("\n");
	return ans;
}

map<string, int> nxt[MAXN];
ll size[MAXN];
int n, cnt = 0, t, root;
bool hassub[MAXN];

bool dfs(int u, string path) {
	path += "/";
	hassub[u] = false;
	for(auto & pp : nxt[u]) {
		string s = pp.fi;
		int v = pp.se;
		if (dfs(v, path + s)) hassub[u] = true;
	}
	//printf("path %s has sub %d\n", path.c_str(), hassub[u]);
	return size[u] >= t;
}

void insert(vector<string> & v, int val) {
	int u = root;
	size[u] += val;
	for(string s : v) {
		if (!nxt[u].count(s)) nxt[u][s] = ++cnt;
		u = nxt[u][s];
		size[u] += val;
	}
}

void print(int u, string path) {
	path += "/";
	if (nxt[u].empty()) printf("  %s %lld\n", path.c_str(), size[u]);
	else if (!hassub[u]) printf("+ %s %lld\n", path.c_str(), size[u]);
	else {
		printf("- %s %lld\n", path.c_str(), size[u]);
		for(auto & pp : nxt[u]) {
			string s = pp.fi;
			int v = pp.se;
			print(v, path + s);
		}
	}
}

char path[109];

int main() {
	scanf("%d", &n);
	root = ++cnt;
	FOR(i, n) {
		int val;
		scanf(" %s %d", path, &val);
		auto v = parse(path);
		insert(v, val);
	}
	scanf("%d", &t);
	dfs(root, "");
	print(root, "");
	return 0;
}