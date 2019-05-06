#include <queue>
using namespace std;
#define MAXN 100009
#define ALFA 26

/*
 * Aho-Corasick Automaton
 */

int go[MAXN][ALFA], ter[MAXN], link[MAXN];
int cnt = 1;
 
void add(const char* s) {
	int u = 0;
	for(int i = 0; s[i]; i++) {
		char c = s[i] - 'a';
		if(!go[u][c]) go[u][c] = cnt++;
		u = go[u][c];
	}
	ter[u] += 1;
}
 
void aho() {
	queue<int> q;
	q.push(0);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		ter[u] += ter[link[u]];
		for(int i = 0; i < ALFA; i++) {
			int &v = go[u][i];
			if (v) {
				q.push(v);
				link[v] = u ? go[link[u]][i] : 0;
			}
			else v = go[link[u]][i];
		}
		link[u] = 0;
	}
}

int match(const char* s) {
	int u = 0, ans = 0;
	for(int i = 0; s[i]; i++) {
		u = go[u][s[i] - 'a'];
		ans += ter[u];
	}
	return ans;
}

/*
 * TEST MATRIX
 */

int main() {
	add("a");
	add("aa");
	add("ab");
	aho();
	printf("%d\n", match("aaab"));
}
