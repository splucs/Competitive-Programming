#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 100009

typedef long long ll;

bool invcomp(ll a, ll b){
	return a>b;
}

ll gaussxor(ll* arr, int N){
	sort(&arr[1], &arr[N+1], &invcomp);
	ll cur, sig = (1LL << 62);
	for(int j=0, t=0, i; sig > 0; sig >>= 1){
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
	cur = 0;
	for(int i=0; i<N; i++){
		cur = cur^arr[i];
	}
	return cur;
}

ll arr[MAXN];

int main(){
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%lld", &arr[i]);
	}
	printf("%lld\n", gaussxor(arr, N));
	return 0;
}