#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-15

typedef long long ll;
typedef pair<ll, ll> ii;

ii read() {
	char str[200];
	scanf(" %s", str);
	int p = -1, nz=0;
	int len = strlen(str);
	for(int i=0; i<len; i++) if(str[i] == '.') p = i;
	ll a=0, b=0;
	if (p == -1) {
		sscanf(str, "%I64d", &a);
		b = 0;
	}
	else {
		str[p] = 0;
		if (p > 0) sscanf(str, "%I64d", &a);
		else a = 0;
		p++;
		while(p < len && str[p] == '0') p++, nz++;
		if (p < len) sscanf(str + p, "%I64d", &b);
		else b = 0;
	}
	int bsz = 0;
	ll baux = b;
	while(baux > 0){
		bsz++;
		baux /= 10;
	}
	for(int i=0; i<9-bsz-nz; i++) b *= 10;
	return ii(a, b);
}

int main()
{
	ii n1 = read();
	ii n2 = read();
	//printf("n1 = %I64d.%09I64d\n", n1.first, n1.second);
	//printf("n2 = %I64d.%09I64d\n", n2.first, n2.second);
	ll a = n1.first*1000000000 + n1.second;
	ll b = n2.first*1000000000 + n2.second;
	ll c = a/b;
	printf("%I64d\n", c);
	return 0;
}