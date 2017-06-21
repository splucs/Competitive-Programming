#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for (int i=(a);i<(b);i++)
#define REP(i,a,b) for (int i=(a);i<=(b);i++)
#define PER(i,b,a) for (int i=(b);i>=(a);i--)

typedef pair<int, int> ii;
typedef long long ll;

int main(){
    int n;
    int vet[1100] = {0};
    ii pd[1100];
    scanf("%d", &n);
    rep(i, 0, n){
        pd[i] = ii(0, 0);
        cin>>vet[i];
    }
    sort(vet, vet+n);
    int maior = -1;
    pd[0] = ii(1, vet[0]);
    rep(i, 0, n){
        PER(j, i-1, 0){
            if(vet[i]>pd[j].second){
                if(pd[i].first<pd[j].first+1 || 
                    (pd[i].first==pd[j].first+1 && pd[i].second>pd[j].second+vet[i])){
                    pd[i] = ii(pd[j].first+1, pd[j].second+vet[i]);
                    maior = max(maior, pd[i].first);
                }
            }
        }
        // cout<<pd[i].first<<" ";
    }
    // cout<<endl;
    cout<<maior<<endl;


}