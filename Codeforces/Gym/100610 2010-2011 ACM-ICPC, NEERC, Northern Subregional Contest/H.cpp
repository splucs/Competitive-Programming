#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int main(){
    freopen("horrible.in", "r", stdin);
    freopen("horrible.out", "w", stdout);

    int n,qtt;
    ii ans[30000];
    cin>>n;
    qtt=0;
    if (n!=1)ans[qtt++]=ii(2,-1);
    for (int i=1;i<n;i++){
        ans[qtt++]=ii(i,0);
        for (int j=1;j<=n;j++){
            if(j!=i+1)ans[qtt++]=ii(j,-(i+1));
            if (j!=i)ans[qtt++]=ii(j,i);
        }
    }ans[qtt++]=ii(n,0);
    if (n!=1)ans[qtt++]=ii(1,n);
    cout<<qtt<<endl;
    for (int i=0;i<qtt;i++)cout<<ans[i].first<<" "<<ans[i].second<<endl;

    fclose(stdin);
    fclose(stdout);
}