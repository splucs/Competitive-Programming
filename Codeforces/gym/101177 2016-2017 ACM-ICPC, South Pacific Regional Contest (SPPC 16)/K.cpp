#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char lower(char u){
	if (u>='A'&&u<='Z')return u+'a'-'A';
	return u;
}

int cnt(char u,char *s){
	int ans = 0;
	u = lower(u);
	int n = strlen(s);
	for (int i=0;i<n;i++){
		if (s[i]==u)ans++;
	}
	//cout<<ans<<endl;
	return ans;
}

int main(){
	char s[1000];
	char a[2][11] = {"kangaroo","kiwibird"};
	int ans[2] = {};
	
	while(scanf(" %s",&s)!=EOF) {
		int n = strlen(s);
		ans[0] = ans[1] = 0;
		for (int i=0;i<n;i++){
			for (int j=0;j<2;j++)ans[j]+=cnt(s[i],a[j]);
		}//cout<<ans[0]<<" "<<ans[1]<<endl;
		if (ans[0]>ans[1])printf("Kangaroos\n");
		else if (ans[1]>ans[0])printf("Kiwis\n");
		else printf("Feud continues\n");
	}
}