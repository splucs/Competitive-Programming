#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("holes.in", "r", stdin);
    freopen("holes.out", "w", stdout);
    int n;
    scanf("%d", &n);
    if (n == 0) printf("1\n");
    else if (n == 1) printf("0\n");
    else{
        if (n%2 != 0) {
            n--;
            printf("4");
        }
        while(n > 0){
            printf("8");
            n -= 2;
        }
        printf("\n");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}