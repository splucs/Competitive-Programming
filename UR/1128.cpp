#include <cstdio>

bool adj[2009][2009];
bool vis[2009], visr[2009];
int N, M, V, W, P;

void dfs(int a){
    vis[a]=true;
    for(int i=0; i<N; i++){
        if (adj[a][i] && !vis[i]) dfs(i);
    }
}

void dfsr(int a){
    visr[a]=true;
    for(int i=0; i<N; i++){
        if (adj[i][a] && !visr[i]) dfsr(i);
    }
}

int main(){
    bool conexo;
    while(true){
        scanf("%d %d", &N, &M);
        if (N ==0 && M==0) break;
        for (int i=0; i<N; i++){
            vis[i]=visr[i]=false;
            for(int j=0; j<N; j++){
                adj[i][j]=false;
            }
        }
        for (int i=0; i<M; i++){
            scanf("%d %d %d", &V, &W, &P);
            V--;
            W--;
            if (P==1) adj[V][W]=true;
            else if (P==2) adj[V][W]=adj[W][V]=true;
        }
        dfs(0);
        dfsr(0);
        conexo=true;
        for (int i=0; i<N && conexo; i++){
            if (!vis[i] || !visr[i]) conexo=false;
        }
        if (conexo) printf("1\n");
        else printf("0\n");
    }
    return 0;
}
