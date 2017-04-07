#include <stdio.h>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){
    int T, n;
    scanf ("%d", &T);
    for (int caso=1; caso<=T; caso++){
        scanf("%d", &n);
        int vet[n];
        for (int i=0; i<n; i++) scanf("%d", vet+i);
        sort(vet, vet+n);
        int maior = n-1, menor=0, ordem[n+4], dir=n/2+3, esq=n/2+1;
        ordem[n/2+2]=vet[maior--];
        for (int i=0; i<n && maior>=menor ; i++)
        {
            if (i%2==0)
            {
                ordem[dir++]=vet[menor++];
                if (maior<menor) break;
                ordem[esq--]=vet[menor++];
                if (maior<menor) break;
            }
            else{
                ordem[dir++]=vet[maior--];
                if (maior<menor) break;
                ordem[esq--]=vet[maior--];
                if (maior<menor) break;
            }
        }
        int soma1=0;
        for (int i=esq+2; i<dir && n>1; i++)
        {
            soma1+=abs(ordem[i]-ordem[i-1]);
        }
        maior = n-1, menor=0, dir=n/2+3, esq=n/2+1;
        ordem[n/2+2]=vet[menor++];
        for (int i=0; i<n && maior>=menor ; i++)
        {
            if (i%2==1)
            {
                ordem[dir++]=vet[menor++];
                if (maior<menor) break;
                ordem[esq--]=vet[menor++];
                if (maior<menor) break;
            }
            else{
                ordem[dir++]=vet[maior--];
                if (maior<menor) break;
                ordem[esq--]=vet[maior--];
                if (maior<menor) break;
            }
        }
        int soma2=0;
        for (int i=esq+2; i<dir && n>1; i++)
        {
            soma2+=abs(ordem[i]-ordem[i-1]);
        }
        printf("Case %d: %d\n", caso, max(soma1, soma2));
    }
    return 0;
}
