#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#define MAXN 10009
using namespace std;

struct node{
	string name;
	set<int> sons;
};

node newnode(string a){
	node b;
	b.name = a;
	b.sons.clear();
	return b;
}

vector<node> nds;
map<string, int> pos;

void add(string father){
	if (!pos.count(father)){
		pos[father] = nds.size();
		nds.push_back(newnode(father));
	}
}

bool visited[MAXN];

int search(int son, int father){
	if (visited[father]) return 0;
	visited[father]=true;
	if (father==son) return 3;
	set<int>::iterator it;
	int res;
	for(it = nds[father].sons.begin(); it!= nds[father].sons.end(); it++){
		res = search(son, *it);
		if (res==3) return 1;
		if (res==2 || res==1) return 2;
	}
	return 0;
}

int main(){
	int n, m, now, last;
	scanf("%d %d ", &n, &m);
	nds.resize(MAXN);
	nds.clear();
	string line, son, father;
	for(int i=0; i<n; i++){
		getline(cin, line);
		last = 0, now=0;
		while(now<(int)line.size() && line[now]!=':'){
			now++;
		}
		father = line.substr(last, now-last);
		last = now+1;
		add(father);
		while(now++){
			if (line[now]==';' || now==(int)line.size()){
				son = line.substr(last, now-last);
				last = now+1;
				add(son);
				nds[pos[father]].sons.insert(pos[son]);
				if (now==(int)line.size()) break;
			}
		}
	}
	map<string, int>::iterator it;
	for(int i=0; i<m; i++){
		getline(cin, line);
		last = 0, now=0;
		while(now<(int)line.size() && line[now]!=';'){
			now++;
		}
		father = line.substr(last, now-last);
		last = ++now;
		while(now<(int)line.size() && line[now]!=';'){
			now++;
		}
		son = line.substr(last, now-last);
		if (!pos.count(son) || !pos.count(father)){
			printf("No\n");
			continue;
		}
		for(int j=0; j<(int)nds.size(); j++) visited[j]=false;
		int res = search(pos[father], pos[son]);
		if (res==0) printf("No\n");
		else if (res == 1) printf("Yes (direct)\n");
		else printf("Yes (indirect)\n"); 
	}
	return 0;
}