#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;
#define MAXN 100009

typedef long long ll;
ll vet[MAXN];

template <typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
	ll N, d=0LL;
	int M;
	scanf("%I64d %d", &N, &M);
	for(int i=0; i<M; i++){
		scanf("%I64d", vet+i);
		vet[i] = gcd(N, vet[i]);
		d = gcd(d, vet[i]);
	}
	printf("%I64d\n", N - N/d);
	return 0;
}