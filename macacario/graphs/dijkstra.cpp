/*
 * Solução do problema http://www.spoj.com/submit/EZDIJKST/
 */

#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#define MAXN 100009
#define swap(a,b){ int _x=a; a=b; b=_x; }
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

vector<ii> adjList[MAXN];
int dist[MAXN], N;

//função de prioridade da heap, equivale a 'menor que'
bool comp(int a, int b){
	return dist[a] < dist[b];
}

class Heap{
private:
	int heap[MAXN];
	int inv[MAXN];
	int heapsize;
	void sifup(int n){
		int k = n << 1;
		while (k <= heapsize){
			if (k < heapsize && comp(heap[k+1], heap[k])) k++;
			if (comp(heap[k], heap[n])){
				swap(heap[n], heap[k]);
				inv[heap[n]]=n;
				n = inv[heap[k]]=k;
				k <<= 1;
			}
			else break;
		}
	}
	void sifdown(int n){
		int k = n >> 1;
		while (k){
			if (comp(heap[n], heap[k])){
				swap(heap[n], heap[k]);
				inv[heap[n]]=n;
				n = inv[heap[k]]=k;
				k >>= 1;
			}
			else break;
		}
	}
public:
	Heap(){ heapsize = 0; }
	void clear(){ heapsize = 0; }
	bool empty(){ return heapsize==0; }
	void update(int n){
		if (inv[n]>heapsize || heap[inv[n]]!=n) return;
		sifup(inv[n]);
		sifdown(inv[n]);
	}
	void push(int n){
		heap[++heapsize] = n;
		inv[n] = heapsize;
		sifdown(heapsize);
	}
	bool count(int n){
		int k = inv[n];
		return k <= heapsize && heap[k] == n;
	}
	int top(){
		if (heapsize <=0) return -1;
		return heap[1];
	}
	void pop(){
		if (heapsize<=0) return;
		heap[1] = heap[heapsize--];
		inv[heap[1]] = 1;
		sifup(1);
	}
};

int dijkstra(int s, int t){
	memset(&dist, -1, sizeof dist);
	dist[s]=0;
	int u, v, w;
	Heap heap; heap.push(s);
	while(!heap.empty()){
		u = heap.top();
		if (u==t) break;
		heap.pop();
		for(int i=0; i<(int)adjList[u].size(); i++){
			v = adjList[u][i].first;
			w = adjList[u][i].second;
			if (dist[v] < 0 || dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				if (heap.count(v)) heap.update(v);
				else heap.push(v);
			}
		}
	}
	return dist[t];
}

int main(){
	int T, M, X, Y, H, O, D;
	scanf("%d", &T);
	for(int t=0; t<T; t++){
		scanf("%d %d", &N, &M);
		N++;
		for(int i=0; i<N; i++) adjList[i].clear();
		for(int i=0; i<M; i++){
			scanf("%d %d %d", &X, &Y, &H);
			adjList[X].push_back(ii(Y, H));
		}
		scanf("%d %d", &O, &D);
		H = dijkstra(O, D);
		if (H>=0) printf("%d\n", H);
		else printf("NO\n");
	}
	return 0;
}
