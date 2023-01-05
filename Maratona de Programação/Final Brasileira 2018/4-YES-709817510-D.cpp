#include <bits/stdc++.h>
#define MAXN 100009
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;
typedef long long int ll;

char arr[1009], str[1009];
set<string> used;

int main() {
	int n;
	scanf("%d", &n);
	FOR(i, n) {
		scanf("%s", arr);
		int j = 0;
		bool arroba = false;
		bool plus = false;
		for (int k = 0; arr[k] != '\0'; k++) {
			if (arr[k] == '@') arroba = true;
			if (arroba) {
				str[j++] = arr[k];
			} else {
				if (arr[k] == '+') plus = true;
				
				if (plus) continue;
				else if (arr[k] == '.') continue;
				else str[j++] = arr[k];
			}
		}
		str[j] = '\0';
		used.insert(str);
	}
	printf("%d\n", (int)used.size());
}
