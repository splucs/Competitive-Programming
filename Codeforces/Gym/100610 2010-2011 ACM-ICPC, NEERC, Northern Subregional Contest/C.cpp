#include <bits/stdc++.h>
using namespace std;
#define MAX_INT 1000000009

vector<int> a,b,c,cycle,q;

int findCycle(int d,int last,int qtt){
    if (d==last){
        c[d]=qtt;
        if(cycle[qtt]==-1){
            int kmin = last;
            for (int i=0;i<(int)q.size();i++){
                if (qtt%q[i]==0)kmin = min(kmin,cycle[q[i]]);
            }
            cycle[qtt]=kmin;
            q.push_back(qtt);
        }
        return qtt;
    }
    c[d]=findCycle(b[d],last,qtt+1);
    return c[d];
}

int main(){
    freopen("commuting.in", "r", stdin);
    freopen("commuting.out", "w", stdout);

    int n;
    cin>>n;
    b.assign(n+1,0);
    a.assign(n+1,-1);
    c.assign(n+1,-1);
    cycle.assign(n+1,-1);
    for(int i=1;i<=n;i++)cin>>b[i];
    for (int i=1;i<=n;i++){
        if (c[i]!=-1)continue;
        findCycle(b[i],i,1);
    }
    for (int i=1;i<=n;i++){
        if (a[i]!=-1)continue;
        a[i]=cycle[c[i]];
        for (int j=b[i],k=b[cycle[c[i]]];j!=i;j=b[j],k=b[k]){
            a[j] = k;
        }
    }
    for (int i=1;i<=n;i++)cout<<a[i]<<" ";
    cout<<endl;
    fclose(stdin);
    fclose(stdout);
}