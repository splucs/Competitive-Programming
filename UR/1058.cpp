#include <cstdio>
#include <map>
using namespace std;
map<int, map<int, int> > mapa;
char vet[40];
int pos(int n, int a, int b)
{
    while (n>b){
        n-=b-a+1;
    }
    while (n<a){
        n+=b-a+1;
    }
    return n;
}
bool valido(int a, int b, int c){
    int Nver=0;
    if (vet[a]=='R')Nver++;
    if (vet[b]=='R')Nver++;
    if (vet[c]=='R')Nver++;
    if (Nver<2) return true;
    else return false;
}
int possibilidades(int a, int b)
{
   // printf("olhando de %d a %d \n", a, b);
    if ((b-a+1)%3!=0) return 0;
    if (b-a+1==0) return 1;
    if (b-a+1==3 && valido(a, a+1, a+2)) return 1;
    if (mapa.find(a)!=mapa.end() && mapa[a].find(b)!=mapa[a].end()) return mapa[a][b];
    int possi=0, a1=pos(a-1, a, b), a2=pos(a-2, a, b);
    for (int i=a+1; i<=a2; i+=3){
        for (int j=i+1; j<=a1; j+=3){
            if (valido(a, i, j)){
          //      printf("triangulo %d-%d-%d valido\n", a, i, j);
                possi+=possibilidades(a+1, i-1)*possibilidades(i+1, j-1)*possibilidades(j+1, a1);
            }
       //     else printf("triangulo %d-%d-%d invalido\n", a, i, j);
        }
    }
    mapa[a][b]=possi;
    return possi;
}
int main()
{
    int T, P;
    scanf("%d", &T);
    for (int caso=1; caso<=T; caso++){
        scanf("%d", &P);
        for (int i=0; i<P; i++) scanf(" %c", vet+i);
     //   for (int i=0; i<P; i++) printf("%c", vet[i]);
     //   printf(" - linha lida\n");
        printf("Case %d: %d\n", caso, possibilidades(0, P-1));
        mapa.clear();
    }
    return 0;
}
