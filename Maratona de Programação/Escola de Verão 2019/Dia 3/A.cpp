#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int a[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	int nim = 0;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		nim ^= a[i];
	}
	if (nim > 1) puts("Alice");
	else if (nim == 1) puts("Bob");
	else {
		bool ok = false;
		for(int i = 0; i < n; i++) {
			//nim^a[i]^x = 1
			int x = nim^a[i]^1;
			if (x < a[i]) ok = true;
		}
		puts(ok ? "Alice" : "Bob");
	}
	return 0;
}