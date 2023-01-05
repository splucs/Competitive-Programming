#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MOD 1000000007LL

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return 1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c *= a;
    return c;
}

typedef long long ll;

bool invcomp(ll a, ll b){
	return a>b;
}

ll gaussxor(ll* arr, int N){
	//sort(arr, arr+N, &invcomp);
	ll cur, sig = (1LL << 62);
	int t = 0;
	for(int i; sig > 0; sig >>= 1){
		i=t;
		while(i<N && (arr[i] & sig)==0) i++;
		if (i >= N) continue;
		swap(arr[i], arr[t]);
		for(int i=0; i<N; i++){
			if(i!=t && (arr[i] & sig)!=0)
				arr[i] ^= arr[t];
		}
		t++;
	}
	return (modExp(2LL, (ll)(N-t), MOD) - 1LL + MOD) % MOD;
}

ll sievesize;
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

map<ll, int> factors;
ll arr[MAXN];
int cnt = 0;

void addprime(ll x, ll p, int i) {
	if (!factors.count(p)) factors[p] = cnt++;
	arr[i] ^= (1LL << factors[p]);
}

void addfactors(ll N, int i) {
	ll PF_idx = 0, PF = primes[PF_idx];
	arr[i] = 0;
	while (PF * PF <= N) {
		
		while (N % PF == 0) {
			N /= PF;
			addprime(N, PF, i);
		}
		PF = primes[++PF_idx];
	}
	// special case if N is a prime
	if (N != 1LL) addprime(N, N, i);
}

int main() {
	int N;
	ll x;
	sieve(MAXN);
	scanf("%d", &N);
	//N = 60;
	for(int i=0; i<N; i++) {
		scanf("%lld", &x);
		//x = primes[i];
		addfactors(x, i);
	}
	printf("%lld\n", gaussxor(arr, N));
	return 0;
}