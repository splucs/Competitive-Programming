#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n, a, b;
    vector<int> v;
    while(scanf(" %d", &n)!=EOF){
        v.push_back(n);
        nth_element(v.begin(), v.begin() + v.size()/2, v.end());
        a = *(v.begin() + v.size()/2);
        if (v.size()%2==0){
            nth_element(v.begin(), v.begin() + v.size()/2 - 1, v.end());
            b = *(v.begin() + v.size()/2 - 1);
            a = (a+b)/2;
        }
        printf("%d\n", a);
    }
    return 0;
}