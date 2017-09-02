#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, ans = 0;
	scanf("%d", &N);
	string s, q;
	s = "FACE";
	char c[4];
	for(int i=0; i<N; i++) {
		scanf(" %c %c %c %c", &c[0], &c[1], &c[2], &c[3]);
		q.clear();
		for(int k=3; k>=0; k--) q.push_back(c[k]);
		if ((unsigned int)s.rfind(q) == s.size()-4u) {
			s.resize(s.size()-4u);
			ans++;
			if (s.empty()) s = "FACE";
		}
		else {
			reverse(q.begin(), q.end());
			s = s + q;
		}
	}
	printf("%d\n", ans);
	return 0;
}