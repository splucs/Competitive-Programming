#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

typedef long long ll;
typedef pair<ll, ll> ii;

ii v[MAXN];
int N;

int main() {
	freopen("pulp.in", "r", stdin);
	freopen("pulp.out", "w", stdout);
	
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%I64d %I64d", &v[i].first, &v[i].second);
	}
	sort(v, v+N);
	ll ans = 0, curday, left;
	map<ll, int> pq;
	for(int i=0; i<N; i++) {
		if (!pq.count(v[i].second)) pq[v[i].second] = 1;
		else pq[v[i].second]++;
		if (i == N-1) left = (1LL<<60);
		else left = v[i+1].first - v[i].first;
		curday = v[i].first;
		//printf("%I64d days left...\n", left);
		while(left > 0 && !pq.empty()) {
			ll cur = pq.begin()->first;
			pq.begin()->second --;
			if (pq.begin()->second == 0) pq.erase(cur);
			//printf("cur=%I64d left=%I64d\n", cur, left);
			ll dt = min(cur, left);
			cur -= dt;
			left -= dt;
			curday += dt;
			//printf("curday = %I64d\n", curday);
			if (cur > 0LL) {
				if (pq.count(cur)) pq[cur] = 1;
				else pq[cur]++;
			}
			else {
				//printf("finished a book in day %I64d\n", curday);
				ans += curday;
			}
		}
	}
	printf("%I64d\n", ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}