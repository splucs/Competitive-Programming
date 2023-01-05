#include <bits/stdc++.h>

using namespace std;
    
int main(){
    int totR = 0, totT = 0;
    int theo, rita, d;
    int t = 2;
    cin>>d>>rita>>theo;
    int r = t+d;
    for(int i = 1; i<d; i++){
        totR += i+3;
    }
    // cout<<totR<<endl;

    while(totR + totT != rita + theo){
        t++;
        totT += t;
        r++;
        totR += r;
        // cout<<t<<" "<<totT<<" "<<r<<" "<<totR<<endl;
    }
    cout<<rita-totR<<endl;

}