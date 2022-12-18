#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int maxCalories = 0, curCalories = 0;

void finishElf() {
	maxCalories = max(maxCalories, curCalories);
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
	printf("%d\n", maxCalories);
	return 0;
}
