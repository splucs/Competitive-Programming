#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define swap(a, b) {int _a=a; a=b; b=_a;}
#define MAXN 509

struct cargo{
    vector<int> superiors;
    int age;
    int minage;
} cargos[MAXN];

int pos[MAXN], N, M, I, x, y;
bool checked[MAXN];

int minAge(int c){
    if (checked[c]) return cargos[c].minage;
    int ans = cargos[c].age;
    for(int i=0; i<(int)cargos[c].superiors.size(); i++){
        ans = min(ans, minAge(cargos[c].superiors[i]));
    }
    checked[c] = true;
    //printf("min(%d) = %d\n", c, ans);
    return cargos[c].minage = ans;
}

int main(){
    char c;
    while(scanf("%d %d %d", &N, &M, &I)!=EOF){
        for(int i=1; i<=N; i++){
            cargos[i].superiors.clear();
            pos[i]=i;
            scanf("%d", &cargos[i].age);
        }
        for(int i=0; i<M; i++){
            scanf("%d %d", &x, &y);
            cargos[y].superiors.push_back(x);
        }
        for(int q=0; q<I; q++){
            scanf(" %c", &c);
            if (c == 'P'){
                scanf("%d", &x);
                y = pos[x];
                memset(&checked, false, sizeof checked);
                int ans = 200;
                for(int i=0; i<(int)cargos[y].superiors.size(); i++){
                    ans = min(ans, minAge(cargos[y].superiors[i]));
                }
                if (ans > 100) printf("*\n");
                else printf("%d\n", ans);
            }
            else if (c == 'T'){
                scanf("%d %d", &x, &y);
                swap(pos[x], pos[y]);
                swap(cargos[pos[x]].age, cargos[pos[y]].age);
            }
        }
    }
}
