#include <bits/stdc++.h>
using namespace std;

int main(){
	string cord[13] = {"do","do#","re","re#","mi","fa","fa#","sol","sol#","la","la#","si","desafinado"};
	int n,i,j,a[100009],b;
	set<int> vals[12];
	cin>>n;
	for (i=0;i<12;i++){
		for (j=0;j<3;j++)vals[i].insert((i+2*j)%12);
		vals[i].insert((i+5)%12);
		for (j=3;j<6;j++)vals[i].insert((i+2*j+1)%12);
	}for (i=0;i<n;i++){
		cin>>b;
		a[i] = (b-1)%12;
	}for (i=0;i<12;i++){
		for (j=0;j<n;j++){
			if (!vals[i].count(a[j]))break;
		}if (j==n)break;
	}cout<<cord[i]<<endl;
}
