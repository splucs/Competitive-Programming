//Fast BIRL Transform
#include <cstdio>
#include <math.h>
#define EPS 1e-12

int main()
{
    double W, H, vx[5], vy[5];
    scanf("%lf %lf", &H, &W);
    for(int i=1; i<=4; i++){
        scanf("%lf %lf", &vx[i], &vy[i]);
    }
    double v1x = vx[1];
    double v1y = vy[1];
    double v21x = vx[2] - vx[1];
    double v21y = vy[2] - vy[1];
    double v41x = vx[4] - vx[1];
    double v41y = vy[4] - vy[1], l, k;
    /*if (fabs(v41x*v21y + (v41y-H)*(W-v21x)) < EPS){
        l = (v1y*(v21x-W) - v1x*v21y)/(v21y*v41x + (v21x-W)*(H-v41y));
        k = (l*(H-v41y) - v1y)/v21y;
    }
    else if (fabs(v21y*v41x + (v21x-W)*(H-v41y)) < EPS){
        k = (v1x*(v41y-H) - v1y*v41x)/(v41x*v21y + (v41y-H)*(W-v21x));
        l = (k*(W-v21x) - v1x)/v41x;
    }
    else{*/
        k = (v1x*(v41y-H) - v1y*v41x)/(v41x*v21y + (v41y-H)*(W-v21x));
        l = (v1y*(v21x-W) - v1x*v21y)/(v21y*v41x + (v21x-W)*(H-v41y));
    printf("%.8f %.8f\n", k*W, l*H);

//    double d12 = sqrt( (vx[1]-vx[0])*(vx[1]-vx[0])) +((vy[1]-vy[0])*(vy[1]-vy[0]));
//    double d14 = sqrt( (vx[3]-vx[0])*(vx[3]-vx[0])) +((vy[3]-vy[0])*(vy[3]-vy[0]));
//
//    printf("%lf %lf", )

    return 0;
}