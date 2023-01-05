#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

typedef long long ll;
ll a[MAXN], b[MAXN];
int n;
bool s[MAXN];

int main() {
    freopen("fenwick.in", "r", stdin);
    freopen("fenwick.out", "w", stdout);

    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%I64d\n", &a[i]);
        s[i] = false;
    }
    for(int i=1; i<=n; i++){
        if((i & -i) > 1){
            ll sum = 0;
            for(int j = i - (i & -i) + 1; j<i-1; j++){
                if (!s[j]){
                    s[j] = true;
                    b[j] = a[j];
                }
                sum += b[j];
            }
            b[i-1] = -sum;
            s[i-1] = true;
        }
    }
    for(int i=1; i<=n; i++){
        if (!s[i]){
            s[i] = true;
            b[i] = a[i];
        }
        printf("%I64d ", b[i]);
    }
    printf("\n");

    fclose(stdin);
    fclose(stdout);
    return 0;
}