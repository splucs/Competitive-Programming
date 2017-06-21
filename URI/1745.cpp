#include <cstdio>
#include <cstring>
int main()
{
    char vet[1000002];
    scanf("%s", vet);
    long long contador=0, r0=0, r1=0, r2=0, len = strlen(vet), x, aux;
    for (int i=0; i<len; i++){
        if (vet[i]<'0' || vet[i]>'9'){
            r0 = r1 = r2 = 0;
        }
        else{
            x = vet[i]-'0';
            if (x%3==0){
                r0++;
            }
            else if (x%3==1){
                aux=r2;
                r2=r1;
                r1=r0+1;
                r0=aux;
            }
            else{
                aux=r2;
                r2=r0+1;
                r0=r1;
                r1=aux;
            }
            //printf("r0 = %d r1 = %d r2 = %d\n", r0, r1, r2);
            contador+=r0;
        }
    }
    printf("%lld\n", contador);
    return 0;
}
