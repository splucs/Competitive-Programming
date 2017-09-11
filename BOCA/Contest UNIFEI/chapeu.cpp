#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

map<string, vector<string> > mp;
char buffer[MAXN];

int main() {
	int N;
	scanf("%d ", &N);
	string name, school;
	for(int i=0; i<N; i++) {
		gets(buffer);
		name = string(buffer);
		scanf(" %s ", buffer);
		school = string(buffer);
		mp[school].push_back(name);
	}
	map<string, vector<string> >::iterator it;
	
	it = mp.find(string("Slytherin"));
	printf("Slytherin:\n");
	if (it != mp.end()) {
		vector<string> & v = it->second;
		sort(v.begin(), v.end());
		for(int i=0; i<(int)v.size(); i++) {
			printf("%s\n", v[i].c_str());
		}
	}
	printf("\n");
	
	it = mp.find(string("Hufflepuff"));
	printf("Hufflepuff:\n");
	if (it != mp.end()) {
		vector<string> & v = it->second;
		sort(v.begin(), v.end());
		for(int i=0; i<(int)v.size(); i++) {
			printf("%s\n", v[i].c_str());
		}
	}
	printf("\n");
	
	it = mp.find(string("Gryffindor"));
	printf("Gryffindor:\n");
	if (it != mp.end()) {
		vector<string> & v = it->second;
		sort(v.begin(), v.end());
		for(int i=0; i<(int)v.size(); i++) {
			printf("%s\n", v[i].c_str());
		}
	}
	printf("\n");
	
	it = mp.find(string("Ravenclaw"));
	printf("Ravenclaw:\n");
	if (it != mp.end()) {
		vector<string> & v = it->second;
		sort(v.begin(), v.end());
		for(int i=0; i<(int)v.size(); i++) {
			printf("%s\n", v[i].c_str());
		}
	}
	printf("\n");
	
	return 0;
}