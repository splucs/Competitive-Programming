#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

ll gcd(ll a, ll b){
	if (b == 0) return a;
	else return gcd(b, a%b);
}

vector<ii> factors(ll n)
{
	vector<ii> ans;
	for(int i=1; i*i <= n; i++){
		if (n%i == 0){
			ans.push_back(ii(i, n/i));
		}
	}
	return ans;
}

int main()
{
	int n;
	scanf("%I64d", &n);
	vector<ii> pos = factors(n);
	bool possible = false;
	for(int i=0; i<(int)pos.size() && !possible; i++){
		int a = pos[i].first;
		int b = pos[i].second;
		if ((b-a)%a != 0) continue;
		int k2 = (b-a)/a;
		for(int k=sqrt(k2); k*k <= k2; k++){
			if (k*k == k2){
				break;
			}
		}
	}
	if (possible) printf("Yes\n");
	else printf("No\n");
	return 0;
}