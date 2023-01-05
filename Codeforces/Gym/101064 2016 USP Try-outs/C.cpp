#include <stdio.h>

int main(){
    int w, h;
    int a[100005], b[100005];

    scanf("%d %d", &w, &h);

    for(int i=0; i<w; i++){
        scanf("%d", &a[i]);
    }

    for(int i=0; i<w; i++){
        scanf("%d", &b[i]);
    }

    int maxi=-1;
    for(int i=0; i<w; i++){
        int s=a[i]+b[i];
        if(s>maxi)
            maxi=s;
    }

    //printf("maxi %d\n", maxi);
    //printf("h %d\n", h);

    double ans=(h-maxi)/2.0;

    printf("%lf\n", ans);

}