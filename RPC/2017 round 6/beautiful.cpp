#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    long long int ans = 0,n,k;
    cin>>t;
    while(t-->0){
        cin>>n>>k;
        ans = 0;
        ans+=n+1;
        for (int i=0;i<k;i++){
            ans+=(n-i)*(1ll)*(i+1)*6;
        }
        cout<<ans<<endl;
    }
}
