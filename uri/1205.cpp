#include <cstdio>
#include <map>
using namespace std;

typedef struct node{
    int num;
    int pos;
    int dist;
    int snipers;
} node;
 
int heapSize;
node nodes[1009];
node* heap[1009];
 
int heapGetTop(){
    node* res = heap[0];
    res->pos=-1;
    node* aux;
    heap[0]=heap[--heapSize];
    heap[0]->pos=0;
    int k=0;
    while((2*k+1<heapSize && heap[k]->dist>heap[2*k+1]->dist) || (2*k+2<heapSize && heap[k]->dist>heap[2*k+2]->dist)){
        if (2*k+2<heapSize && heap[2*k+1]->dist > heap[2*k+2]->dist){
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
	int N, M, K, A, B, O, D;
	double P, prob;
	int p;
	map<int, map<int, bool> > adj;
	map<int, map<int, bool> >::iterator itl;
	map<int, bool>::iterator it;
	for (int i = 1; i <= 1000; ++i)
	{
		nodes[i].num=i;
	}
	while(scanf("%d %d %d %lf", &N, &M, &K, &P)!=EOF){
		heapSize=0;
		for (int i = 1; i <= N; ++i)
		{
			nodes[i].snipers=0;
			nodes[i].dist=-1;
		}
		for (int i = 0; i < M; ++i)
		{
			scanf("%d %d", &A, &B);
			adj[A][B]=adj[B][A]=true;
		}
		scanf("%d", &A);
		for (int i = 0; i < A; ++i)
		{
			scanf("%d", &B);
			nodes[B].snipers++;
		}
		scanf("%d %d", &O, &D);
		nodes[O].dist=nodes[O].snipers;
		heapAdd(O);
        while(heapSize>0){
            p = heapGetTop();
            itl = adj.find(p);
            if (itl==adj.end()) continue;
            for(it = itl->second.begin(); it!=itl->second.end(); it++){
                if(nodes[it->first].dist < 0){
                    nodes[it->first].dist = nodes[p].dist + nodes[it->first].snipers;
                    heapAdd(it->first);
                }
                else if(nodes[it->first].dist > nodes[it->first].snipers + nodes[p].dist){
                    nodes[it->first].dist = nodes[it->first].snipers + nodes[p].dist;
                    heapUpdate(it->first);
                }
            }
        }
        if (nodes[D].dist<0 || nodes[D].dist>K) prob=0.0;
        else {
        	prob=1.0;
	        for (int i = 0; i < nodes[D].dist; ++i)
	        {
	        	prob*=P;
	        }
        }
        printf("%.3f\n", prob);
        adj.clear();
	}
	return 0;
}