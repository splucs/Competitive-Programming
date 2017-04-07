#include <cstdio>
#include <map>
using namespace std;

class node{
public:
	node(char c){
		carac = c;
		printHere = false;
	}
	~node(){
		map<char, node*>::iterator it;
		for(it = sons.begin(); it!=sons.end(); it++){
			delete it->second;
		}
	}
	char carac;
	map<char, node*> sons;
	bool printHere;
};

node* root;

void add(node* no, char* str){
	if (str[0]=='\0'){
		no->printHere=true;
		return;
	}
	if (!no->sons.count(str[0])){
		no->sons[str[0]] = new node(str[0]);
	}
	add(no->sons[str[0]], str+1);
}

char toPrint[229];
int size;

void print(node* no){
	if (no!=root){
		toPrint[size++]=no->carac;
		if (no->printHere){
			toPrint[size]='\n';
			toPrint[size+1]='\0';
			printf(toPrint);
		}
	}
	map<char, node*>::iterator it;
	for(it = no->sons.begin(); it!=no->sons.end(); it++){
		print(it->second);
	}
	size--;
}

int main()
{
	char read[229], c;
	int s;
	s=0;
	root = new node('\0');
	while(scanf("%c", &c)!=EOF){
		if (c>='A' && c<='Z') c += 'a' - 'A';
		if (c>='a' && c<='z') read[s++]=c;
		else{
			read[s]='\0';
			add(root, read);
			s=0;
		}
	}
	root->printHere=false;
	size=0;
	print(root);
	delete root;
	return 0;
}