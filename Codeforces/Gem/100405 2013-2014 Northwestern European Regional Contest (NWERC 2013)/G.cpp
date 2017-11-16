#include <bits/stdc++.h>
using namespace std;

int mdc(int a,int b){
	if (b==0)return a;
	return mdc(b,a%b);
}

int main(){
	int ab,ac,bd;
	while (cin>>ab>>ac>>bd){
		int u = ab*ac, v = bd-ac;
		int k = mdc(u,v);
		printf("%d/%d\n",u/k,v/k);
	}
}