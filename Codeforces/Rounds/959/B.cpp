#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define push_back pb
#define INF (1LL<<60)
typedef long long ll;
typedef pair<int, int> ii;

int n, k, m;
ll mincost[MAXN], ans = 0;
string words[MAXN];
map<string, int> index;
ll cost[MAXN];
int ids[MAXN];

int main() {
	cin >> n >> k >> m;
	FOR1(i, n) {
		cin >> words[i];
		index[words[i]] = i;
	}
	FOR1(i, n) {
		ll x;
		cin >> x;
		cost[i] = x;
	}
	FOR(j, k) {
		int cnt;
		ll minc = INF;
		cin >> cnt;
		FOR(i, cnt) {
			cin >> ids[i];
			minc = min(minc, cost[ids[i]]);
		}
		FOR(i, cnt) {
			cost[ids[i]] = minc;
		}
	}
	string word;
	FOR(j, m) {
		cin >> word;
		ans += cost[index[word]];
	}
	cout << ans << endl;
	return 0;
}