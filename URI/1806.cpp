#include <cstdio>
#include <map>
#define troca(x,y){int _x=x; x=y; y=_x;}
using namespace std;

int dist[10009], heap[10009], inv[10009], heapsize, I[10009];

int comp(int a, int b){
	return dist[heap[a]] - dist[heap[b]];
}

void sifup(int n){
	int k=2*n;
	if(k>heapsize) return;
	if(k<heapsize && comp(k,k+1)>0) k++;
	if(comp(n,k)>0){
		troca(heap[n], heap[k]);
		inv[heap[n]]=n;
		inv[heap[k]]=k;
		sifup(k);
	}
}

void sifdown(int n){
	int k=n/2;
	if(!k) return;
	if(comp(n,k)<0){
		troca(heap[n], heap[k]);
		inv[heap[n]]=n;
		inv[heap[k]]=k;
		sifdown(k);
	}
}

void addheap(int a){
	heap[++heapsize]=a;
	inv[a]=heapsize;
	sifdown(heapsize);
}

int getheap(){
	int k;
	if(heapsize<=0) return -1;
	k=heap[1];
	heap[1]=heap[heapsize--];
	inv[heap[1]]=1;
	sifup(1);
	return k;
}

int main(){
	int N, C, S, B, a, b, v, K, F, distKF, res=0;
	map<int, map<int, int> > rbino, rcrim;
	map<int, map<int, int> >::iterator itl;
	map<int, int>::iterator it;
	scanf("%d %d %d %d", &N, &C, &S, &B);
	for(int i=0; i<C; i++){
		scanf("%d %d %d", &a, &b, &v);
		if(rbino.count(a) && rbino[a].count(b) && rbino[a][b]<v) continue;
		rbino[a][b]=rbino[b][a]=v;
	}
	for(int i=0; i<S; i++){
		scanf("%d %d %d", &a, &b, &v);
		if(rcrim.count(a) && rcrim[a].count(b) && rcrim[a][b]<v) continue;
		rcrim[a][b]=rcrim[b][a]=v;
	}
	for(int i=0; i<B; i++){
		scanf("%d", I+i);
	}
	scanf("%d %d", &K, &F);
	for(int i=1; i<=N; i++){
		dist[i]=-1;
	}
	heapsize=0;
	dist[K]=0;
	addheap(K);
	while(heapsize>0){
		v = getheap();
		if(v==F) break;
		itl = rbino.find(v);
		if(itl==rbino.end()) continue;
		for(it = itl->second.begin(); it!=itl->second.end(); it++){
			if (dist[it->first]<0){
				dist[it->first] = dist[v] + it->second;
				addheap(it->first);
			}
			else if(dist[it->first] > dist[v] + it->second){
				dist[it->first] = dist[v] + it->second;
				sifdown(inv[it->first]);
			}
		}
	}
	distKF = dist[F];
	for(int i=1; i<=N; i++){
		dist[i]=-1;
	}
	heapsize=0;
	dist[F]=0;
	addheap(F);
	while(heapsize>0){
		v = getheap();
		itl = rbino.find(v);
		if(itl!=rbino.end()){
			for(it = itl->second.begin(); it!=itl->second.end(); it++){
				if (dist[it->first]<0){
					dist[it->first] = dist[v] + it->second;
					addheap(it->first);
				}
				else if(dist[it->first] > dist[v] + it->second){
					dist[it->first] = dist[v] + it->second;
					sifdown(inv[it->first]);
				}
			}
		}
		itl = rcrim.find(v);
		if(itl==rcrim.end()) continue;
		for(it = itl->second.begin(); it!=itl->second.end(); it++){
			if (dist[it->first]<0){
				dist[it->first] = dist[v] + it->second;
				addheap(it->first);
			}
			else if(dist[it->first] > dist[v] + it->second){
				dist[it->first] = dist[v] + it->second;
				sifdown(inv[it->first]);
			}
		}
	}
	for(int i=0; i<B; i++){
		if(dist[I[i]]<=distKF && dist[I[i]]>=0) res++;
	}
	printf("%d\n", res);
	return 0;
}