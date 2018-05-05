#include <bits/stdc++.h>
using namespace std;
#define MAXN 150009

typedef long long ll;
typedef pair<int, ll> ii;
int N;
map<ll, set<int> > indexes;

int main() {
	scanf("%d", &N);
	ll a;
	for(int i = 0; i < N; i++) {
		scanf("%I64d", &a);
		indexes[a].insert(i);
	}
	vector<ii> ans;
	for(auto it = indexes.begin(); it != indexes.end(); it++) {
		ll num = it->first;
		set<int> & ids = it->second;
		while (ids.size() >= 2u) {
			int id1 = *ids.begin();
			ids.erase(ids.begin());
			int id2 = *ids.begin();
			ids.erase(ids.begin());
			indexes[2*num].insert(id2);
		}
		if (ids.size() == 1u) {
			ans.push_back(ii(*ids.begin(), num));
		}
		it = indexes.find(num);
	}
	sort(ans.begin(), ans.end());
	printf("%u\n", ans.size());
	for(int i = 0; i < (int)ans.size(); i++) {
		printf("%I64d ", ans[i].second);
	}
	return 0;
}