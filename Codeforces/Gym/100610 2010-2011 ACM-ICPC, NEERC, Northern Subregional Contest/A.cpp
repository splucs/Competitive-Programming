#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m,a;
    string ans = "";
    freopen("acm.in", "r", stdin);
    freopen("acm.out", "w", stdout);

    cin>>n>>m;
    for (int i=0;i<n;i++){
        cin>>a;
        if (i!=0)ans.push_back('*');
        ans.push_back('(');
        ans.push_back('1');
        ans.push_back('0');
        for (int j=0;j<a;j++){
            ans.push_back('-');
            ans.push_back('1');
        }ans.push_back(')');
    }ans.push_back('=');
    ans.push_back('0');
    for (int i=0;i<m;i++)cin>>a;
    cout<<ans<<endl;

    fclose(stdin);
    fclose(stdout);
}