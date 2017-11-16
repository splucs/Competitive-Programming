#include <bits/stdc++.h>

using namespace std;

double a, r;

double inter(double d){
    double theta = acos(d/(2*r));
    double a = sqrt(r*r - d*d/4);
    return 2*theta*r*r - a*d;

}

int main(){
    const double MY_PI = acos(-1);
    int n;
    int vet[1100];
    cin>>n>>r;

    for(int i = 0; i<n; i++){
        cin>>vet[i];
    }
    sort(vet, vet+n);
    double ans = n*MY_PI*r*r;
    for(int i = 1; i<n; i++){
        double x = vet[i]-vet[i-1];
        if(x<2*r){
            ans -= inter(x);
        }
    }
    printf("%.10f\n", ans);

}