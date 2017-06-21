#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;

typedef struct node{
	int h;
	map<int, node*> sons;
	node* parent;
} node;

void dfs(node* n, int height){
	map<int,node*>::iterator it;
	int p=-1;
	for(it = n->sons.begin(); it!=n->sons.end(); it++){
		if(it->second!=n->parent){
			it->second->parent = n;
			dfs(it->second, height+1);
		}
		else p = it->first;
	}
	n->sons.erase(p);
	n->h = height;
}

int LCA(node* a, node* b){
	int res=0;
	while(a->h > b->h){
		a=a->parent;
		res++;
	}
	while(a->h < b->h){
		b=b->parent;
		res++;
	}
	while(a!=b){
		b=b->parent;
		a=a->parent;
		res+=2;
	}
	return res;
}

int main()
{
	int N, x, y, res=0;
	scanf("%d", &N);
	node nodes[N];
	int pos[N/2][2];
	for(int i=0; i<N/2; i++){
		pos[i][0]=pos[i][1]=-1;
	}
	for(int i=0; i<N; i++){
		scanf("%d", &x);
		x--;
		if (pos[x][0]<0) pos[x][0]=i;
		else pos[x][1]=i;
	}
	for(int i=0; i<N-1; i++){
		scanf("%d %d", &x, &y);
		nodes[x-1].sons[y-1] = &nodes[y-1];
		nodes[y-1].sons[x-1] = &nodes[x-1];
	}
	nodes[0].parent=NULL;
	dfs(&nodes[0], 0);
	for(int i=0; i<N/2; i++){
		res+=LCA(&nodes[pos[i][0]], &nodes[pos[i][1]]);
	}
	printf("%d\n", res);
	return 0;
}
