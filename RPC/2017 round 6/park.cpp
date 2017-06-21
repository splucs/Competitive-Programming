#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int t,n,l,ccount,w,p;
    double area;
    char c;
    cin>>t;
    while (t-->0){
        cin>>n;
        ccount = p = w = 0;
        area = 0;
        for (int i=0;i<n;i++){
            cin>>c>>l;
            if (c=='C'||c=='S')area-=l*l;
            if (c=='C')ccount++;
            if (c=='T')area-=(double)l*l*sqrt(3)/4;
            p+=l;
            if (ccount==2)w = p,p=l,ccount = 3;
            if (ccount==4){
                    area+=p*w;
                ccount = 5;
            }
        }
        printf("%.4lf\n",area);
    }
}
