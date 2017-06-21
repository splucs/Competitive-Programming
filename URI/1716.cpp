#include <cstdio>
#include <cmath>

int calculateD(int E, int tot){
    return expon();
}
int mdc(int x, int y){
    if (y==0) return x;
    else return mdc(y, x%y);
}
int expon(int base, int expo, int r){
    if (expo==0) return 1;
    int k = expon(base, expo/2, r);
    k = (k*k)%r;
    if (expo%2!=0) k = (k*base)%r;
    return k%r;
}
int main()
{
    int N, E, C, P=-1, Q=-1, D=-1;
    scanf("%d %d %d", &N, &E, &C);
    bool primo[4000];
    int primos[4000], Nprimos=0;

    primo[0]=primo[1]=false;
    for (int i=2; i<4000; i++){
        primo[i]=true;
    }
    for (int i=2; i<4000; i++){
        if (!primo[i]) continue;
        primos[Nprimos++]=i;
        for (int j=2*i; j<4000; j+=i){
            primo[j]=false;
        }
    }
    int aux = sqrt(N);
    for (int i=2; i<aux && D<0; i++){
        for (int j=2; j<aux && D<0; j++){
            if (i==j) continue;
            else if (primos[i]*primos[j]==N && mdc((primos[i]-1)*(primos[j]-1), E)==1){
                D = calculateD(E, (primos[i]-1)*(primos[j]-1));
            }
        }
    }
    printf("%d\n", expon(C, D, N));
    return 0;
}
