#include <bits/stdc++.h>

using namespace std;

double a, r;

int arred(double x){
    if(x - floor(x)<0.5) return floor(x);
    return ceil(x);
}

int vet[100];
int n;

bool solvre(int ans){
    set<int> sat;
    sat.clear();
    double x = 100.00/ans;
    for(int i = 0; i<=ans; i++){
        sat.insert(arred(i*x));
    }
    for(int i = 0; i<n; i++){
        if(sat.find(vet[i])==sat.end()){
            // cout<<x<<" "<<vet[i]<<endl;
            return false;
        }
    }
    return true;
}

int main(){
    cin>>n;
    for(int i = 0; i<n; i++){
        scanf("%d", &vet[i]);
    }
    for(int i = 1; i<=100; i++){
        if(solvre(i)){
            cout<<i<<endl;
            break;
        }
    }

}