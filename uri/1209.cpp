#include <cstdio>
#include <map>
#include <queue>
using namespace std;

map< int, map<int, bool> > adj;

int main()
{
	int N, M, K, A, B;
	int grades[1001], cont, p;
	queue<int> fila;
	map< int, map<int, bool> >::iterator itl;
	map<int, bool>::iterator it;
	while(scanf("%d %d %d", &N, &M, &K)!=EOF){
		for (int i = 1; i <= N; ++i)
		{
			grades[i]=0;
		}
		for (int i = 0; i < M; ++i)
		{
			scanf("%d %d", &A, &B);
			adj[A][B]=adj[B][A]=true;
			grades[A]++;
			grades[B]++;
		}
		cont = N;
		for (int i = 1; i <= N; ++i)
		{
			if (grades[i]<K){
				fila.push(i);
				grades[i]=-1;
			}
		}
		while(!fila.empty()){
			cont--;
			p=fila.front();
			fila.pop();
			itl = adj.find(p);
			if (itl==adj.end()) continue;
			for(it = itl->second.begin(); it!=itl->second.end(); it++){
				if (grades[it->first]<0) continue;
				else{
					grades[it->first]--;
					if (grades[it->first]<K){
						fila.push(it->first);
						grades[it->first]=-1;
					}
				}
			}
		}
		adj.clear();
		if (cont==0) printf("0");
		for (int i = 1; i <= N; ++i)
		{
			if (grades[i]>=0){
				cont--;
				printf("%d", i);
				if (cont>0) printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}