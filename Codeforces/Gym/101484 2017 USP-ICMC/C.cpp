#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

map<string,int> team;

bool comp(ii a1,ii a2){
    if (a1.first!=a2.first)return a1.first>a2.first;
    return a1.second<=a2.second;
}

int main(){
    int n,m,p,fails[201][15],t,ans=0,lastt=0;
    string name,s,ver;
    char prob;
    ii score[201],first = ii(0,0);

    cin>>n>>m>>p;
    lastt=0;
    for (int i=0;i<n;i++){
        cin>>name;
        team[name] = i;
        score[i] = ii(0,0);
        for (int j=0;j<p;j++)fails[i][j]=0;
    }
    for (int i=0;i<m;i++){
        cin>>s>>prob>>t>>ver;
        int index = team[s];
        prob-='A';
        if (fails[index][prob]==-1)continue;
        if (ver=="OK"){
            score[index] = ii(score[index].first+1,score[index].second+t+20*fails[index][prob]);
            fails[index][prob] = -1;
        }else{
            fails[index][prob]++;
        }
        if (comp(score[index],first)){
            first = score[index];
            if (lastt!=-1)ans+=t-lastt;
            if (comp(score[0],first))lastt = t;
            else lastt = -1;
        }
    }
    if (lastt!=-1)ans+=300-lastt;
    /*for (int i=0;i<n;i++){
        cout<<score[i].first<<" "<<score[i].second<<endl;
    }*/
    cout<<ans<<endl;
}