#include <cstdio>
#include <algorithm>
#define MOD 1000000007
using namespace std;

int T;
typedef long long ll;
ll N;

ll rec(ll i){
	if (i<0 || i > N) return 0;
	return i*(N-i+1LL);
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%I64d", &N);
		ll ans = 0;
		for(int i=-2; i<=2; i++){
			ans = max(ans, rec(N/2LL + (ll)i));
		}
		printf("%I64d\n", ans%MOD);
	}
	return 0;
}