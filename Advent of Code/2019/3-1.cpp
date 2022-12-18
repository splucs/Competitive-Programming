#include <cstdio>
#include <vector>
using namespace std;

struct op {
	char dir;
	int dist;
};

vector<op> read() {
	vector<op> ans;
	while(true) {
		op cur;
		scanf(" %c%d", &cur.dir, &cur.dist);
		ans.push_back(cur);
		char nxtChar;
		scanf("%c", &nxtChar);
		if (nxtChar != ",") break;
	}
	return ans;
}

void move(cur op, int &x, int &y) {
	
}

int main()
