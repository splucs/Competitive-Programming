#include <cstdio>
#include <map>
#include <iostream>
#include <string>
using namespace std;

bool verify(const char* c1, const char* c2, unsigned int n){
	int res = 1;
	for (int i=0; i<n; i++){
		if (c1[i]!=c2[i]) res--;
		if (res<0) return false;
	}
	return true;
}

int main(){
	int N, M, res;
	string nome, ass;
	map<string, string> mapa;
	while(true){
		scanf("%d", &N);
		if (N==0) break;
		res=0;
		for(int i=0; i<N; i++){
			cin>>nome >> ass;
			mapa[nome]=ass;
		}
		scanf("%d", &M);
		for (int i=0; i<M; i++){
			cin>> nome >> ass;
			if (!verify(mapa[nome].c_str(), ass.c_str(), ass.size())) res++;
		}
		printf("%d\n", res);
		mapa.clear();
	}
	return 0;
}