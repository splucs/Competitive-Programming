#include <cstdio>
#include <map>
using namespace std;
int main()
{
    int x, npessoas, contotal, con, mor, k=0;
    scanf("%d", &x);
    while (x)
    {
        map<int, int> Map;
        map<int, int>::iterator it;
        k++;
        npessoas=0, contotal=0;
        for (int i=0; i<x; i++)
        {
            scanf("%d %d", &mor, &con);
            if(Map.find(con/mor)==Map.end()) Map[con/mor]=mor;
            else Map[con/mor]+=mor;
            npessoas+=mor;
            contotal+=con;
        }
        printf("Cidade# %d:\n", k);
        for (it=Map.begin(); it!=Map.end(); it++)
        {
            if (it!=Map.begin()) printf(" ");
            printf("%d-%d", it->second, it->first);
        }
        printf("\nConsumo medio: %.2f m3.\n", contotal/(double)npessoas - 0.0049999999);
        scanf("%d", &x);
        if (x) printf("\n");
    }
    return 0;
}
