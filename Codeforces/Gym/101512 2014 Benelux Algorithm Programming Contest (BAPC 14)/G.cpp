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

int N;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll t, a, b, c, best;
	double ans;
	cin>>t;
		
	while (t--){
		cin>>N;
		ans = 0;
		FOR(i, N){
			
			cin>>a>>b>>c;
			double y = (double)(b * b + 4 * a * c) / (4 * a);
			if (y > ans) ans = y, best = i + 1;
		}
		cout<<best<<'\n';
	}
}