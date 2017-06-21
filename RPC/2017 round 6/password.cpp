#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for(int t=0; t<T; t++){
        int p, num=10;
        scanf("%d", &p);
        printf("0.");
        while(true){
            while(num < p){
                printf("0");
                num *= 10;
            }
            printf("%d", num/p);
            num %= p;
            num *= 10;
            if (num == 10) break;
        }
        printf("\n");
    }
    return 0;
}
