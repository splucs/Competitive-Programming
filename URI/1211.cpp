#include <cstdio>
#include <cstdlib>
#include <cstring>

class node{
public:
	node(){
		for (int i = 0; i < 10; ++i)
		{
			sons[i]=NULL;
		}
	}
	~node(){
		for (int i = 0; i < 10; ++i)
		{
			if(sons[i]!=NULL) delete sons[i];
		}
	}
	node* sons[10];
};

node* root;
int cont;

void add(char* str, node* no){
	if (str[0]=='\0') return;
	if (no->sons[str[0]-'0']==NULL){
		no->sons[str[0]-'0'] = new node();
		cont++;
	}
	add(str+1, no->sons[str[0]-'0']);
}

int main()
{
	int N;
	char str[229];
	while(scanf("%d", &N)!=EOF){
		cont=0;
		root = new node();
		for (int i = 0; i < N; ++i)
		{
			scanf(" %s", str);
			add(str, root);
		}
		printf("%d\n", N*strlen(str) - cont);
		delete root;
	}
	return 0;
}