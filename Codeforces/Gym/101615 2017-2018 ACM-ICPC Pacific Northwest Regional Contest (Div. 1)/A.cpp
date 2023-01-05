#include <bits/stdc++.h>
#define FOR(x,n) for(int x=0; x<n; x++)
using namespace std;

string s;
int main() {
	cin >> s;
	int n = s.size();
	FOR(i, n-1) {
		if (s[i] == s[i+1]) {
			cout << "Or not.\n";
			return 0;
		}
	}
	cout << "Odd.\n";
	return 0;
}