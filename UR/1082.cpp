#include <cstdio>
#include <map>
using namespace std;
map<char, map<char, int> > mapa;
map<char, int> componentes;
void dfs(char a, int comp)
{
    componentes[a]=comp;
    map<char, int>::iterator it;
    for (it=mapa[a].begin(); it!=mapa[a].end(); it++){
        if (mapa[a][it->first]<0){
            mapa[a][it->first]=mapa[it->first][a]=comp;
            dfs(it->first, comp);
        }
    }
}
int main()
{
    int N, V, E;
    char x, y;
    scanf("%d", &N);
    for (int caso=1; caso<=N; caso++){
        componentes.clear();
        mapa.clear();
        scanf("%d %d", &V, &E);
        for (int i=0; i<E; i++){
            scanf(" %c %c", &x, &y);
            mapa[x][y]=mapa[y][x]=-1;
        }
        for (int i=0; i<V; i++){
            componentes[i+'a']=-1;
        }
        int counter=0;
        map<char, int>::iterator it;
        for (it=componentes.begin(); it!=componentes.end(); it++){
            if(it->second<0) dfs(it->first, counter++);
        }
        printf("Case #%d:\n", caso);
        for (int i=0; i<counter; i++){
            for (it=componentes.begin(); it!=componentes.end(); it++){
                if (it->second==i) printf("%c,", it->first);
            }
            printf("\n");
        }
        printf("%d connected components\n\n", counter);
    }
    return 0;
}
