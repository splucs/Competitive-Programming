#include <cstdio>
#include <map>
using namespace std;

int main()
{
    int n, m;
    while(scanf ("%d", &n)!=EOF)
    {
        scanf("%d", &m);
        map<int, map<int, int> > mapa;
        // v, k, resposta
        int v, k;
        for(int i=1; i<=n; i++)
        {
            scanf("%d", &v);
            if (mapa[v].count(-1)) mapa[v][-1]++;
            else mapa[v][-1]=1;
            mapa[v][mapa[v][-1]]=i;
        }
        for(int i=1; i<=m; i++)
        {
            scanf("%d %d", &k, &v);
            if (!mapa.count(v)) printf ("0\n");
            else if (!mapa[v].count(k)) printf ("0\n");
            else printf ("%d\n", mapa[v][k]);
        }
    }
    return 0;
}
