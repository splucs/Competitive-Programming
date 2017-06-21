#include <cmath>
#include <cstdio>

typedef struct vetor{
    double x;
    double y;
    double z;
} vetor;
vetor operator + (vetor a, vetor b){
    vetor c;
    c.x = a.x+b.x;
    c.y = a.y+b.y;
    c.z = a.z+b.z;
    return c;
}
vetor operator *(double k, vetor a){
    vetor c;
    c.x = k*a.x;
    c.y = k*a.y;
    c.z = k*a.z;
    return c;
}
vetor operator - (vetor a, vetor b){
    vetor c;
    c.x = a.x-b.x;
    c.y = a.y-b.y;
    c.z = a.z-b.z;
    return c;
}
vetor prodVetor(vetor a, vetor b){
    vetor c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = a.z*b.x - b.z*a.x;
    c.z = a.x*b.y - b.x*a.y;
    return c;
}
double prodInter(vetor a, vetor b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
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
    if (prodInter(dl, dl)>prodInter(d, d) || dl.x*d.x<0 || dl.y*d.y<0 || dl.z*d.z<0) return -1.0;
    return norma(v-dl);
}
vetor projPontoPlano(vetor p, vetor a, vetor b, vetor c){
    return p - proj(p-a, prodVetor(b-a, c-a));
}
double distPontoPlano(vetor p, vetor a, vetor b, vetor c){
    vetor pr = projPontoPlano(p, a, b, c);
    vetor d1, d2;
    d1 = projPontoReta(pr, b, c)-pr;
    d2 = projPontoReta(a, b, c)-a;
    if (d1.x*d2.x < 0 || d1.y*d2.y < 0 || d1.z*d2.z < 0 || prodInter(d2, d2)<prodInter(d1, d1)) return -1.0;
    d1 = projPontoReta(pr, a, c)-pr;
    d2 = projPontoReta(b, a, c)-b;
    if (d1.x*d2.x < 0 || d1.y*d2.y < 0 || d1.z*d2.z < 0 || prodInter(d2, d2)<prodInter(d1, d1)) return -1.0;
    d1 = projPontoReta(pr, b, a)-pr;
    d2 = projPontoReta(c, b, a)-c;
    if (d1.x*d2.x < 0 || d1.y*d2.y < 0 || d1.z*d2.z < 0 || prodInter(d2, d2)<prodInter(d1, d1)) return -1.0;
    return norma(pr-p);
}
double distRetaReta(vetor a1, vetor a2, vetor b1, vetor b2){
    vetor va = a2-a1;
    vetor vb = b2-b1;
    vetor d = (a1-b1) + proj(b1-a1, prodVetor(va, vb));
    double lambda1, lambda2;
    if (va.x*vb.y - vb.x*va.y!=0.0) lambda1 = (vb.x*d.y - d.x*vb.y)/(va.x*vb.y - vb.x*va.y);
    else if (va.x*vb.z - vb.x*va.z!=0.0) lambda1 = (vb.x*d.z - d.x*vb.z)/(va.x*vb.z - vb.x*va.z);
    else if (va.y*vb.z - vb.y*va.z!=0.0) lambda1 = (vb.y*d.z - d.y*vb.z)/(va.y*vb.z - vb.y*va.z);
    if (vb.x*va.y - va.x*vb.y!=0.0) lambda2 = (d.x*va.y - va.x*d.y)/(vb.x*va.y - va.x*vb.y);
    else if (vb.x*va.z - va.x*vb.z!=0.0) lambda2 = (d.x*va.z - va.x*d.z)/(vb.x*va.z - va.x*vb.z);
    else if (vb.y*va.z - va.y*vb.z!=0.0) lambda2 = (d.y*va.z - va.y*d.z)/(vb.y*va.z - va.y*vb.z);
    if (lambda1<0 || lambda1 >1 || lambda2<0 || lambda2 >1) return -1.0;
    else return norma(proj(b1-a1, prodVetor(va, vb)));
}
double verificar(vetor *a, vetor *b){
    double minimo=dist(a[0], b[0]), x;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            x = dist(a[i], b[j]);
            if (x>=0.0 && x<minimo) minimo=x;
        }
    }
    for (int i=0; i<4; i++){
        for (int j=i+1; j<4; j++){
            for (int k=0; k<4; k++){
                x = distPontoReta(a[k], b[i], b[j]);
                if (x>=0.0 && x<minimo) minimo=x;
            }
        }
    }
    for (int i=0; i<4; i++){
        for (int j=i+1; j<4; j++){
            for (int k=j+1; k<4; k++){
                for (int m=0; m<4; m++){
                    x = distPontoPlano(a[m], b[i], b[j], b[k]);
                    if (x>=0.0 && x<minimo) minimo=x;
                }
            }
        }
    }
    for (int i=0; i<4; i++){
        for (int j=i+1; j<4; j++){
            for (int m=0; m<4; m++){
                for (int p=m+1; p<4; p++){
                    x = distRetaReta(a[i], a[j], b[m], b[p]);
                    if (x>=0.0 && x<minimo) minimo=x;
                }
            }
        }
    }
    return minimo;
}
int main(){
    int T;
    scanf("%d", &T);
    vetor a[4], b[4];
    double x, y;
    for (int caso=1; caso<=T; caso++){
        for (int i=0; i<4; i++) scanf("%lf %lf %lf", &a[i].x, &a[i].y, &a[i].z);
        for (int i=0; i<4; i++) scanf("%lf %lf %lf", &b[i].x, &b[i].y, &b[i].z);
        x = verificar(a, b);
        y = verificar(b, a);
        if (x>y) printf("%.2f\n", y);
        else printf("%.2f\n", x);
    }
    return 0;
}
