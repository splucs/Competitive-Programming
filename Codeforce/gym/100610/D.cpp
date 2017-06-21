#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("defense.in", "r", stdin);
    freopen("defense.out", "w", stdout);

    int maxx,maxy;
    int w,h,n,x[40002],y[40002];

    cin>>w>>h>>n;
    x[0]=y[0]=0;
    x[n+1]=w+1, y[n+1] = h+1;
    for (int i=1;i<=n;i++)cin>>x[i]>>y[i];
    sort(x,x+n+2);
    sort(y,y+n+2);
    maxx=maxy=-1;

    for (int i=1;i<=n+1;i++){
        maxx=max(maxx,x[i]-x[i-1]-1);
        maxy=max(maxy,y[i]-y[i-1]-1);
    }cout<<(long long int)maxx*maxy<<endl;

    fclose(stdin);
    fclose(stdout);
}