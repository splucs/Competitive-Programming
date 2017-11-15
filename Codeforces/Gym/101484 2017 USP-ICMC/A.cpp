#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,x,wmin,wmax,a,ans = -1;
    wmin = 1000, wmax = -1;
    cin>>n>>x;
    for (int i=0;i<n;i++){
        cin>>a;
        if (a<wmin)wmin = a;
        if (a>wmax)wmax = a;
        if (a==x)ans = 1;
    }if (ans==-1&&wmin<x&&wmax>x)ans = 2;
    cout<<ans<<endl;
}