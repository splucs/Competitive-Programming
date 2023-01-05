#include <map>
#include <cstdlib>
#include <cstdio>
using namespace std;
int main()
{
    int N;
    while(scanf("%d", &N)!=EOF)
    {
        if (N==0) {printf("0\n");continue;}
        int x, y;
        map<int, map<int, bool> > mapa;
        while (N-->0)
        {
            scanf("%d %d", &x, &y);
            mapa[y][x]=true;
        }
        map<int, map<int, bool> >::iterator a;
        map<int, bool>::iterator encima;
        map<int, bool>::iterator embaixo;
        int maior=1, atual;
        for(int i=0; i<2; i++)
        {
            for(a=mapa.begin(); a!=mapa.end(); a++)
            {
                if (mapa.find(a->first+2)==mapa.end()) continue;
               // printf("Analizando linha %d\n", a->first+1);
                encima = a->second.begin();
                embaixo = mapa[a->first+2].begin();
                if (i==1)
                {
                    map<int, bool>::iterator aux;
                    aux = encima;
                    encima = embaixo;
                    embaixo = aux;
                }
                atual =1;
             //   if (i==0) printf("(%d,%d) ", a2->first, embaixo->first);
             //   else printf("(%d,%d) ", a->first, embaixo->first);
                while(encima!=(a)->second.end() && encima!=mapa[a->first+2].end() && embaixo->first >=encima->first)
                {
                    encima++;
                }
                while (embaixo!=(a)->second.end() && embaixo!=mapa[a->first+2].end())
                {
                    if (encima!=(a)->second.end() && encima!=mapa[a->first+2].end())
                    {
                    //    if (i==0) printf("(%d,%d) ", a->first, encima->first);
                     //   else printf("(%d,%d) ", a2->first, encima->first);
                        atual++;
                        while (embaixo!=(a)->second.end() && embaixo!=mapa[a->first+2].end() && embaixo->first <=encima->first)
                        {
                            embaixo++;
                        }
                        if (embaixo!=(a)->second.end() && embaixo!=mapa[a->first+2].end()) atual++;
                        else break;
                      //  if (i==0) printf("(%d,%d) ", a2->first, embaixo->first);
                     //   else printf("(%d,%d) ", a->first, embaixo->first);
                        while(encima!=(a)->second.end() && encima!=mapa[a->first+2].end() && embaixo->first >=encima->first)
                        {
                            encima++;
                        }
                    }
                    else break;
                }
                //printf("\nEsta linha (a=%d): %d\n", a1->first, atual);
                if (atual>maior) maior=atual;
            }
        }
        printf("%d\n", maior);
    }
    return 0;
}
