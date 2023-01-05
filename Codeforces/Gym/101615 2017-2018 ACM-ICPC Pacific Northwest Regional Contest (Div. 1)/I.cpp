#include <bits/stdc++.h>
#define MAXN 309
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define REP(x,n) for(int x=n-1; x>=0; x--)
#define REP1(x,n) for(int x=n; x>0; x--)
#define pb push_back
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
typedef vector<int> vi;

ll large_value = 12000000000000LL;

vector<pair<ll, char> > added, nadded, add_ans;
vector<ll> deleted, ndeleted, del_ans;

void compute() {
	char op, let;
	ll val;
	added.clear(); deleted.clear();
	while (scanf(" %c", &op) != EOF && op != 'E') {
		ndeleted.clear();
		nadded.clear();
		scanf("%lld", &val);
		if (op == 'I') {
			scanf(" %c", &let);

			nadded.pb(make_pair(val, let));
			FOR(i, sz(added)) {
				if (added[i].first < val) {
					nadded.back() = added[i];
					nadded.pb(make_pair(val, let));
				} else if (added[i].first >= val) nadded.pb(make_pair(added[i].first + 1, added[i].second));
			}
			swap(nadded, added);
		} else {
			int t = 0;
			FOR(i, sz(added)) {
				if (added[i].first < val) {
					t++;
					nadded.pb(added[i]);
				} else if (added[i].first == val) {
					val = -1;
				} else {
					nadded.pb(make_pair(added[i].first - 1, added[i].second));
				}
			}
			swap(nadded, added);
			if (val == -1) continue;

			val -= t;
			FOR(i, sz(deleted)) {
				if (deleted[i] <= val) {
					val++;
					ndeleted.pb(deleted[i]);
				} else {
					ndeleted.pb(val);
					i--;
					val = large_value;
				}
			}
			if (val < large_value) ndeleted.pb(val);
			swap(ndeleted, deleted);
		}
	}

}

int main() {
	compute();
	add_ans = added;
	del_ans = deleted;
	/*FOR(i, sz(add_ans)) printf("%lld %c\n", add_ans[i].first, add_ans[i].second);
	printf("\n");
	FOR(i, sz(del_ans)) printf("%lld\n", del_ans[i]);
	printf("\n");*/
	compute();
	
	if (added == add_ans && del_ans == deleted) puts("0");
	else puts("1");
}