#include <cstdio>
#include <set>
using namespace std;
#define MAXN 100009

int main(){
    int cur, N, X, ans;
    while(scanf("%d", &N) != EOF){
        cur = 0;
        set<int> points;
        for (int i=0; i<N; i++){
            scanf("%d", &X);
            cur += X;
            points.insert(cur);
        }
        if (cur % 3 != 0){
            printf("0\n");
            continue;
        }
        else cur /= 3;
        set<int>::iterator it;
        ans = 0;
        for(it = points.begin(); it!=points.end(); it++){
            if (points.count(cur + (*it)) && points.count(2*cur + (*it))) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}

