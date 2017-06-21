#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

int a[MAXN], ap[MAXN], crivo[MAXN];
int n, m;

int main() {
    freopen("deposits.in", "r", stdin);
    freopen("deposits.out", "w", stdout);

    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    memset(&ap, 0, sizeof ap);
    memset(&crivo, 0, sizeof crivo);
    int b;
    scanf("%d", &m);
    for(int j=0; j<m; j++){
        scanf("%d", &b);
        ap[b]++;
    }
    for(int i=1; i<MAXN; i++){
        if (ap[i] == 0) continue;
        for(int j=i; j<MAXN; j+=i){
            crivo[j] += ap[i];
        }
    }
    long long ans = 0;
    for(int i=0; i<n; i++) {
        ans += crivo[a[i]];
    }
    printf("%I64d\n", ans);

    fclose(stdin);
    fclose(stdout);
    return 0;
}