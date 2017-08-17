#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

int k[MAXN], id[MAXN], a[MAXN], s;
typedef pair<int, int> ii;
set<ii> pq;
map<int, vector<int> > ans;

int main() {
	int N;
	while(scanf("%d", &N), N) {
		for(int i=1; i<=N; i++) {
			scanf("%d", &k[i]);
			id[i] = 0;
			a[i] = 1;
		}
		ans.clear();
		pq.clear();
		scanf("%d", &s);
		for(int i=1; i<=N; i++) {
			while(a[i] < s) {
				id[i]++;
				a[i] = id[i] + (id[i]*(id[i]+1)/2)*(k[i]-2) + 1;
			}
			pq.insert(ii(a[i], i));
		}
		int last = -1, cnt = 0;
		while(cnt < 5 || (pq.begin()->first == last)) {
			int i = pq.begin()->second;
			pq.erase(pq.begin());
			ans[a[i]].push_back(i);
			if (ans[a[i]].size() == 2u) cnt++;
			if (a[i] != last && ans.count(last) && ans[last].size() < 2u) ans.erase(last);
			last = a[i];
			id[i]++;
			a[i] = id[i] + (id[i]*(id[i]+1)/2)*(k[i]-2) + 1;
			pq.insert(ii(a[i], i));
		}
		for(map<int, vector<int> >::iterator it = ans.begin(); it != ans.end(); it++) {
			printf("%d:", it->first);
			vector<int> & v = it->second;
			for(int i=0; i<(int)v.size(); i++) {
				if (i > 0) printf(" ");
				printf("%d", k[v[i]]);
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}