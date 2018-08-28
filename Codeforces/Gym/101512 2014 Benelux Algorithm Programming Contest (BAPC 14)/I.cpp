#include <bits/stdc++.h>
using namespace std;
#define MAXN 509
#define MAXM 1009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;

ll g1, g2;

template <typename T>
T extGcd(T a, T b, T& x, T& y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	else {
		T g = extGcd(b, a % b, y, x);
		y -= a / b * x;
		return g;
	}
}

template<typename T>
void diophantine(T a, T b, T c, T& x, T& y) {
	T d = extGcd(a, b, x, y);
	x *= c / d; y *= c / d;
}

int solve(ll f1, ll f2, ll N){
	ll x, y;
	diophantine(f1, f2, N, x, y);
	//cout<<f1<<' '<<f2<<' '<<N<<' '<<x<<' '<<y<<'\n';
	if (x <= 0) {
		ll d = (-x + 1) / f2;
		d += ((-x + 1) % f2 ? 1 : 0);
		x += d * f2, y -= d * f1;
		if (y < x) return 0;
	}else if (y <= 0) {
		ll d = (-y + 1) / f1;
		d += ((-y + 1) % f1 ? 1 : 0);
		x -= d * f2, y += d * f1;
		if (x <= 0) return 0;
	}
	if (y < x){
		ll d = (x - y) / (f1 + f2);
		d += ((x - y) % (f1 + f2) ? 1 : 0);
		x -= d * f2, y += d * f1;
	}else{
		ll d = (y - x) / (f1 + f2);
		y -= d * f1, x += d * f2;
	}
	g1 = x, g2 = y;

	return y > 0 && x > 0;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, N;
	cin>>t;

	while (t--){
		cin>>N;
		ll a = INF, b = INF;
		for (ll f1 = 1, f2 = 1; f1 + f2 <= N;){
			if (solve(f1, f2, N) && (g2 < b || (g2 == b && g1 < a))) a = g1, b = g2;
			ll aux = f2;
			f2 += f1; f1 = aux;
		}
		cout<<a<<' '<<b<<'\n';
	}
}