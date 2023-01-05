#include <bits/stdc++.h>
#define pb push_back
#define FOR(x,n) for(int x=0;x<n;x++)
#define FOR1e(x,n) for(int x=1; x<=n; x++)
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

map<int, int> cnt[109];
int total[109];
bool elected[109];

int main() {
	int t, n, k, v, l, vote;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &k, &v);
		FOR1e(i, k) { cnt[i].clear(); total[i] = 0; elected[i] = false; }

		FOR(i, n) {
			scanf("%d", &l);
			FOR(j, l) {
				scanf("%d", &vote);
				if (vote < 1 || vote > k) continue;
				if (j >= v) continue;
				cnt[vote][j]++;
				total[vote]++;
			}
		}

		vector<int> selected;
		while (selected.size() < v) {
			vector<int> ans;
			FOR1e(i, k) {
				if (elected[i]) continue;
				if (ans.empty()) {
					ans.pb(i);
					continue;
				}

				int idx = ans.back();
				if (total[idx] > total[i]) continue;

				if (total[idx] == total[i]) {
					map<int, int>::iterator it_idx = cnt[idx].begin();
					map<int, int>::iterator it_i = cnt[i].begin();

					bool done = false;
					while (it_i != cnt[i].end() && it_idx != cnt[idx].end()) {
						ii score_i = *it_i;
						ii score_idx = *it_idx;
						
						if (score_i == score_idx) {
							it_i++; it_idx++;
							continue;
						}

						if (score_i.first < score_idx.first) {
							ans.clear(); ans.pb(i);
						} else if (score_i.first > score_idx.first) {
						} else if (score_i.second > score_idx.second) {
							ans.clear(); ans.pb(i);
						}
						done = true;
						break;
					}
					if (done) continue;


					if (it_i == cnt[i].end() && it_idx == cnt[idx].end()) {
						ans.pb(i);
					} else if (it_i == cnt[i].end()) {

					} else if (it_idx == cnt[idx].end()) {
						ans.clear(); ans.pb(i);
					}

				} else {
					ans.clear();
					ans.pb(i);
				}
			}
			FOR(i, (int)ans.size()) {
				selected.pb(ans[i]);
				elected[ans[i]] = true;
			}
		}
		FOR(i, (int)selected.size()) {
			if (i > 0) printf(" ");
			printf("%d", selected[i]);
		}
		printf("\n");
	}
}