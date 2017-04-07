#include <cstdio>
#include <map>
using namespace std;
map< int, map< int, bool> > mat;
void dfs(int num, int venhoDe, bool* visitado, int grau)
{
    for (int i=0; i<grau; i++) printf("  ");
    printf("%d-%d", venhoDe, num);
    if (visitado[num]){
        printf("\n");
        return;
    }
    visitado[num]=true;
    printf(" pathR(G,%d)\n", num);
    map< int, bool>::iterator it;
    for (it=mat[num].begin(); it!=mat[num].end(); it++){
        dfs(it->first, num, visitado, grau+1);
    }
}
int main()
{
    int N, V, E, x, y;
    scanf("%d", &N);
    for (int caso=1; caso<=N; caso++){
        mat.clear();
        scanf("%d %d", &V, &E);
        bool visitado[V+1];
        for (int i=0; i<=V; i++) visitado[i]=false;
        for (int i=0; i<E; i++){
            scanf("%d %d", &x, &y);
            mat[x][y]=true;
        }
        printf("Caso %d:\n", caso);
        for (int i=0; i<=V; i++){
            if (!visitado[i]){
                visitado[i]=true;
                map< int, bool>::iterator itl;
                for (itl=mat[i].begin(); itl!=mat[i].end(); itl++){
                    dfs(itl->first, i, visitado, 1);
                }
                if (itl!=mat[i].begin()) printf("\n");
            }
        }
    }
    return 0;
}
