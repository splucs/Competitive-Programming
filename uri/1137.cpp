#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef struct point{
	double x;
	double y;
} point;

bool isColinear(point a, point b, point c){
	return abs(a.x*b.y + b.x*c.y + c.x*a.y - b.y*c.x - c.y*a.x - a.y*b.x)<0.0049;
}

typedef struct circle{
    point center;
    double radius;
} circle;

bool comp(circle a, circle b){
	if (a.radius<b.radius) return true;
	if (a.radius>b.radius) return false;
	if (a.center.x<b.center.x) return true;
	if (a.center.x>b.center.x) return false;
	if (a.center.y<b.center.y) return true;
	return false;
}

bool equal(circle *a, circle *b){
	return (a->radius==b->radius && a->center.x == b->center.x && a->center.y == b->center.y);
}

double prodInter(point p1, point p2){
    return p1.x*p2.x + p1.y*p2.y;
}

circle findCircle(point a, point b, point c){
    circle ans;
    point al, cl;
    al.x=a.x-b.x;
    cl.x=c.x-b.x;
    al.y=a.y-b.y;
    cl.y=c.y-b.y;
    double D1, D2, D;
    D1=0.5*(cl.y*prodInter(al, al) - al.y*prodInter(cl, cl));
    D2=0.5*(al.x*prodInter(cl, cl) - cl.x*prodInter(al, al));
    D=al.x*cl.y - al.y*cl.x;
    ans.center.x = D1/D + b.x;
    ans.center.y = D2/D + b.y;
    ans.radius = sqrt((ans.center.x-b.x)*(ans.center.x-b.x)+(ans.center.y-b.y)*(ans.center.y-b.y));
    return ans;
}

int calculateN(int cont)
{
	for(int i=0; i<100; i++){
		if (i*(i+1)*(i+2)==6*cont) return i+2;
	}
	return 0;
}

circle circles[1000009];
int main()
{
	int N, cont, maxd, nCircles;
	point points[100];
	while(true){
		scanf("%d", &N);
		if (N==0) break;
		for (int i = 0; i < N; ++i){
			scanf("%lf %lf", &points[i].x, &points[i].y);
		}
		nCircles=0;
		for (int i = 0; i < N; ++i){
			for (int j = 0; j < i; ++j){
				for (int k = 0; k < j; ++k){
					if (i==j || i==k || j==k || isColinear(points[i], points[j], points[k])) continue;
					circles[nCircles++]=findCircle(points[i], points[j], points[k]);
				}
			}
		}
		sort(circles, circles+nCircles, &comp);
		maxd=1;
		cont=0;
		for(int i=1; i<nCircles; i++){
			if(equal(&circles[i],&circles[i-1])) maxd++;
			else{
				if(cont<maxd) cont=maxd;
				maxd=1;
			}
		}
		if(cont<maxd && nCircles>0) cont=maxd;
		printf("%d\n", calculateN(cont));
	}
	return 0;
}

