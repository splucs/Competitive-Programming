#include <cstdio>
#include <map>
using namespace std;
int main()
{
    map<int, bool>mapa;
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    mapa[x]=true;
    mapa[y]=true;
    mapa[z]=true;
    map<int, bool>::iterator it;
    for (it=mapa.begin(); it!=mapa.end(); it++)
    {
        printf("%d\n", it->first);
    }
    printf("\n%d\n%d\n%d\n", x, y, z);
    return 0;
}
