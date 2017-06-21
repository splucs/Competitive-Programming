#include <cstdio>
#include <cstring>

typedef struct node{
	int sons[2];
	bool endHere[2];
}node;

node nodes[1609];
int nNodes, wordSize;
char inserting[59];
bool called[1609][1609];

void insert(int no, int pos, int conjunto){
	if (pos==wordSize){
		nodes[no].endHere[conjunto]=true;
		return;
	}
	int next = (inserting[pos]=='1'?1:0);
	if (nodes[no].sons[next]<0){
		nodes[no].sons[next]=++nNodes;
		nodes[nNodes].sons[0]=nodes[nNodes].sons[1]=-1;
		nodes[nNodes].endHere[0]=nodes[nNodes].endHere[1]=false;
	}
	insert(nodes[no].sons[inserting[pos]-'0'], pos+1, conjunto);
}

bool solve(int no0, int no1){
	if(no0<0 || no1<0 || called[no0][no1]) return false;
	called[no0][no1]=true;
	if (nodes[no0].endHere[0] && nodes[no1].endHere[1]) return true;
	bool res=false;
	if (nodes[no0].endHere[0]){
		res = (res || solve(nodes[0].sons[0], nodes[no1].sons[0]));
		res = (res || solve(nodes[0].sons[1], nodes[no1].sons[1]));
	}
	if (nodes[no1].endHere[1]){
		res = (res || solve(nodes[no0].sons[0], nodes[0].sons[0]));
		res = (res || solve(nodes[no0].sons[1], nodes[0].sons[1]));
	}
	res = (res || solve(nodes[no0].sons[0], nodes[no1].sons[0]));
	res = (res || solve(nodes[no0].sons[1], nodes[no1].sons[1]));
	return res;
}

int main()
{
	int N0, N1;
	while(scanf("%d %d", &N0, &N1)!=EOF){
		nNodes=0;
		nodes[nNodes].sons[0]=nodes[nNodes].sons[1]=-1;
		nodes[nNodes].endHere[0]=nodes[nNodes].endHere[1]=false;
		for(int i=0; i<N0; i++){
			scanf(" %s", inserting);
			wordSize = strlen(inserting);
			insert(0, 0, 0);
		}
		for(int i=0; i<N1; i++){
			scanf(" %s", inserting);
			wordSize = strlen(inserting);
			insert(0, 0, 1);
		}
		for(int i=0; i<=nNodes; i++){
			for(int j=0; j<=nNodes; j++){
				called[i][j]=false;
			}
		}
		if(solve(0,0)) printf("S\n");
		else printf("N\n");
	}
	return 0;
}