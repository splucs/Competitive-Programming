#include <cstdio>
#include <map>
#include <queue>
using namespace std;

int main()
{
    int N, M, C, x;
    map<int, queue<int> >::iterator it;
    scanf("%d", &N);
    for (int cas = 0; cas<N; cas++){
        scanf("%d %d", &M, &C);
        map< int, queue<int> > hashmap;
        for (int i=0; i<C; i++){
            scanf("%d", &x);
            hashmap[x%M].push(x);
        }
        for (int i=0; i<M; i++){
            printf("%d -> ", i);
            it=hashmap.find(i);
            if (it!=hashmap.end())
                while(!it->second.empty()){
                    printf("%d -> ", it->second.front());
                    it->second.pop();
                }
            printf("\\\n");
        }
        if (cas!=N-1) printf("\n");
    }
    return 0;
}
