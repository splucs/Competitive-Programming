#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 10001009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
#define pb push_back
#define L(N) N<<1
#define R(N) (N<<1) + 1
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
const ll MOD = 1000000007;

ll N, b[MAXN], a[MAXN];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, a, b;
	cin>>t;
	while (t--){
		cin>>a>>b;
		double ans = a * log10(2) + b * log10(5);
		cout<<((int)floor(ans) + 1)<<'\n';
	}
}
