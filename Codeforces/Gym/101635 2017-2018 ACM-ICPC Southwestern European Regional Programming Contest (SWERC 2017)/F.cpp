#include <bits/stdc++.h>
#define MAXN 2009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int W, N, w, l;
	cin>>W>>N;
	ll area = 0;
	FOR(i, N){
		cin>>w>>l;
		area += 1LL * w * l;
	}
	cout<<area / W<<'\n';
}