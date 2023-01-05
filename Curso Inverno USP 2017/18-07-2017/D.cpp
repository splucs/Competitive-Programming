#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	string str, rev;
	scanf(" %d ", &T);
	while(T-->0) {
		cin >> str;
		bool possible = true;
		int len = str.size();
		rev = str;
		for(int i=0; i<len/2; i++) swap(rev[i], rev[len-i-1]);
		for(int i=0; i<len; i++) {
			for(int j=i+1; j<len; j++) {
				if (rev.find(str.substr(i, j-i+1)) == string::npos){
					//cout << "didnt find " << str.substr(i, j-i+1) << endl;
					possible = false;
				}
				//else cout << "found " << str.substr(i, j-i+1) << endl;
			}
		}
		if (possible) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}