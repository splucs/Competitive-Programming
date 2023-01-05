#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <cstring>
using namespace std;
#define MAXN 1009
#define REM 1000000007LL

typedef long long ll;
typedef pair<int, int> ii;

map<ii, int> meds;
set<ii> pointsset;

template <typename T>
T extGcd(T a, T b, T& x, T& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        T g = extGcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}
 
template <typename T>
T modInv(T a, T m) {
    T x, y;
    extGcd(a, m, x, y);
    return (x % m + m) % m;
}
 
template <typename T>
T modDiv(T a, T b, T m) {
    return ((a % m) * modInv(b, m)) % m;
}

ll fat[MAXN*MAXN];
void preprocessfat(){
    fat[0] = 1;
    for(ll i=1; i<MAXN*MAXN; i++){
        fat[i] = (i*fat[i-1])%REM;
    }
}

template<typename T>
T pascal(int n, int k, T m){
	//printf("C(%d,%d) = %lld\n", n, k, modDiv(fat[n], (fat[k]*fat[n-k])%m, m));
    return modDiv(fat[n], (fat[k]*fat[n-k])%m, m);
}

int main(){
	int N, x, y, P;
	preprocessfat();
	scanf("%d", &N);
	ii points[MAXN];
	for(int i=0; i<N; i++){
		scanf("%d %d", &x, &y);
		points[i] = ii(x, y);
		pointsset.insert(ii(2*x, 2*y));
		for(int j=0; j<i; j++){
			ii newpair = ii(x + points[j].first, y + points[j].second);
			if (meds.count(newpair)) meds[newpair]++;
			else meds[newpair] = 1;
		}
	}
	map<ii, int>::iterator it;
	int ans[MAXN];
	memset(&ans, 0, sizeof ans);
	for(it = meds.begin(); it!=meds.end(); it++){
		//printf("(%d,%d) -> %d\n", it->first.first, it->first.second, it->second);
		for(int p=0; p<=it->second; p++){
			ans[2*p] = (ans[2*p] + (int)pascal(it->second, p, REM))%REM;
			if (pointsset.count(it->first)){
				//if (p == 1) printf("%d subsets centered in (%d,%d)\n", (int)pascal(it->second, p, REM), it->first.first, it->first.second);
				ans[2*p+1] = (ans[2*p+1] + (int)pascal(it->second, p, REM))%REM;
			}
		}
	}
	ans[1] = N;
	for(int i=1; i<=N; i++){
		printf("%d", ans[i]);
		if (i<N) printf(" ");
		else printf("\n");
	}
	return 0;
}