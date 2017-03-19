#include <bits/stdc++.h>
using namespace std;

string val[105];
int acum[200][200][200];
int j;

int dp(int pos1, int pos2,int k) {
	if (pos1 == val[0].size()) {
		if (pos2==j) return 1;
		return 0;
	}
	if (pos2 == j||k==val[pos2].size())return 0;
	if (acum[pos1][pos2][k] != -1)return acum[pos1][pos2][k];

	string s = val[pos2];
	char c = val[0][pos1]-'A'+'a';
	int ans = 0;
	
	for (int i = k; i < s.size(); i++) {
		if (c == s[i])ans += dp(pos1 + 1, pos2 + 1, 0) + dp(pos1 + 1, pos2, i + 1);
	}
	return acum[pos1][pos2][k] = ans;
}

int main() {
	map<string, bool> insig;
	string word = "", input;
	int n;
	while (cin >> n&&n != 0) {
		insig.clear();
		for (int i = 0; i<n; i++) {
			cin >> input;
			insig[input] = true;
		}
		getline(cin, input);
		while (getline(cin, input)&&input!="LAST CASE") {
			j = 0;
			word = "";
			for (int i = 0; i<input.size(); i++) {
				if (input[i] == ' ') {
					if (j == 0 || !insig[word])val[j++] = word;
					word = "";
					continue;
				}
				word += input[i];
			}if (!insig[word])val[j++] = word;
			//for (int i=0;i<j;i++)cout<<val[i]<<endl;
			for (int i = 0; i<val[0].length(); i++)
				for (int k = 0; k<j; k++)for (int l=0;l<=150;l++)acum[i][k][l]=-1;
			int ans = dp(0, 1, 0);
			if (ans == 0)cout << val[0] << " is not a valid abbreviation" << endl;
			else cout << val[0] << " can be formed in " << ans << " ways" << endl;
		}
	}

}