#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

char num[MAXN];

int main(){
    int T;
    scanf("%d", &T);
    int ans[5] = {56, 96, 36, 76, 16};
    for(int t=0; t<T; t++){
        scanf(" %s", num);
        int len = strlen(num);
        char last = num[len-1];
        int i = last - '0';
        if (len == 1 && i == 0) printf("1\n");
        else if (len == 1 && i == 1) printf("66\n");
        else{
            i = (i+3)%5;
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
