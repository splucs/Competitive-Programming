#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    int pos = -1,cnt=0,redk,redn,acum;
    redk=redn=0;
    k--;

    while (n>0){
        cnt++;
        acum = n-pos-1;
        pos=pos+m;

        if (pos>=n){
            pos=m-acum-1;
            n-=redn, k-=redk;
            pos=pos%n;
            redn=redk=0;
        }
        if (pos==k)break;
        if (pos<k){
            redk++;
        }redn++;
        //cout<<pos<<" "<<n<<" "<<k<<endl;
    }
    cout<<cnt<<endl;
}