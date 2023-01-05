#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	string emp;

	getline(cin, emp);
	while (T--) {
		string line;
		getline(cin, line);
		stringstream ss;
		ss << line;

		set<string> used;
		while (true) {
			getline(cin, line);
			stringstream other;
			other << line;
			
			other >> line;
			other >> line;

			if (line == "does") break;

			other >> line;
			used.insert(line);
		}

		bool space = false;
		while (ss >> line) {
			if (used.count(line)) continue;
			if (space) cout << " ";
			cout << line; space = true;
		}
		cout << "\n";
	}
}