#include <cstdio>
#include <map>
using namespace std;

int main()
{
    int N, M, C, K, x, y, p, heapSize;
    long long int Dmin;
    long long int Cdist[250], dist[250];
    bool vis[250];
    map< int, map<int, long long int> > adj;
    map<int, long long int>::iterator it;
    map<int, long long int>::iterator itl;
    int heap[250], pos[250];
    bool isheap[250];
    while(true){
        scanf("%d %d %d %d", &N, &M, &C, &K);
        if (N==0 && M==0 && C==0 && K==0) break;
        adj.clear();
        for (int i=0; i<M; i++){
            scanf("%d %d %d", &x, &y, &p);
            adj[x][y] = adj[y][x] = p;
        }
        Cdist[C-1]=0;
        for (int i=C-2; i>=0; i--){
            Cdist[i]=Cdist[i+1] + adj[i][i+1];
        }
        if (K<C){
            printf("%d\n", Cdist[K]);
            continue;
        }
        for (int i=0; i<N; i++){
            dist[i]=-1;
            vis[i]=false;
            isheap[i]=false;
            heap[i]=-1;
            pos[i]=-1;
        }
        dist[K]=0;
        p=K;
        Dmin=-1;
        x=0;
        heapSize=0;
        do{
            vis[p]=true;
            if (p<C){
                if(Dmin<0 || Dmin> Cdist[p]+dist[p])
                    Dmin = Cdist[p]+dist[p];
            }
            else for (it=adj[p].begin(), itl=adj[p].end(); it!=itl; it++){
                if (!vis[it->first] && (dist[it->first]<0 || dist[it->first] > dist[p] + it->second))
                {
                    dist[it->first] = dist[p] + it->second;
                    if (isheap[it->first]){
                        x=pos[it->first];
                    }
                    else{
                        isheap[it->first]=true;
                        x = heapSize++;
                        heap[x]=it->first;
                        pos[heap[x]]=x;
                    }
                    while (dist[heap[(x-1)/2]]>dist[heap[x]]){
                        y = heap[(x-1)/2];
                        heap[(x-1)/2] = heap[x];
                        heap[x] = y;
                        pos[heap[x]]=x;
                        x = (x-1)/2;
                        pos[heap[x]]=x;
                    }
                }
            }
            if (heapSize==0) break;
            else{
                p=heap[0];
                heap[0]=heap[--heapSize];
                x=0;
                while((2*x+1<heapSize && dist[heap[x]] > dist[heap[2*x+1]]) || (2*x+2<heapSize && dist[heap[x]] > dist[heap[2*x+2]])){
                    if (2*x+2<heapSize && dist[heap[2*x+2]]<dist[heap[2*x+1]]){
                        y = heap[2*x+2];
                        heap[2*x+2] = heap[x];
                        heap[x] = y;
                        pos[heap[x]]=x;
                        x = 2*x+2;
                        pos[heap[x]]=x;
                    }
                    else{
                        y = heap[2*x+1];
                        heap[2*x+1] = heap[x];
                        heap[x] = y;
                        pos[heap[x]]=x;
                        x = 2*x+1;
                        pos[heap[x]]=x;
                    }
                }
            }
        }while(true);
        printf("%lld\n", Dmin);
    }
    return 0;
}
