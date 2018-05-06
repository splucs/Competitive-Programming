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

int a[11]={};
int pos[11] = {0, 7, 6, 6, 5, 4, 4, 3, 2, 2, 1};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	FORN(i, 1, 11) a[i] = a[i - 1] + 2 * i;
	
	int X;
	while (cin>>X && X != -1)cout<<a[pos[X]]<<'\n';
}