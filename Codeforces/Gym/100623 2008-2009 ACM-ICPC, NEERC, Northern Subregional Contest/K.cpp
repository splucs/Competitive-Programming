#include <bits/stdc++.h>
using namespace std;
#define MAXN 39

typedef long long ll;
ll v[MAXN];
int  n, m;

int main() {
    freopen("key.in", "r", stdin);
    freopen("key.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        scanf("%I64d", &v[i]);
    }
    sort(v, v+n);
    ll cur = 1;
    int i=0;
    while(m-- > 0){
        while(i < n && v[i] <= cur){
            cur += v[i];
            i++;
        }
        printf("%I64d ", cur);
        cur += cur;
    }
    printf("\n");

    fclose(stdin);
    fclose(stdout);
    return 0;
}