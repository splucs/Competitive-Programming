#include <cstdio>
#include <map>
#include <stack>
using namespace std;

/*
 * Parenthetic to polish expression conversion
 */

inline bool isOp(char c) {
	return c=='+' || c=='-' || c=='*' || c=='/' || c=='^';
}

inline bool isCarac(char c) {
	return (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9');
}

int paren2polish(char* paren, char* polish) {
	map<char, int> prec;
	prec['('] = 0;
	prec['+'] = prec['-'] = 1;
	prec['*'] = prec['/'] = 2;
	prec['^'] = 3;
	int len = 0;
	stack<char> op;
	for (int i = 0; paren[i]; i++) {
		if (isOp(paren[i])) {
			while (!op.empty() && prec[op.top()] >= prec[paren[i]]) {
				polish[len++] = op.top(); op.pop();
			}
			op.push(paren[i]);
		}
		else if (paren[i]=='(') op.push('(');
		else if (paren[i]==')') {
			for (; op.top()!='('; op.pop())
				polish[len++] = op.top();
			op.pop();
		}
		else if (isCarac(paren[i]))
			polish[len++] = paren[i];
	}
	for(; !op.empty(); op.pop())
		polish[len++] = op.top();
	polish[len] = 0;
	return len;
}

/*
 * TEST MATRIX
 */

int main() {
	int N, len;
	char polish[400], paren[400];
	scanf("%d", &N);
	for (int j=0; j<N; j++) {
		scanf(" %s", paren);
		paren2polish(paren, polish);
		printf("%s\n", polish);
	}
	return 0;
}
