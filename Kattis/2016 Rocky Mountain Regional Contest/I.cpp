#include <bits/stdc++.h>
using namespace std;
typedef pair<int, string> ds;

bool isNumber(string a){
    for (int i=0;i<a.size();i++){
        if (a[i]<'0'||a[i]>'9')return false;
    }
    return true;
}

int main(){
    int n,qtt;
    ds val[20];
    string a,b;
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>a>>b;
        if (isNumber(a)){
            val[i] = ds(atoi(a.c_str()),b);
        }else{
            val[i] = ds(2*atoi(b.c_str()),a);
        }
    }
    sort(val,val+n);
    for (int i=0;i<n;i++){
        cout<<val[i].second<<endl;
    }
}