#include <cstdio>
#include <map>
using namespace std;
int N;
typedef struct node{
	map<int, int> edges;
	int grade;
}node;
node vetA[10009];
node vetB[10009];

bool verify(int noA, int noB, int fromA, int fromB){
	if (vetA[noA].grade!=vetB[noB].grade) return false;
	int n = vetA[noA].grade;
	bool usedA[n], usedB[n];
	for (int i = 0; i < n; ++i)
	{
		if (vetA[noA].edges[i]==fromA)
			usedA[i]=true;
		else usedA[i]=false;
		if (vetB[noB].edges[i]==fromB)
			usedB[i]=true;
		else usedB[i]=false;
	}
	for (int i = 0; i < n; ++i)
	{
		if (usedA[i]) continue;
		for (int j = 0; j < n; j++){
			if (usedB[j]) continue;
			if (verify(vetA[noA].edges[i],vetB[noB].edges[j], noA, noB)){
				usedA[i]=usedB[j]=true;
				break;
			}
		}
		if (!usedA[i]) return false;
	}
	return true;
}

int main()
{
	int x, y;
	bool found;
	while(scanf("%d", &N)!=EOF){
		for (int i = 0; i < N; ++i)
		{
			vetA[i].edges.clear();
			vetB[i].edges.clear();
			vetA[i].grade=0;
			vetB[i].grade=0;
		}
		for (int i = 0; i < N-1; ++i)
		{
			scanf("%d %d", &x, &y);
			x--;
			y--;
			vetA[x].edges[vetA[x].grade++]=y;
			vetA[y].edges[vetA[y].grade++]=x;
		}
		for (int i = 0; i < N-1; ++i)
		{
			scanf("%d %d", &x, &y);
			x--;
			y--;
			vetB[x].edges[vetB[x].grade++]=y;
			vetB[y].edges[vetB[y].grade++]=x;
		}
		for (int i = 0; i < N; ++i)
		{
			found = verify(0, i, -1, -1);
			if (found) break;
		}
		if (found) printf("S\n");
		else printf("N\n");
	}
	return 0;
}