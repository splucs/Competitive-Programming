#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,qtt;
    string a;
    double val[500],ans;
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>a>>val[i];
    }sort(val,val+n);
    ans = 0;

    for (int i=n-1;i>=0;i--){
        qtt = n-i;
        ans += val[i]*qtt;
    }
    printf("%.4lf\n",ans);
}