#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define MAXN 1009

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN];
bool vis[MAXN];
int m, n;
///Vértices enumerados de 1 a m em U e de 1 a n em V!!!!

bool dfs(int u)
{
    vis[u] = true;
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i){
        v = adjU[u][i];
        if (!vis[pairV[v]] && dfs(pairV[v])){
            pairV[v] = u; pairU[u] = v;
            return true;
        }
    }
    return false;
}

//O(E*V)
int hungarian()
{
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    for (int u = 1; u <= m; u++){
        memset(&vis, false, sizeof vis);
        if (pairU[u]==0 && dfs(u))
            result++;
    }
    return result;
}

int main()
{
    int T, lu[MAXN], lv[MAXN];
    scanf("%d", &T);
    for(int caseNo=1; caseNo <= T; caseNo++){
        scanf("%d", &m);
        for(int i=1; i<=m; i++){
            scanf("%d", lu+i);
            adjU[i].clear();
        }
        scanf("%d", &n);
        for(int i=1; i<=n; i++){
            scanf("%d", lv+i);
            for(int j=1; j<=m; j++){
                if (lu[j] != 0 && lv[i]%lu[j] == 0) adjU[j].push_back(i);
                if (lu[j] == 0 && lv[i] == 0) adjU[j].push_back(i);
            }
        }
        printf("Case %d: %d\n", caseNo, hungarian());
    }
 
    return 0;
}
