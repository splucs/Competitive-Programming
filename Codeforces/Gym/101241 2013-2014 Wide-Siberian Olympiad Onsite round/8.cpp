#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=(a);i<(b);i++)
#define REP(i,a,b) for (int i=(a);i<=(b);i++)
#define PER(i,b,a) for (int i=(b);i>=(a);i--)

typedef pair<int, int> ii;
typedef long long ll;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    bool change = false;
    bool dimi = false;
    ll soma = 0;
    int n, m;
    string s, last;
    scanf("%d", &n);

    for(int i = 0; i<n; i++){
        scanf("%d", &m);
        if(m==0) continue;
        soma++;
        cin>>s;
        last = s;
        rep(j, 1, m){
            last = s;
            cin>>s;
            if(s!=last){
                if(last=="c") dimi = true;
                soma++;
                change = true;
            }
        }
    }
    if(dimi) soma--;
    if(n==1){
        if(soma<=2 || (soma==3 && s=="c")) cout<<soma<<endl;
        else cout<<-1<<endl; 
    }else
    cout<<soma<<endl;

}