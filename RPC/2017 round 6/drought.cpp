#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
typedef long long int ll;
typedef pair<int,int> ii;

int l[MAXN], r[MAXN];
int x[MAXN], h[MAXN];

int main(){
    int T, N;
    scanf("%d", &T);
    ll a;
    while(T-->0){
        scanf("%lld %d", &a, &N);
        for(int i=1; i<=N; i++){
            scanf("%d", &x[i]);
        }
        for(int i=0; i<=N; i++){
            scanf("%d", &h[i]);
        }
        for(int i=0; i<=N; i++){
            if (i == 0) l[i] = h[i];
            else l[i] = max(h[i], l[i-1]);
        }
        for(int i=N; i>=0; i--){
            if (i == N) r[i] = h[i];
            else r[i] = max(h[i], r[i+1]);
        }
        ll ans = 0;
        for(int i=1; i<=N; i++){
            ans += x[i]*a*min(l[i-1], r[i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
