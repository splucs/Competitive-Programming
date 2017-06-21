#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
	ll n;
	scanf("%I64d", &n);
	bool possible = false;
	for(ll i=0, j; i*i<=n; i++)
	{
		j = sqrt(n - i*i);
		if (j*j + i*i == n) possible = true;
	}
	if (possible) printf("Yes\n");
	else printf("No\n");
	return 0;
}