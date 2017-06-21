#include <cstdio>
int main()
{
    int T, N, D, x;
    char c;
    scanf("%d", &T);
    for (int caso=1; caso<=T; caso++)
    {
        scanf("%d %d", &N, &D);
        int dist[N+2];
        bool big[N+2];
        big[0]=true;
        dist[0]=0;
        big[N+1]=true;
        dist[N+1]=D;
        for (int i=1; i<=N; i++)
        {
            scanf(" %c-%d", &c, &x);
            if (c=='B') big[i]=true;
            else big[i]=false;
            if (x>D) x=D;
            dist[i]=x;
        }
        int maxd=0;
        for (int i=1; i<=N; i++)
        {
            if (big[i])
            {
                if (dist[i+1]-dist[i]>maxd) maxd=dist[i+1]-dist[i];
                if (dist[i]-dist[i-1]>maxd) maxd=dist[i]-dist[i-1];
            }
            else if (dist[i+1]-dist[i-1]>maxd) maxd=dist[i+1]-dist[i-1];
        }
        printf("Case %d: %d\n", caso, maxd);
    }
    return 0;
}
