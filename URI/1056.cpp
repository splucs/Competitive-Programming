#include <cstdio>
#include <stack>
#include <map>
#include <utility>
using namespace std;
map< pair<char, int>, bool> mapa;
int eliminados, n, m;
bool grafo[105][105], emp[105][105],  grauA[105], grauB[105];
int DFS(char fila, int num, bool venhodeEmp, bool primeiro)
{
   // printf("percorrendo %c-%d\n", fila, num);
    pair<char, int> p;
    p.first = fila;
    p.second = num;
    mapa[p]=true;
    if (fila=='a' && !grauA[num] && !primeiro){
        grauA[num]=true;
      //  printf("fim - true\n");
        return num;
    }
    if (fila=='b' && !grauB[num] && !primeiro){
        grauB[num]=true;
      //  printf("fim - true\n");
        return num;
    }
    if (fila=='a'){
        p.first = 'b';
        for (int i=0; i<m; i++)
        {
            p.second = i;
            if(venhodeEmp && grafo[num][i] && !emp[num][i] && mapa.find(p)==mapa.end()){
                if(DFS('b', i, !venhodeEmp, false)!=-1) {emp[num][i]=!emp[num][i];return num;}
            }
            if (!venhodeEmp && grafo[num][i] && emp[num][i] && mapa.find(p)==mapa.end()){
                if(DFS('b', i, !venhodeEmp, false)!=-1) {emp[num][i]=!emp[num][i];return num;}
            }
        }
    }
    if (fila=='b'){
        p.first = 'a';
        for (int i=0; i<n; i++)
        {
            p.second = i;
            if(venhodeEmp && grafo[i][num] && !emp[i][num] && mapa.find(p)==mapa.end()){
                if(DFS('a', i, !venhodeEmp, false)!=-1) {emp[i][num]=!emp[i][num];return num;}
            }
            if (!venhodeEmp && grafo[i][num] && emp[i][num] && mapa.find(p)==mapa.end()){
                if(DFS('a', i, !venhodeEmp, false)!=-1) {emp[i][num]=!emp[i][num];return num;}
            }
        }
    }
  //  printf("fim - false\n");
   // p.first = fila;
   // p.second = num;
  //  mapa.erase(p);
    return -1;
}
int main()
{
    int T;
    scanf("%d", &T);
    for (int caso=1; caso<=T; caso++){
        eliminados=0;
        scanf(" %d", &n);
        //printf("n=%d\n", n);
        int a[n];
        for (int i=0; i<n; i++) {scanf(" %d", a+i);grauA[i]=false;}
        scanf(" %d", &m);
      //  printf("m=%d\n", m);
        int b[m];
        for (int i=0; i<m; i++){
            scanf(" %d", b+i);
            grauB[i]=false;
            for (int j=0; j<n; j++){
                emp[j][i]=false;
                if (a[j]!=0 && b[i]%a[j]==0 || b[i]==0){
                    grafo[j][i]=true;
                    if (!grauA[j] && !grauB[i]){
                        grauA[j]=grauB[i]=emp[j][i]=true;
                        eliminados++;
                      //  printf("Linha criada de %d a %d\n", a[j], b[i]);
                    }
                }
                else grafo[j][i]=false;
            }
        }
        int x;
        for (int i=0; i<n; i++)
        {
            if (!grauA[i])
            {
                if((x=DFS('a', i, true, true))!=-1)
                {
                //    printf("Linha aumentada criada de %d a %d, x=%d\n", a[i], b[x], x);
                    emp[i][x]=true;
                    grauA[i]=true;
                    eliminados++;
                }
                mapa.clear();
            }
        }
        for (int i=0; i<m; i++)
        {
            if (!grauB[i])
            {
                if((x=DFS('b', i, true, true))!=-1)
                {
                //    printf("Linha aumentada criada de %d a %d\n", a[x], b[i]);
                    emp[x][i]=true;
                    grauB[i]=true;
                    eliminados++;
                }
                mapa.clear();
            }
        }
        printf("Case %d: %d\n", caso, eliminados);
    }
    return 0;
}
