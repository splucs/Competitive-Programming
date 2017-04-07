#include <cstdio>
int main()
{
    for (int i=0; i<=20; i+=2){
        for (int j=10; j<=30; j+=10){
            if (i%10==0) printf("I=%d J=%d\n", i/10, (i+j)/10);
            else printf("I=%.1f J=%.1f\n", i/10.0, (i+j)/10.0);
        }
    }
    return 0;
}
