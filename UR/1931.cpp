#include <cstdio>
#include <map>
using namespace std;

map<int, map<int, int> > adj;
int dist[20009], C, V;
int heap[20009], inv[20009], heapsize;

int comp(int a, int b){
	return dist[heap[a]] - dist[heap[b]];
}

void sifup(int n){
	int k = 2*n, aux;
	if (k>heapsize) return;
	if (k<heapsize && comp(k,k+1)>0) k++;
	if(comp(n,k)>0){
		aux = heap[n];
		heap[n]=heap[k];
		heap[k]=aux;
		inv[heap[n]]=n;
		inv[heap[k]]=k;
		sifup(k);
	}
}

void sifdown(int n){
	int k = n/2, aux;
	if(!k) return;
	if(comp(n,k)<0){
		aux = heap[n];
		heap[n]=heap[k];
		heap[k]=aux;
		inv[heap[n]]=n;
		inv[heap[k]]=k;
		sifdown(k);
	}
}

void addHeap(int a){
	heap[++heapsize] = a;
	inv[a]=heapsize;
	sifdown(heapsize);
}

int getHeap(){
	int k;
	if(heapsize<=0) return -1;
	k = heap[1];
	heap[1] = heap[heapsize--];
	inv[heap[1]]=1;
	sifup(1);
	return k;
}

int main()
{
	int x, y, z;
	heapsize=0;
	scanf("%d %d", &C, &V);
	for(int i=0; i<V; i++){
		scanf("%d %d %d", &x, &y, &z);
		adj[x][y+C]=adj[y][x+C]=adj[x+C][y]=adj[y+C][x]=z;
	}
	for(int i=1; i<=2*C; i++){
		dist[i]=-1;
	}
	dist[1]=0;
	addHeap(1);
	map<int, map<int, int> >::iterator itl;
	map<int, int>::iterator it;
	while(heapsize>0){
		x = getHeap();
		itl = adj.find(x);
		if (itl==adj.end()) continue;
		for(it = itl->second.begin(); it!=itl->second.end(); it++){
			if (dist[it->first]<0){
				dist[it->first] = dist[x] + it->second;
				addHeap(it->first);
			}
			else if (dist[it->first] > dist[x] + it->second){
				dist[it->first] = dist[x] + it->second;
				sifdown(inv[it->first]);
			}
		}
		if (x==C) break;
	}
	printf("%d\n", dist[C]);
	return 0;
}
