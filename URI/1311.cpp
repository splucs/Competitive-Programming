#include <stdio.h>
int main(){
    int S, B;
    while (true){
        scanf ("%d %d", &S, &B);
        if (S==0 && B==0) break;
        int proxesq[S+1], proxdir[S+1], esq, dir;
        for (int i=1; i<=S; i++)
            proxesq[i]=i-1, proxdir[i]=i+1;
        proxdir[S]=0;
        for (int i=0; i<B; i++){
            scanf ("%d %d", &esq, &dir);
            if (proxesq[esq]==0) printf ("* ");
            else printf ("%d ", proxesq[esq]);
            if (proxdir[dir]==0) printf ("*\n");
            else printf ("%d\n", proxdir[dir]);
            proxesq[proxdir[dir]]=proxesq[esq], proxdir[proxesq[esq]]=proxdir[dir];
        }
        printf ("-\n");
    }
    return 0;
}
