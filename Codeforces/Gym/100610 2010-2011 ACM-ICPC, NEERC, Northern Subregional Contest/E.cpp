#include <bits/stdc++.h>
using namespace std;

int main(){
    int num[10];
    int cnt = 0;
    freopen("explicit.in","r",stdin);
    freopen("explicit.out","w",stdout);

    for (int i=0;i<10;i++)cin>>num[i];
    for (int i=0;i<10;i++)for (int j=i+1;j<10;j++){
        if (num[i]==1||num[j]==1)cnt++;
        for (int k=j+1;k<10;k++)if (num[i]==1||num[j]==1||num[k]==1)cnt++;
    }

    cout<<cnt%2<<endl;
    fclose(stdin);
    fclose(stdout);
}