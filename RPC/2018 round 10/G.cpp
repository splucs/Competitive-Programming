#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
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

ll qs[20];
int pos[256];
int RA[MAXN], tempRA[MAXN];
int tempSA[MAXN], SA[MAXN], c[MAXN], n;
int Phi[MAXN], PLCP[MAXN], LCP[MAXN];
string str;

void countingSort(int k){
	int i, sum, maxi = max(300, n);
	memset(c, 0, sizeof c);
	FOR(i, n) c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; ++i){
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	FOR(i, n) tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
	FOR(i, n) SA[i] = tempSA[i];
}

void sa(){
	int i, k, r; n = str.size() + 1;
	str.pb('$');
	FOR(i, n) RA[i] = pos[str[i]], SA[i] = i;
	for (k = 1; k < n; k <<= 1){
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = r = 0;
		FORN(i, 1, n) tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
		FOR(i, n) RA[i] = tempRA[i];
		if (RA[SA[n - 1]] == n - 1) break;
	}
}

void lcp(){
	int i, L;
	Phi[SA[0]] = -1;
	FORN(i, 1, n) Phi[SA[i]] = SA[i - 1];
	for (i = L = 0; i < n; ++i){
		if (Phi[i] == -1){
			PLCP[i] = 0; continue;
		}
		while (pos[str[i + L]] == pos[str[Phi[i] + L]]) ++L;
		PLCP[i] = L;
		L = max(L - 1, 0);
	}
	FOR(i, n) LCP[i] = PLCP[SA[i]];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int q;
	string s1;
	while (cin>>str>>s1>>q && q){
		char auxc = 'a';
		for (char c : s1) pos[c] = auxc++;
		FOR(i, q)cin>>qs[i];
		//sort(qs, qs + q);
		
		sa();
		lcp();
		
		//FOR(i, n) cout<<SA[i]<<' '<<LCP[i]<<' ';
		//cout<<'\n';
	//	int cur = 0;
		--n;
		FOR(j, q){
			ll acum = 0;
			int ans = 0;
			FORN(i, 1, n + 1){
				int u = SA[i];
				if (acum + n - u - LCP[i] >= qs[j]){
					ll rem = qs[j] - acum + LCP[i];
					cout<<str.substr(u, rem)<<'\n';
					ans = 1;
					++i;
					while (i <= n && LCP[i] >= rem) ++ans, ++i;
					cout<<ans<<'\n';
					break;
				}
				acum += n - u - LCP[i];
			}
			if (!ans)cout<<"*\n0\n";
		}
	}
}
