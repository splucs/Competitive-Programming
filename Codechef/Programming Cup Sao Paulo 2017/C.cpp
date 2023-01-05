#include <bits/stdc++.h>
using namespace std;

map<string, set<string> > defeats;

int main() {
	int x, y, z, T;
	defeats["scissors"].insert("paper");
	defeats["paper"].insert("rock");
	defeats["rock"].insert("moon");
	defeats["moon"].insert("sun");
	defeats["sun"].insert("scissors");
	defeats["scissors"].insert("moon");
	defeats["moon"].insert("paper");
	defeats["paper"].insert("sun");
	defeats["sun"].insert("rock");
	defeats["rock"].insert("scissors");
	cin >> T;
	while(T --> 0) {
		string s1, s2;
		cin >> s1 >> s2;
		if (s1 == s2) printf("drew\n");
		if (defeats[s1].count(s2)) printf("akira\n");
		if (defeats[s2].count(s1)) printf("hideki\n");
	}
	return 0;
}