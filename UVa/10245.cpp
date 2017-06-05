#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <set>
#define EPS 1e-9
#define INF 1e+9
#define MAXN 100009
using namespace std;

struct point {
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
};

double dist(point p1, point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

typedef pair<point, point> pp;

bool compx(point a, point b){
    if (fabs(a.x - b.x)<EPS) return a.y < b.y;
    else return a.x < b.x;
}

bool compy(point a, point b){
    if (fabs(a.y - b.y)<EPS) return a.x < b.x;
    else return a.y < b.y;
}

pp closestPair(point* points, point* aux, int a, int b) {
    pp pl, pr, ans = make_pair(point(-INF, 0), point(0, INF));
    if (a == b) return ans;
    int mid = (a+b)/2;
    pl = closestPair(points, aux, a, mid);
    pr = closestPair(points, aux, mid+1, b);
    double dr = dist(pr.first, pr.second);
    double dl = dist(pl.first, pl.second);
    double d = min(dl, dr);
    double midx = 0.5*(points[mid].x + points[mid+1].x);
    int kl=0, kr;
    point * s = lower_bound(&points[a], &points[mid+1], point(midx-d-EPS, 0.0), &compx);
    for(int i= a + (s-&points[a])/sizeof(point); i<=mid; i++){
        if (points[i].x >= midx - d - EPS) aux[kl++] = points[i];
    }
    kr = kl;
    for(int i=mid+1; i<=b; i++){
        if (points[i].x <= midx + d + EPS) aux[kr++] = points[i];
        else break;
    }
    sort(aux, aux+kl, &compy);
    sort(aux+kl, aux+kr, &compy);
    for(int i=0, k=kl; i<kl; i++){
        for(int j=k; j<kr; j++){
            if (aux[i].y - aux[j].y > d + EPS) k=j+1;
            else if (aux[j].y - aux[i].y > d + EPS) break;
            else if (dist(ans.first, ans.second) > dist(aux[i], aux[j])) ans = make_pair(aux[i], aux[j]);
        }
    }
    if (dr < dist(ans.first, ans.second)) ans = pr;
    if (dl < dist(ans.first, ans.second)) ans = pl;
    return ans;
}

pp closestPair(point* points, int n){
    point aux[n];
    sort(points, points+n, &compx);
    return closestPair(points, aux, 0, n-1);
}

int main(){
    int N;
    point points[MAXN];
    pp ans;
    double dans;
    while(scanf("%d", &N), N){
        for(int i=0; i<N; i++){
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }
        ans = closestPair(points, N);
        dans = dist(ans.first, ans.second);
        if (dans >= 10000.0) printf("INFINITY\n");
        else printf("%.4f\n", dans);
    }
    return 0;
}