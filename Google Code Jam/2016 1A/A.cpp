#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

list<char> deq;
char str[MAXN];

int main(){
	int T, n;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo<=T; caseNo++){
		scanf(" %s", str);
		n = strlen(str);
		for(int i=0; i<n; i++){
			if (!deq.empty() && deq.front() <= str[i]) deq.push_front(str[i]);
			else deq.push_back(str[i]);
		}
		printf("Case #%d: ", caseNo);
		while(!deq.empty()){
			printf("%c", deq.front());
			deq.pop_front();
		}
		printf("\n");
	}
	return 0;
}