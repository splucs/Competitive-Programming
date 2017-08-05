#include <bitset>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define MAXN 10000009

typedef long long int ll;
ll sievesize, numDiffPF[MAXN];
bitset<MAXN> bs;
vector<ll> primes;

void sieve(ll n) {
	sievesize = n + 1;
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= sievesize; i++) {
		if (bs[i]) {
			for (ll j = i * i; j <= (ll)sievesize; j += i) bs[j] = 0;
			primes.push_back(i);
		}
	}
}

//O(sqrt(n)/logn), works if factors are less than the biggest prime in primes
bool isPrimeSieve(ll N) {
	if (N <= (ll)sievesize) return bs[N];
	for (int i = 0; i < (int)primes.size() && primes[i]*primes[i] <= N; i++)
		if (N % primes[i] == 0) return false;
	return true;
}

//O(sqrt(n))
bool isPrime(ll N){
    if (N < 0) return isPrime(-N);
	for(ll i=2; i*i <= N; i++){
		if (N % i == 0) return false;
	}
	return true;
}

//O(sqrt(n))
bool isPrimeFast(ll n){
    if (n < 0) n = -n;
    if (n < 5 || n % 2 == 0 || n % 3 == 0)
        return (n == 2 || n == 3);
    ll maxP = sqrt(n) + 2;
    for (ll p = 5; p < maxP; p += 6) {
        if (p < n && n % p == 0) return false;
        if (p+2 < n && n % (p+2) == 0) return false;
	}
    return true;
}

vector<ll> primeFactors(ll N) {
	vector<int> factors;
	ll PF_idx = 0, PF = primes[PF_idx];
	while (PF * PF <= N) { 
		while (N % PF == 0) {
			N /= PF;
			factors.push_back(PF);
		}
		PF = primes[++PF_idx];
	}
	// special case if N is a prime
	if (N != 1) factors.push_back(N);
	return factors;
}

ll numDiv(ll N) {
	ll PF_idx = 0, PF = primes[PF_idx], ans = 1; // start from ans = 1
	while (PF * PF <= N) {
		ll power = 0; // count the power
		while (N % PF == 0) { N /= PF; power++; }
		ans *= (power + 1); // according to the formula
		PF = primes[++PF_idx];
	}
	// (last factor has pow = 1, we add 1 to it)
	if (N != 1) ans *= 2;
	return ans;
}

ll EulerPhi(ll N) {
	ll PF_idx = 0, PF = primes[PF_idx], ans = N;
	while (PF * PF <= N) {
		if (N % PF == 0) ans -= ans / PF;
		while (N % PF == 0) N /= PF;
		PF = primes[++PF_idx];
	}
	if (N != 1) ans -= ans / N;
	return ans;
}

void numDiffPf(){
	memset(numDiffPF, 0, sizeof numDiffPF);
	for (int i = 2; i < MAXN; i++)
		if (numDiffPF[i] == 0)
			for (int j = i; j < MAXN; j += i)
				numDiffPF[j]++;
}

int main(){
	sieve(MAXN); // can go up to 10^7 (need few seconds)
	printf("%d\n", isPrime(2147483647)); // 10-digits prime
	printf("%d\n", isPrime(136117223861LL)); // not a prime, 104729*1299709
	return 0;
}