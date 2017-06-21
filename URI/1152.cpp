#include <cstdio>
#include <map>
using namespace std;

typedef struct edge{
	int num;
	long long int weight;
	int a;
	int b;
}edge;

edge edges[200000];
int heap[200000];
bool visited[200000];

int main(){
	int n, m, top, target, k, aux;
	long long int totalWeight;
	int heapSize;
	for (int i = 0; i < 200000; ++i)
	{
		edges[i].num=i;
	}
	map<int, map<int, edge*> > adj;
	map<int, map<int, edge*> >::iterator it;
	map<int, edge*>::iterator itl;
	while(true){
		scanf("%d %d", &n, &m);
		if (n==0 && m==0) break;
		totalWeight=0;
		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d %lld", &edges[i].a, &edges[i].b, &edges[i].weight);
			adj[edges[i].a][edges[i].b] = adj[edges[i].b][edges[i].a] = &edges[i];
			totalWeight+=edges[i].weight;
		}
		for (int i = 0; i < n; ++i)
		{
			visited[i]=false;
		}
		heapSize=0;
		it = adj.find(0);
		visited[0]=true;
		for (itl = it->second.begin(); itl!=it->second.end(); itl++)
		{
			if(!visited[itl->first]){
				heap[heapSize]=itl->second->num;
				k = heapSize++;
				while(edges[heap[k]].weight < edges[heap[(k-1)/2]].weight){
					aux = heap[k];
					heap[k]=heap[(k-1)/2];
					heap[(k-1)/2]=aux;
					k=(k-1)/2;
				}
			}
		}
		while(heapSize>0){
			top = heap[0];
			heap[0]=heap[--heapSize];
			k=0;
			while((2*k+2<heapSize && edges[heap[2*k+2]].weight < edges[heap[k]].weight)
			|| (2*k+1<heapSize && edges[heap[2*k+1]].weight < edges[heap[k]].weight))
			{
				if (2*k+2<heapSize && edges[heap[2*k+2]].weight < edges[heap[2*k+1]].weight){
					aux = heap[k];
					heap[k]=heap[2*k+2];
					heap[2*k+2]=aux;
					k=2*k+2;
				}
				else{
					aux = heap[k];
					heap[k]=heap[2*k+1];
					heap[2*k+1]=aux;
					k=2*k+1;
				}
			}
			if (visited[edges[top].a] && visited[edges[top].b]) continue;
			if (visited[edges[top].a]) target = edges[top].b;
			else target = edges[top].a;
			visited[target]=true;
			totalWeight -= edges[top].weight;
			it = adj.find(target);
			for (itl = it->second.begin(); itl!=it->second.end(); itl++)
			{
				if(!visited[itl->first]){
					heap[heapSize]=itl->second->num;
					k = heapSize++;
					while(edges[heap[k]].weight < edges[heap[(k-1)/2]].weight){
						aux = heap[k];
						heap[k]=heap[(k-1)/2];
						heap[(k-1)/2]=aux;
						k=(k-1)/2;
					}
				}
			}
		}
		printf("%lld\n", totalWeight);
		adj.clear();
	}
	return 0;
}