#include <bits/stdc++.h>
using namespace std;

int limit(string univ) {
	if (univ == "MSU") return 4;
	return 2;
}

int main() {
	int N;
	cin >> N;
	map<string, int> teams;
	vector<pair<string, string> > ans;
	string univ, name;
	while(N --> 0 && ans.size() < 10u) {
		cin >> univ >> name;
		if (univ == "SCH") continue;
		if (!teams.count(univ)) {
			teams[univ] = 0;
		}
		if (teams[univ] < limit(univ)) {
			teams[univ]++;
			ans.push_back(make_pair(univ, name));
		}
	}
	cout << ans.size() << endl;
	for(int i = 0; i < (int)ans.size(); i++) {
		univ = ans[i].first;
		name = ans[i].second;
		cout << univ << " " << name << endl;
	}
	return 0;
}