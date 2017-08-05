#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

typedef pair<char, char> cc;
multiset<cc> pa;
char s1[MAXN], s2[MAXN], s3[MAXN], s4[MAXN];

int main() {
    freopen("enchanted.in", "r", stdin);
    freopen("enchanted.out", "w", stdout);

    scanf(" %s %s %s %s", s1, s2, s3, s4);
    int n = strlen(s1);
    for(int i=0; i<n/2; i++){
        swap(s2[i], s2[n-i-1]);
        swap(s4[i], s4[n-i-1]);
    }
    for(int i=0; i<n; i++){
        pa.insert(cc(s1[i], s2[i]));
    }
    bool possible = true;
    for(int i=0; i<n && possible; i++){
        cc cur = cc(s3[i], s4[i]);
        if (!pa.count(cur)) possible = false;
        else pa.erase(pa.find(cur));
    }
    if(possible) printf("Yes\n");
    else printf("No\n");

    fclose(stdin);
    fclose(stdout);
    return 0;
}