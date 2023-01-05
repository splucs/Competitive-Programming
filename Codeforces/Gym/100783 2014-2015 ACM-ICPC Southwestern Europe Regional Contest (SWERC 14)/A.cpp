#include <bits/stdc++.h>
using namespace std;

string words[10];
char letters[10];
map<char,int> value;
bool used[10]={};
int n,ans=0,l=0,maxsize=0;

int recurse(int pos,int digit,int res){
    int d = words[pos].size()-digit-1;
    int ans = 0;

    if (digit==maxsize){
        if (res==0)return 1;
        else return 0;
    }

    if (pos==n-1){
        if (d==0&&res%10==0)return 0;
        if (value[words[pos][d]]==-1){
            if (used[res%10])return 0;
            used[res%10]=true;
            value[words[pos][d]] = res%10;
            ans+=recurse(0,digit+1,res/10);
            used[res%10]=false;
            value[words[pos][d]]=-1;
            return ans;
        }
        if (value[words[pos][d]]!=res%10)return 0;
        return recurse(0,digit+1,res/10);
    }

    if (d>=0){
        if (value[words[pos][d]]==-1){
            for (int i=0;i<=9;i++){
                if ((i==0&&d==0)||used[i])continue;
                used[i]=true;
                value[words[pos][d]] = i;
                ans+=recurse(pos+1,digit,res+i);
                used[i]=false;
            }
            value[words[pos][d]]=-1;
            return ans;
        }
        else {
            if (d==0&&value[words[pos][d]]==0)return 0;
            return recurse(pos+1,digit,res+value[words[pos][d]]);
        }
    }
    return recurse(pos+1,digit,res);
}

int main(){
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>words[i];
        maxsize = max((int)words[i].length(),maxsize);
        for (int j=0;j<words[i].length();j++)value[words[i][j]]=-1;
    }
    for (map<char,int>::iterator it = value.begin();it!=value.end();it++)letters[l++] = it->first;
    printf("%d\n",recurse(0,0,0));
}