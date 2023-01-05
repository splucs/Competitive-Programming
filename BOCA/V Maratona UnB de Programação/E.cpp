#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

map<int,int> divisores;
vector<int> d, p;
vector<ii> solutions;

void bt(int ind, ll m, ll h) {
	if (ind == d.size()) {
		ll complement = h/m;
		ll a = (complement+m)/2;
		ll b = (m-complement)/2;
		
		if ((a-b)*(a+b) == h && a > 0 && b > 0) {
			solutions.push_back(ii(b, a));
		}
		return;
	}
	
	for (int i = 0; i <= d[ind]; i++) {
		bt(ind+1, m, h);
		m *= p[ind];
	}
}
int main(){
	ll h;
	int cases = 0;
	while(scanf("%lld", &h) != EOF) {
		divisores.clear(); d.clear(); p.clear(); solutions.clear();
		ll v = h;
		
		for (ll i = 2; i*i <= h && v > 1; i++) {
			while(v%i == 0) { divisores[i]++; v /= i; }
		}
		if (v > 1) divisores[v]++;
		
		for (map<int, int>::iterator it = divisores.begin(); it != divisores.end(); it++) {
			d.push_back((it->second)*2);
			p.push_back(it->first);
		}
		printf("Caso %d: ", ++cases);
		
		bt(0, 1, h*h);
		sort(solutions.begin(), solutions.end());
		if (solutions.size() <= 1 || solutions[1].first > 1000000000) printf("Impossivel\n");
		else {
			printf("Trapezio perfeito\n");
			printf("- Medidas: %lld %lld %lld\n", solutions[0].first, solutions[1].first, h);
			printf("- Diagonais: %lld %lld\n", solutions[0].second, solutions[1].second);
		}
	}
}