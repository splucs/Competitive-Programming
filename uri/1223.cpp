#include <cmath>
#include <cstdio>
 
typedef struct vetor{
    double x;
    double y;
} vetor;
vetor operator + (vetor a, vetor b){
    vetor c;
    c.x = a.x+b.x;
    c.y = a.y+b.y;
    return c;
}
vetor operator *(double k, vetor a){
    vetor c;
    c.x = k*a.x;
    c.y = k*a.y;;
    return c;
}
vetor operator - (vetor a, vetor b){
    vetor c;
    c.x = a.x-b.x;
    c.y = a.y-b.y;
    return c;
}
double prodInter(vetor a, vetor b){
    return a.x*b.x + a.y*b.y;
}
vetor proj(vetor a, vetor b){
    return (prodInter(a, b)/prodInter(b, b))*b;
}
double dist(vetor a, vetor b){
    return sqrt(prodInter(a-b, a-b));
}
double norma(vetor a){
    return sqrt(prodInter(a,a));
}
vetor projPontoReta(vetor p, vetor a, vetor b){
    return proj(p-a, b-a) +a;
}
double distPontoReta(vetor p, vetor a, vetor b){
    vetor d = b-a;
    vetor v = p-a;
    vetor dl = proj(v, d);
    if (prodInter(dl, dl)>prodInter(d, d) || dl.x*d.x<0 || dl.y*d.y<0) return -1.0;
    return norma(v-dl);
}

int main(){
    int N;
    double L, H, minimum, aux;
    vetor vf[1009], vi[1009];
    while(scanf("%d", &N)!=EOF){
        scanf("%lf %lf", &L, &H);
        minimum = L;
        for(int i=0; i<N; i++){
            scanf("%lf %lf %lf", &vi[i].y, &vf[i].x, &vf[i].y);
            vi[i].x = (i%2)*L;
            if (i%2==0) minimum = (minimum>L-vf[i].x?L-vf[i].x:minimum);
            else minimum = (minimum>vf[i].x?vf[i].x:minimum);
        }
        for(int i=0; i+1<N; i++){
            aux = distPontoReta(vf[i], vi[i+1], vf[i+1]);
            if (aux>=0){
                minimum = (minimum>aux?aux:minimum);
            }
            else{
                aux = dist(vf[i], vf[i+1]);
                minimum = (minimum>aux?aux:minimum);
            }
        }
        printf("%.2f\n", minimum);
    }
    return 0;
}