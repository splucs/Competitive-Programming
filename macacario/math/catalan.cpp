#include <cstdio>
#define MAXN 100009

template <typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

typedef long long ll;
ll cat[MAXN];

void catalan(int n){
	cat[0] = cat[1] = 1;
	ll g;
	for(int i=2; i<=n; i++){
		g = gcd(2*(2*i-1), i+1);
		cat[i] = ((2*(2*i-1))/g)*(cat[i-1]/((i+1)/g));
	}
}

void test(int n){
	catalan(n);
	for(int i=0; i<=n; i++) printf(" %I64d", cat[i]);
}

int main()
{
	test(20);
	return 0;
}