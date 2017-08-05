#include <bits/stdc++.h>

using namespace std;

int main(){
	string s;
	vector<int> letra[300];
	string t = "happiness";
	cin>>s;
	int cont = 0;
	int a, b;
	bool flag;
	
	for(int i = 0; i<s.length(); i++){
		letra[s[i]].push_back(i+1);
	}
	
	for(int i = 0; i<=(int)s.length()-(int)t.length(); i++){
		flag = true;
		for(int j = 0; j<(int)t.length(); j++){
			if(s[i+j]!=t[j]){
				flag = false;
				break;
			}
		}
		if(flag){
			cont++;
			if(cont==1) a = i+1;
			b = i+2;
		}
	}
	if(cont == 1 || cont==2){
		printf("YES\n%d %d\n", a, b);
	}else if(cont==0){
		flag = false;
		for(int i = 97; i<=122; i++){
			if(letra[i].size()>=2){
				printf("YES\n%d %d\n", letra[i][0], letra[i][1]);
				flag = true;
				break;
			}
		}
		if(!flag){
			printf("YES\n1 2\n");
		}
	}else
		printf("NO\n");
	return 0;
}