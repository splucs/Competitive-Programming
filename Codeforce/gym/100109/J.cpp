#include <bits/stdc++.h>
using namespace std;
#define MAXN 209

char pass[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n, a, b;
	scanf("%d %d %d %s", &n, &a, &b, pass);
	int ca = 0, cb = 0;
	for(int i=0; i<n; i++) {
		if (pass[i] == '0') ca++;
		if (pass[i] == '1') cb++;
	}
	//no solution
	if (a+b > n){
		printf("-1\n");
		return 0;
	}
	int ans = 0;
	//replace 0 by 1
	for(int i=0; i<n && cb < b && ca > a; i++) {
		if (pass[i] == '0'){
			pass[i] = '1';
			ans++;
			ca--;
			cb++;
		}
	}
	//replace 1 by 0
	for(int i=0; i<n && cb > b && ca < a; i++) {
		if (pass[i] == '1'){
			pass[i] = '0';
			ans++;
			ca++;
			cb--;
		}
	}
	//replace 2 by 0
	for(int i=0; i<n && ca < a; i++) {
		if (pass[i] == '2'){
			pass[i] = '0';
			ans++;
			ca++;
		}
	}
	//replace 2 by 1
	for(int i=0; i<n && cb < b; i++) {
		if (pass[i] == '2'){
			pass[i] = '1';
			ans++;
			cb++;
		}
	}
	//replace 0 by 2
	for(int i=0; i<n && ca > a; i++) {
		if (pass[i] == '0'){
			pass[i] = '2';
			ans++;
			ca--;
		}
	}
	//replace 1 by 2
	for(int i=0; i<n && cb > b; i++) {
		if (pass[i] == '1'){
			pass[i] = '2';
			ans++;
			cb--;
		}
	}
	printf("%d\n%s\n", ans, pass);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}