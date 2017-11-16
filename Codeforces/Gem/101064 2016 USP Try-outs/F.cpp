//Fast Birl Transform
#include <cstdio>
#include <queue>
using namespace std;

typedef long long ll;

ll solve(ll n, ll i, bool pop){
    if (n == 1) return 1;
    if (pop){
        if (i%2 != 0) return i/2 + 1;
        else return (n%2 == 0 ? n/2 + solve(n/2, i/2, true) : n/2 + 1 + solve(n/2, i/2, false));
    }
    else{
        if (i%2 == 0) return i/2;
        else return (n%2 == 0 ? n/2 + solve(n/2, i/2 + 1, false) : n/2 + solve(n/2 + 1, i/2 + 1, true));
    }
}

ll simulate(ll n, ll i){
    queue<ll> q;
    for(int j=1; j<=n; j++){
        q.push(j);
    }
    ll ans = 0;
    bool c = true;
    while(!q.empty()){
        if (c){
            ans++;
            if (q.front() == i) return ans;
            q.pop();
        }
        else{
            q.push(q.front());
            q.pop();
        }
        c = !c;
    }
    return -1;
}

int main()
{
    ll T, N, K;

    scanf("%I64d", &T);

    while(T--){
        scanf("%I64d %I64d", &N, &K);
        printf("%I64d\n", solve(N, K, true));
    }
    return 0;
}