#include <cstdio>
#include <string>
#include <cstring>
#include <map>
using namespace std;
int mdc(int x, int y){
    if (y==0) return x;
    else return mdc(y, x%y);
}
int main()
{
    char c[100], aux[102];
    int N, k, cont=0, bullshits=0;
    map<string, bool> mapa;
    while(scanf("%s", c)!=EOF){
        N = strlen(c);
        for (int i=0; i<N; i++){
            if (c[i]>='a' && c[i]<='z') c[i]+='A'-'a';
        }
        k=0;
        for (int i=0; i<=N; i++){
            if (c[i]>='A' && c[i]<='Z'){
                aux[k++]=c[i];
            }
            else{
                aux[k]='\0';
                k=0;
                if (!strcmp("BINGO", aux) || strlen(aux)==0) continue;
                if (!strcmp("BULLSHIT", aux)){
                    map<string, bool>::iterator it;
                    bullshits++;
                    int contador=0;
                    for (it=mapa.begin(); it!=mapa.end(); it++){
                        contador++;
                    }
                    mapa.clear();
                    cont+=contador;
                }
                else{
                    mapa[aux]=true;
                   // printf("\nword: %s\n", aux);
                }
            }
        }
    }
    N=mdc(cont, bullshits);
    printf("%d / %d\n", cont/N, bullshits/N);
    return 0;
}
