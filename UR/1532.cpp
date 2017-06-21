#include <stdio.h>

int main(){
    while (true){
        int N, V, dist;
        bool chegou = false;
        scanf ("%d %d", &N, &V);
        if (N==0 && V==0) break;
        for (; V>0; V--){
            dist = 0;
            for (int i=V; i>0 && dist<=N && !chegou; i--){
                for (int j=0; j<i && dist<=N && !chegou; j++){
                    dist+=i;
                    if (dist==N) chegou = true;
                }
            }
        }
        if (chegou) printf ("possivel\n");
        else printf ("impossivel\n");
    }
    return 0;
}
