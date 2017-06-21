#include <cstdio>
#include <queue>
using namespace std;
int main()
{
    int x, y, pos[8][8], n1, n2, dist[64], cont;
    bool adj[64][64], vis[64];
    x=0;
    char a, b;
    for (int i=0; i<64; i++){
        for (int j=0; j<64; j++){
            adj[i][j]=false;
        }
    }
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            pos[i][j]=x++;
        }
    }
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (i+1<8 && j+2<8) adj[pos[i][j]][pos[i+1][j+2]]=true;
            if (i+1<8 && j-2>=0) adj[pos[i][j]][pos[i+1][j-2]]=true;
            if (i-1>=0 && j+2<8) adj[pos[i][j]][pos[i-1][j+2]]=true;
            if (i-1>=0 && j-2>=0) adj[pos[i][j]][pos[i-1][j-2]]=true;
            if (i+2<8 && j+1<8) adj[pos[i][j]][pos[i+2][j+1]]=true;
            if (i+2<8 && j-1>=0) adj[pos[i][j]][pos[i+2][j-1]]=true;
            if (i-2>=0 && j+1<8) adj[pos[i][j]][pos[i-2][j+1]]=true;
            if (i-2>=0 && j-1>=0) adj[pos[i][j]][pos[i-2][j-1]]=true;
        }
    }
    while (scanf(" %c%d %c%d", &a, &x, &b, &y)!=EOF){
        n1=pos[x-1][a-'a'];
        n2=pos[y-1][b-'a'];
        queue <int> fila;
        for (int i=0; i<64; i++){
            vis[i]=false;
            dist[i]=-1;
        }
        dist[n1]=0;
        fila.push(n1);
        vis[n1]=true;
        while(!fila.empty() && dist[n2]<0){
            cont = fila.front();
            fila.pop();
            for (int i=0; i<64; i++){
                if (adj[cont][i] && !vis[i]){
                    vis[i]=true;
                    dist[i]=dist[cont]+1;
                    fila.push(i);
                }
            }
        }
        printf("To get from %c%d to %c%d takes %d knight moves.\n", a, x, b, y, dist[n2]);
    }
    return 0;
}
