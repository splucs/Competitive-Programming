#include <bits/stdc++.h>
#define MAXN 59
#define FOR(x, n) for(int x=0; x<n; x++)
#define REP(x, n) for(int x=n-1; x>=0; x--)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define REP1(x, n) for(int x=n; x>0; x--)
#define all(x) x.begin(), x.end()
#define sz(x) (int (x.size()) )
using namespace std;
typedef long long ll;

vector<int> hashes[4009];
map<pair<int, int>, string > example;

char w[4009];

const ll prime = 41;
const ll mod = 1000000009;

int main() {
	#ifdef ONLINE_JUDGE
	freopen("pattern.in", "r", stdin);
	freopen("pattern.out", "w", stdout);
	#endif
	
	scanf("%s", w);
	int n = strlen(w);
	FOR(i, n) {
		ll h = 0;
		vector<int> ids; ids.assign(26, 0);
		assert(ids.size() == 26);

		int cnt = 0;

		string mstring = "";

		for (int j = i; j < n; j++) {
			mstring.push_back(w[j]);

			int k = (w[j] - 'a');
			if (ids[k] == 0) {
				ids[k] = ++cnt;
			}
			k = ids[k];
			h = (prime*h + k)%mod;

			hashes[j-i+1].push_back(h);

			example[make_pair(j-i+1, h)] = mstring;
		}
	}

	ll ans = 0; ll wordsz = 0, chosen = 0;

	FOR1(i, n) {
		sort(all(hashes[i]));
		for (int j = 0; j < sz(hashes[i]); j++) {
			int k = j;
			while (k < sz(hashes[i]) && hashes[i][k] == hashes[i][j]) k++;


			if (1ll*(k-j)*i > ans) {
				ans = 1ll*(k-j)*i;
				wordsz = i;
				chosen = hashes[i][j];
			}
			j = k-1;
		}
	}
	printf("%s\n", example[make_pair(wordsz, chosen)].c_str());

}