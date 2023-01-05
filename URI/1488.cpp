#include <cstdio>
#include <cmath>

int main(){
int n,m,p3,z,t=1;
while (scanf("%d",&n)&&n!=0){
    m=0;
    for (int i=sqrt((double)n);i>1;i--){
        z=n/(i*i);
        if (z*i*i==n){
            m=i-1;
            p3=z;
            break;
        }
    }
    printf("Instancia %d\n",t++);
    if (m==0)printf("%d nao e quadripartido\n\n",n);
    else printf("%d %d %d %d %d\n\n",m,m*(p3-1),m*(p3+1),p3,p3*m*m);
}
}
