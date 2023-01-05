#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

vector<string> words;
int N;

int main() {
	cin >> N;
	words.resize(N);
	FOR(i, N) {
		string aux;
		cin >> aux;
		sort(all(aux));
		FOR(j, int(aux.size())) {
			if (j == 0 || aux[j] != aux[j-1]) {
				words[i].pb(aux[j]);
			}
		}
	}
	sort(all(words));
	int ans = 0;
	FOR(i, N) {
		if (i == 0 || words[i] != words[i-1]) ans++;
	}
	printf("%d\n", ans);
	return 0;
}