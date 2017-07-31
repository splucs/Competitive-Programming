#include <bits/stdc++.h>
using namespace std;

int main(){
    int mp[1000] = {};
    int n,m,a,ans;
    cin>>n>>m;
    for (int i=0;i<n;i++){
        cin>>a;
        ans = mp[0] = mp[0]+a;
        for (int j=1;j<m;j++){
            cin>>a;
            mp[j] = max(mp[j],mp[j-1])+a;
        }
        cout<<mp[m-1]<<" ";
    }
    cout<<endl;
}
