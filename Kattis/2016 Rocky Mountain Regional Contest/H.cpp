#include <bits/stdc++.h>
using namespace std;

int dp[201][201];
string s;

int numberPairs(int first,int last){
    if (first>=last)return 0;
    if (dp[first][last]!=-1)return dp[first][last];

    char val = s[first];
    int ans = numberPairs(first+1,last);
    for (int i=first+1;i<=last;i++){
        if (val==s[i]){
            ans = max(ans,1+numberPairs(first,i-1)+numberPairs(i+1,last));
        }
    }
    return dp[first][last] = ans;
}

int main(){
    int t;
    cin>>t;
    getline(cin,s);
    while (t-->0){
        getline(cin,s);
        memset(dp,-1,sizeof(dp));
        cout<<3*s.size()-2*numberPairs(0,s.size()-1)<<endl;
    }
}
