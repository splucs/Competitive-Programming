#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

typedef pair<char, int> ci;
typedef pair<int, int> ii;

int main()
{
	int n, level = 0, linesize;
	char line[100];

	scanf("%d", &n);
	gets(line);

	stack<ci> seq;
	stack<ii> pos[30];

	for(int i=0; i<n; i++){
		gets(line);
		linesize = strlen(line);
		for(int j=0; j<linesize; j++){
			if (line[j] == '{'){
				level++;
			}
			if (line[j] == '}'){
				while(!seq.empty() && seq.top().second == level){
					pos[seq.top().first-'a'].pop();
					seq.pop();
				}
				level--;
			}
			if (line[j] >= 'a' && line[j] <= 'z'){

				if (!pos[line[j]-'a'].empty()){
					printf("%d:%d: warning: shadowed declaration of %c, the shadowed position is %d:%d\n", i+1, j+1, line[j], pos[line[j]-'a'].top().first + 1, pos[line[j]-'a'].top().second + 1);
				}

				pos[line[j]-'a'].push(make_pair(i, j));
				seq.push(make_pair(line[j], level));
			}
		}
	}

	return 0;
}