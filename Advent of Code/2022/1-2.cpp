#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int curCalories = 0;
priority_queue<int> pq;

void finishElf() {
	pq.push(curCalories);
	curCalories = 0;
}

int main() {
        char line[MAXN];
	while(gets(line)) {
		if (strlen(line) == 0) {
			finishElf();
		}
		else {
			int calories;
			sscanf(line, "%d", &calories);
			curCalories += calories;
		}
	}
	finishElf();
	int sum = 0;
	for (int i = 0; i < 3; i++) {
		sum += pq.top();
		pq.pop();
	}
	printf("%d\n", sum);
	return 0;
}
