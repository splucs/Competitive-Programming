#include <cstdio>
#include <cmath>
double abs(double x)
{
    if (x<0) return -1.0*x;
    else return x;
}
int main()
{
    int X, Y, R, P, Q, A, T;
    double x, y, r, a, t, alpha1, alpha2, d1, d2, area1, area2, theta, phi1, phi2, res;
    while(true){
        scanf("%d %d %d", &X, &Y, &R);
        if (X==0 && Y==0 && R==0) break;
        scanf("%d %d %d %d", &P, &Q, &A, &T);
        x=(double)(X-P);
        y=(double)(Y-Q);
        r=(double)R;
        a=((double)A)*M_PI/180.0;
        t=((double)T)*M_PI/180.0;
        alpha1=a-t/2.0;
        alpha2=a+t/2.0;
        d1 = abs(y-(tan(alpha1)*(x)))*abs(cos(alpha1));
        d2 = abs(y-(tan(alpha2)*(x)))*abs(cos(alpha2));
        theta = atan2(y, x);
        if (d1<r && (abs(theta-alpha1)<M_PI/2.0 || abs(theta+2*M_PI-alpha1)<M_PI/2.0 || abs(theta-2*M_PI-alpha1)<M_PI/2.0)){
            phi1=2.0*acos(d1/r);
            area1=(r*r/2.0)*(phi1-sin(phi1));
        }
        else area1=0.0;
        if (d2<r && (abs(theta-alpha2)<M_PI/2.0 || abs(theta+2*M_PI-alpha2)<M_PI/2.0 || abs(theta-2*M_PI-alpha2)<M_PI/2.0)){
            phi2=2.0*acos(d2/r);
            area2=(r*r/2.0)*(phi2-sin(phi2));
        }
        else area2=0.0;
        if ((theta>=alpha1 && theta<=alpha2) || (theta+2*M_PI>=alpha1 && theta+2*M_PI<=alpha2) || (theta-2*M_PI>=alpha1 && theta-2*M_PI<=alpha2)){
            res=(r*r*M_PI)-abs(area1+area2);
        }
        else{
            res=abs(area1-area2);
        }
        printf("%.1f\n", res);
    }
    return 0;
}
