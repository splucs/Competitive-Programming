#include <bits/stdc++.h>
using namespace std;
#define MAXN 17
#define MAXM 100009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;

int N, T, b[MAXN], dist[3601];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin>>t;
	while (t--){
		cin>>N>>T;
		FOR(i, N) cin>>b[i];

		queue<ii> pq;
		pq.push(ii(0, 0));
		FOR(i, 3601) dist[i] = INF;
		int ans = INF, cnt;

		while (!pq.empty()){
			ii aux = pq.front();
			pq.pop();
			int u = aux.second, d = aux.first;

			if (u >= T && u - T < ans) ans = u - T, cnt = d;

			FOR(i, N){
				int v = u + b[i];
				if (v < 0) v = 0;
				if (v > 3600) v = 3600;
				if (d + 1 < dist[v]){
					dist[v] = d + 1; pq.push(ii(d + 1, v));
				}
			}
		} 
		cout<<cnt<<' '<<ans<<'\n';
	}
}