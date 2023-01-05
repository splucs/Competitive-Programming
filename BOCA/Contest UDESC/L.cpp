#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF (1<<30)
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

int digit1(ll cpf) {
	ll sum = 0;
	FOR1(i, 9) {
		sum += (cpf%10)*(i+1);
		cpf /= 10;
	}
	ll r = sum % 11;
	if (r < 2) return 0;
	else return 11-r;
}

int digit2(ll cpf) {
	cpf = cpf*10 + digit1(cpf);
	ll sum = 0;
	FOR1(i, 10) {
		sum += (cpf%10)*(i+1);
		cpf /= 10;
	}
	ll r = sum % 11;
	if (r < 2) return 0;
	else return 11-r;
}

bool check(ll cpf, ll d) {
	return digit1(cpf) == d/10 && digit2(cpf) == d%10;
} 

set<ll> pres;

int main() {
	int N;
	scanf("%d", &N);
	while(N --> 0) {
		ll cpf, d;
		scanf("%lld %lld", &cpf, &d);
		if (!check(cpf, d)) {
			printf("Invalido\n");
		}
		else if (pres.count(cpf)) {
			printf("Clonado\n");
		}
		else {
			printf("Sucesso\n");
			pres.insert(cpf);
		}
	}
	return 0;
}