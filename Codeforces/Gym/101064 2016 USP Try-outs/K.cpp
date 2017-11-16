#include <cstdio>

int main(){
    int n;
    double p;
    int i=2;
    scanf("%d",&n);
    p=1;
    while (true){
        p*=1-(double)(i-1)/n;
        if (p<0.5){
            printf("%d\n",i);
            break;
        }
        i++;
    }
}