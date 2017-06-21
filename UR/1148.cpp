#include <cstdio>
#include <map>
using namespace std;

typedef struct node{
	int num;
	int pos;
	int dist;
} node;

int heapSize;
node nodes[509];
node* heap[509];

int heapGetTop(){
	node* res = heap[0];
	node* aux;
	heap[0]=heap[--heapSize];
	heap[0]->pos=0;
	int k=0;
	while((2*k+1<heapSize && heap[k]->dist>heap[2*k+1]->dist) || (2*k+2<heapSize && heap[k]->dist>heap[2*k+2]->dist)){
		if (2*k+2<heapSize && heap[2*k+2]->dist < heap[k]->dist && heap[2*k+1]->dist > heap[2*k+2]->dist){
			aux = heap[2*k+2];
			heap[2*k+2]=heap[k];
			heap[k]=aux;
			heap[k]->pos=k;
			k=2*k+2;
			heap[k]->pos=k;
		}
		else{
			aux = heap[2*k+1];
			heap[2*k+1]=heap[k];
			heap[k]=aux;
			heap[k]->pos=k;
			k=2*k+1;
			heap[k]->pos=k;
		}
	}
	return res->num;
}

void heapAdd(int n){
	heap[heapSize] = &nodes[n];
	heap[heapSize]->pos = heapSize;
	int k = heapSize;
	heapSize++;
	node* aux;
	while(heap[k]->dist < heap[(k-1)/2]->dist){
		aux = heap[(k-1)/2];
		heap[(k-1)/2]=heap[k];
		heap[k]=aux;
		heap[k]->pos=k;
		k=(k-1)/2;
		heap[k]->pos=k;
	}
}

void heapUpdate(int n){
	int k = nodes[n].pos;
	node* aux;
	while(heap[k]->dist < heap[(k-1)/2]->dist){
		aux = heap[(k-1)/2];
		heap[(k-1)/2]=heap[k];
		heap[k]=aux;
		heap[k]->pos=k;
		k=(k-1)/2;
		heap[k]->pos=k;
	}
}

int main()
{
	int N, E, X, Y, H, K, O, D;
	int p, d;
	map<int, map<int, int> > adj;
	map<int, int>::iterator it;
	for (int i = 1; i <= 500; ++i)
	{
		nodes[i].num=i;
	}
	while(true){
		scanf("%d %d", &N, &E);
		if (N==0 && E==0) break;
		for (int i = 0; i < E; ++i)
		{
			scanf("%d %d %d", &X, &Y, &H);
			if(adj.count(Y) && adj[Y].count(X)){
				adj[X][Y]=adj[Y][X]=0;
			}
			else adj[X][Y]=H;
		}
		scanf("%d", &K);
		for (int i = 0; i < K; ++i)
		{
			heapSize=0;
			for (int i = 1; i <= N; ++i)
			{
				nodes[i].dist=-1;
			}
			scanf("%d %d", &O, &D);
			nodes[O].dist=0;
			heapAdd(O);
			while(heapSize>0){
				p = heapGetTop();
				if (!adj.count(p)) continue;
				for(it = adj[p].begin(); it!=adj[p].end(); it++){
					if(nodes[it->first].dist < 0){
						nodes[it->first].dist = nodes[p].dist + it->second;
						heapAdd(it->first);
					}
					else if(nodes[it->first].dist > it->second + nodes[p].dist){
						nodes[it->first].dist = nodes[p].dist + it->second;
						heapUpdate(it->first);
					}
				}
			}
			if (nodes[D].dist<0) printf("Nao e possivel entregar a carta\n");
			else printf("%d\n", nodes[D].dist);
		}
		printf("\n");
		adj.clear();
	}
	return 0;
}