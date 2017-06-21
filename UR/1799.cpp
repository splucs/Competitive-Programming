#include <cstdio>
#include <queue>
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	int P, L;
	scanf("%d %d", &P, &L);
	string a, b;
	map<string, map<string, bool> > adj;
	map<string, map<string, bool> >::iterator itl;
	map<string, bool>::iterator it;
	map<string, int> dist;
	for(int i=0; i<L; i++){
		cin >> a >> b;
		adj[a][b]=adj[b][a]=true;
	}
	dist["*"]=0;
	queue<string> fila;
	fila.push("*");
	while(!fila.empty()){
		a = fila.front();
		fila.pop();
		itl = adj.find(a);
		if(itl==adj.end()) continue;
		for(it = itl->second.begin(); it!=itl->second.end(); it++){
			if(!dist.count(it->first)){
				dist[it->first] = dist[a]+1;
				fila.push(it->first);
			}
		}
	}
	printf("%d\n", dist["Entrada"]+dist["Saida"]);
	return 0;
}