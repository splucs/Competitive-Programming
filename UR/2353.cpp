#include <bitset>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;
#define MAXN 10000009
typedef long long ll;
ll sievesize;
bitset<MAXN> bs;
vector<ll> primes;

void sieve(ll n){
	sievesize = n+1;
	bs.set();
	bs[0] = bs[1] = 0;
	for(ll i=2; i<=sievesize; i++){
		if (bs[i]){
			for(ll j=i*2; j<=sievesize; j+=i)
				bs[j] = 0;
			primes.push_back(i);
		}
	}
}

bool isPrimeSieve(ll N){
	if (N <= sievesize) return bs[N];
	for(int i=0; i<(int)primes.size() && primes[i]*primes[i] <= N; i++){
		if (N%primes[i] == 0) return false;
	}
	return true;
}

int main(){
	ll N;
	scanf("%lld", &N);
	sieve(sqrt(N)+9);
	while(!isPrimeSieve(N)) N--;
	printf("%lld\n", N);
	return 0;
}
