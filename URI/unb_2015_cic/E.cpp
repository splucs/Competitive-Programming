#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	char op[10];
	int x[3], ans;
	for(int caseNo = 1; caseNo <= T; caseNo++){
		scanf(" %s %d %d %d", op, &x[0], &x[1], &x[2]);
		if (strcmp(op, "min") == 0) {
			ans = x[0];
			ans = min(ans, x[1]);
			ans = min(ans, x[2]);
		}
		else if (strcmp(op, "max") == 0) {
			ans = x[0];
			ans = max(ans, x[1]);
			ans = max(ans, x[2]);
		}
		else if (strcmp(op, "mean") == 0){
			ans = (x[0] + x[1] + x[2]) / 3.0;
		}
		else if (strcmp(op, "eye") == 0) {
			ans = 0.30*x[0] + 0.59*x[1] + 0.11*x[2];
		}
		printf("Caso #%d: %d\n", caseNo, ans);
	}
	return 0;
}