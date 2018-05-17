#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN 3009

typedef long long ll;
int N;
ll a[MAXN];

ll f[MAXN], opt[MAXN];

ll slope() {
    priority_queue<ll> pq;
    opt[0] = a[0]; f[0] = 0;
    pq.push(a[0]);
    for(int i=1; i<N; i++) {
        pq.push(a[i]);
        f[i] = f[i-1] + abs(a[i] - pq.top());
        if (a[i] < pq.top()) {
            pq.pop();
            pq.push(a[i]);
        }
        opt[i] = pq.top();
    }
    return f[N-1];
}

/*
 *  TEST MATRIX
 */

#define INF (1<<30)
ll brutef[MAXN][MAXN];
int brute() {
    ll M = 0;
    printf("arr: ");
    for(int i=0; i<N; i++) {
        M = max(M, a[i]+1LL);
        printf(" %3I64d", a[i]);
    }
    printf("\n");
    printf("x:   ", 0);
    for(ll x=0; x<=M; x++) {
        printf(" %3I64d", x);
    }
    printf("\n");
    printf("i=%2d:", 0);
    for(ll x=0; x<=M; x++) {
        brutef[0][x] = max(0LL, a[0]-x);
        printf(" %3I64d", brutef[0][x]);
    }
    printf("\n");
    for(int i=1; i<N; i++) {
        printf("i=%2d:", i);
        for(ll x=0; x<=M; x++) {
            brutef[i][x] = INF;
            for(ll y=0; y<=x; y++) {
                brutef[i][x] = min(brutef[i][x], brutef[i-1][y] + abs(y-a[i]));
            }
            printf(" %3I64d", brutef[i][x]);
        }
        printf("\n");
    }
}

/*
 *  Codeforces 713C
 */

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        scanf("%I64d", &a[i]);
        a[i] += N-i;
    }
    printf("%I64d\n", slope());
    return 0;
}