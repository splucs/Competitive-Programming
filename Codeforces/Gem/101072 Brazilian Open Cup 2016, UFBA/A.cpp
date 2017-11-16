#include <cstdio>
#include <cmath>

int main(){
    char value[100]={};
    int n,m,a,j,k,p;
    bool poss = true;
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++){
        scanf("%d",&a);
        j=1,p=0;
        k=a;
        while (a>0){
            j*=2,p++;
            a/=2;
        }if (j/2==k)value[p-1]='1';
    }
    j=0;
    while (m>0){
        if (m%2==1&&value[j]!='1'){
            poss=false;
            break;
        }
        j++;
        m/=2;
    }
    if (poss)printf("S\n");
    else printf("N\n");
}