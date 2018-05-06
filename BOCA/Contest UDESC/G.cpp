#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> ii;
#define MAXN 200009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define PMOD(a, m) ((a) % (m) + (m)) % (m)

#define EPS 1e-9

int a[9];
set< pair<int, ii> > vals;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	FOR(i, 5) cin>>a[i];
	sort(a, a + 5);
	int ans = 0;
	FOR(i, 5) FORN(j, i + 1, 5) FORN(k, j + 1, 5){
		if (a[k] < a[j] + a[i] &&  !vals.count(make_pair(a[i], ii(a[j], a[k])))){
			ans++;
			vals.insert(make_pair(a[i], ii(a[j], a[k])));
		}
	}
	cout<<ans<<'\n';
}