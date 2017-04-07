#include <cstdio>

int main()
{
    int N, k, m, Ncand, a, b;
    while(true){
        scanf("%d %d %d", &N, &k, &m);
        if (N==0 && k==0 && m==0) break;
        int esq[N+1], dir[N+1];
        for (int i=1; i<=N; i++) {
            dir[i]=i-1;
            esq[i]=i+1;
        }
        esq[N]=1;
        dir[1]=N;
        Ncand=N;
        a=1;
        b=N;
        while(Ncand>0){
            for (int j=0; j<k-1; j++){
                a=esq[a];
            }
            for(int j=0; j<m-1; j++){
                b=dir[b];
            }
            if (a==b){
                printf("%3d", a);
                esq[dir[a]]=esq[a];
                dir[esq[a]]=dir[a];
                b=dir[b];
                a=esq[a];
                Ncand--;
                if (Ncand>0) printf(",");
            }
            else{
                printf("%3d%3d", a, b);
                esq[dir[a]]=esq[a];
                dir[esq[a]]=dir[a];
                a=esq[a];
                if (a==b) a= esq[a];
                esq[dir[b]]=esq[b];
                dir[esq[b]]=dir[b];
                b=dir[b];
                Ncand-=2;
                if (Ncand>0) printf(",");
            }
        }
        printf("\n");
    }
    return 0;
}
