#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

map<char, string> encoder;
map<string, char> decoder;

char s[MAXN];
int num[MAXN];

int main() {
	encoder['A'] = ".-";
	encoder['B'] = "-...";
	encoder['C'] = "-.-.";
	encoder['D'] = "-..";
	encoder['E'] = ".";
	encoder['F'] = "..-.";
	encoder['G'] = "--.";
	encoder['H'] = "....";
	encoder['I'] = "..";
	encoder['J'] = ".---";
	encoder['K'] = "-.-";
	encoder['L'] = ".-..";
	encoder['M'] = "--";
	encoder['N'] = "-.";
	encoder['O'] = "---";
	encoder['P'] = ".--.";
	encoder['Q'] = "--.-";
	encoder['R'] = ".-.";
	encoder['S'] = "...";
	encoder['T'] = "-";
	encoder['U'] = "..-";
	encoder['V'] = "...-";
	encoder['W'] = ".--";
	encoder['X'] = "-..-";
	encoder['Y'] = "-.--";
	encoder['Z'] = "--..";
	encoder['_'] = "..--";
	encoder[','] = ".-.-";
	encoder['.'] = "---.";
	encoder['?'] = "----";

	for(auto pp : encoder) {
		decoder[pp.se] = pp.fi;
	}

	while(scanf(" %s", s) != EOF) {
		int n = strlen(s);
		string aux;
		FOR(i, n) {
			num[i] = encoder[s[i]].size();
			aux.append(encoder[s[i]]);
		}
		reverse(num, num+n);
		int j = 0;
		FOR(i, n) {
			string cur = aux.substr(j, num[i]);
			//if (!decoder.count(cur)) printf("cur not found %s\n", cur.c_str());
			//assert(decoder.count(cur));
			s[i] = decoder[cur];
			j += num[i];
		}
		printf("%s\n", s);
	}

	return 0;
}