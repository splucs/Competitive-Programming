#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 100009

typedef long long ll;

int N;
ll a[MAXN], K;

bool solve(ll S){
    ll h, l, mid, ans = 0;
    for(int i=0; i<N; i++){
        l = 0;
        h = N-1;
        if (a[i]+a[l] > S) continue;
        if (a[i]+a[h] <= S){
            ans += N-1;
            continue;
        }
        while(h > l + 1){
            mid = (l+h)/2;
            if (a[mid]+a[i] <= S) l = mid;
            else h = mid;
        }
        ans += (i <= l ? l : h);
    }
    ans /= 2;
    return ans >= K;
}

ll bs(){
    ll h = 2*a[N-1];
    ll l = -1ll, mid;
    while(h > l+1){
        mid = (l+h)/2;
        if (solve(mid)) h = mid;
        else l = mid;
    }
    return h;
}

int main(){
    scanf("%d %I64d", &N, &K);
    for(int i=0; i<N; i++){
        scanf("%I64d", a+i);
    }
    sort(a, a+N);
    printf("%I64d\n", bs());
/*
    N = 100;
    for(int i=0; i<N; i++){
       a[i] = rand();
    }
    sort(a, a+N);*/



    return 0;
}