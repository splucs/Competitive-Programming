#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define INF 1000000000

struct line{
    double x,y,dx,dy;
    line(){}
    line(double _x,double _y, double _dx,double _dy){
        x = _x, y = _y, dx = _dx, dy = _dy;
    }
};

double slope(line a){
    if (abs(a.dx)<EPS)return INF;
    return a.dy/a.dx;
}

double pointy(line a) {
    if (abs(a.dx)<EPS) return INF;  
    return a.y - slope(a)*a.x;
}

bool sortLine(line a,line b){
    if (abs(slope(a)-slope(b))>EPS)
        return slope(a)<slope(b);
    if (abs(pointy(a) - pointy(b)) > EPS) 
        return pointy(a)<pointy(b);
    if (abs(a.x-b.x)>EPS)
        return a.x<b.x;
    return a.y<b.y;
}

bool inLine(line a,double x,double y){
    double ymin = min(a.y,a.y+a.dy);
    double ymax = max(a.y,a.y+a.dy);
    return (x>=a.x&& x<=a.x+a.dx)&&
        (y>=ymin && y<=ymax) && (abs((a.dy) * (a.x - x) - (a.y - y) * (a.dx)) < EPS);

}

bool intersects(line a,line b){
    if (abs(slope(a)-slope(b))>EPS)
        return false;
    return inLine(a,b.x,b.y) || inLine(a, b.x + b.dx, b.y + b.dy);
}

bool contains(line a, line b) {
    if (abs(slope(a)-slope(b))>EPS)
        return false;
    return inLine(a,b.x,b.y) && inLine(a, b.x + b.dx, b.y + b.dy);

}
int main(){
    int n,cnt;
    line l[10000],prev;
    double x1,y1,x2,y2,ax,ay;

    while (cin>>n&&n!=0){
        for (int i=0;i<n;i++){
            cin>>x1>>y1>>x2>>y2;
            if (x2<x1 || (x2 == x1 && y2<y1)){
                ax = x2,ay = y2;
                x2 = x1, y2 = y1;
                x1 = ax, y1 = ay;
            }
            l[i] = line(x1,y1,x2-x1,y2-y1);
        }
        sort(l,l+n,sortLine);
        prev = l[0],cnt = 1;
        for (int i=1;i<n;i++){
            //cout<<prev.x<<" "<<prev.y<<" "<<prev.dx<<" "<<prev.dy<<endl;
            if (contains(prev, l[i])) {}
            else if (intersects(prev,l[i])) {
                prev = l[i];
            } else {
                cnt++;
                prev = l[i];
            }
        }
        //cout<<prev.x<<" "<<prev.y<<" "<<prev.dx<<" "<<prev.dy<<endl;
        cout<<cnt<<endl;
    }
}
/* 
3
0.0 0.0 10.0 10.0
1.0 1.01 2.0 2.01
3.0 3.0 4.0 4.0
3
0.0 -1.0 0.0 -3.0
0.0 -2.0 0.0 -2.5
0.0 -3.0 0.0 -4.0
*/