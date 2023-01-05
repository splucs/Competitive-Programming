#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

typedef struct kid{
	string name;
	int num;
	kid* left;
	kid* right;
}kid;

int main()
{
	kid kids[109];
	kid *p;
	int N, toWalk;
	while(true){
		scanf("%d", &N);
		if (N==0) break;
		for (int i = 0; i < N; ++i)
		{
			cin>> kids[i].name;
			cin>> kids[i].num;
		}
		if (N==1){
			printf("Vencedor(a): %s\n", kids[0].name.c_str());
			continue;
		}
		kids[0].left=&kids[N-1];
		kids[0].right=&kids[1];
		kids[N-1].right=&kids[0];
		kids[N-1].left=&kids[N-2];
		for (int i = 1; i < N-1; ++i)
		{
			kids[i].right=&kids[i+1];
			kids[i].left=&kids[i-1];
		}
		p=&kids[0];
		while(N-->1){
			toWalk=p->num;
			if (toWalk%2!=0){
				while(toWalk-->0) p=p->right;
			}
			else while(toWalk-->0) p=p->left;
			p->left->right=p->right;
			p->right->left=p->left;
		}
		p=p->right;
		printf("Vencedor(a): %s\n", p->name.c_str());
	}
	return 0;
}