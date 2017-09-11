#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

inline void printspaces(int n) {
	for(int i=0; i<n; i++) printf(" ");
}

char name[MAXN];
stack<char> s;
char conv[26] = {0, 1, 2, 4, 0, 1, 3, 0, 0, 3, 3, 5, 6, 6, 0, 1, 3, 7, 2, 4, 0, 1, 0, 2, 0, 2};

int main() {
	printspaces(9);
	printf("NOME");
	printspaces(21);
	printf("CODIGO LOUCO DO ROBERTO\n");
	printf("---------------------------------------------------------\n");
	while(scanf(" %s ", name) != EOF) {
		int len = strlen(name);
		for(int i = len-2; i>0; i--) {
			int c = conv[name[i]-'A'];
			if (c > 0 && c != conv[name[i-1]-'A']) {
				s.push(c);
			}
		}
		printspaces(9);
		printf("%s", name);
		printspaces(25-len);
		printf("%c", name[0]);
		for(int i=1; i<len-1; i++) {
			if (!s.empty()) {
				printf("%d", s.top());
				s.pop();
			}
			else printf("0");
		}
		printf("%c\n", name[len-1]);
	}
	printspaces(19);
	printf("FIM DO PROGRAMA\n");
	return 0;
}
