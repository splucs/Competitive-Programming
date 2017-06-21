#include <cstdio>
#include <map>
using namespace std;

map<int, map<int, int> > adj;
bool called[109];
int A, B, C, altura, alturaC;

int dfs(int node, int h){
	called[node]=true;
	int x;
	if (node==C) alturaC=h;
	bool isway = (node==C);
	bool isentrance = (node==A);
	map<int, map<int, int> >::iterator itl;
	map<int, int>::iterator it;
	itl = adj.find(node);
	for(it = itl->second.begin(); it!=itl->second.end(); it++){
		if(!called[it->first]){
			x = dfs(it->first, h+1);
			if (x==1){
				isway=true;
			}
			if (x==2){
				isentrance=true;
			}
		}
	}
	if (isway && isentrance){
		altura=h;
		return 0;
	}
	if (isentrance) return 2;
	if (isway) return 1;
	return 0;
}

int main()
{
	int N, X, Y;
	while(scanf("%d %d %d %d", &N, &A, &B, &C)!=EOF){
		for (int i = 1; i < N; ++i)
		{
			scanf("%d %d", &X, &Y);
			adj[X][Y]=adj[Y][X]=0;
			called[i]=false;
		}
		called[N]=false;
		altura=alturaC=1;
		dfs(B, 0);
		printf("%.6f\n", (alturaC-altura)/((double)alturaC));
		adj.clear();
	}
	return 0;
}