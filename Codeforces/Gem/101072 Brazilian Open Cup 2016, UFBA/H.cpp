#include <cstdio>
#include <algorithm>
using namespace std;
#define WMAX 1000000009
typedef pair<int,int> ii;

int valx[100009],valy[100009];
ii coordmax,coordmin;

int main(){
    int xmax,ymax,xmin,ymin;
    int n,p,x0,y0;
    ii u;
    long long int x,y;
    scanf("%d",&n);
    xmax=-WMAX,xmin=WMAX;
    ymax=-WMAX,ymin=WMAX;
    for (int i=0;i<n;i++){
        scanf("%d",&p);
        for (int j=0;j<p;j++){
            scanf("%d%d",&valx[j],&valy[j]);
        }sort(valx,valx+p);
        sort(valy,valy+p);
        u = ii(valx[p/2],valy[p/2]);
        coordmax = u;
        if (p%2==1)coordmin = u;
        else coordmin = ii(valx[p/2-1],valy[p/2-1]);

        //printf("%d %d\n%d %d\n",coordmin.first,coordmin.second,coordmax.first,coordmax.second);

        xmax=max(coordmin.first,xmax);
        ymax=max(coordmin.second,ymax);
        xmin=min(coordmax.first,xmin);
        ymin=min(coordmax.second,ymin);

        //printf("%d %d\n%d %d\n\n",xmin,ymin,xmax,xmin);
    }x = (xmax-xmin);
    y = (ymax-ymin);
    printf("%I64d\n",x*y);
    //scanf("%d",&n);
}