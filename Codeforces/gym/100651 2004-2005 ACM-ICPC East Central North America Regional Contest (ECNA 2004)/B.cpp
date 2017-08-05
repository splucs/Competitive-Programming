#include <stdio.h>
#include <vector>
#include <set>
using namespace std;


const int N = 10005;
vector<bool> pr;

void compute() {
	pr.assign(N, true);
	pr[0] = pr[1] = false;
    for (int i=2; i<=N; ++i) {
        if (pr[i]) {
            for(int j=2*i; j<=N; j+=i) pr[j] = false;
        }
    }
}

vector<int> ans;
set<int> avail;

bool backtracking(int index, int last, int d) {
	if (index == last) return true;

	for(set<int>::iterator it = avail.begin(); it != avail.end(); it++) {
		ans[index] = *it;
		avail.erase(it);
		
		bool ok = true;
		if (index >= 1) {
			int acum = ans[index];
			for (int j = 1; index-j >= 0 && j < d; j++) {
				acum += ans[index-j];

				if (pr[acum]) { ok = false; break; }
			}
		}

		if (ok && backtracking(index+1, last, d)) return true;
		
		avail.insert(ans[index]);
		it = avail.find(ans[index]);
	}
	return false;
}

int main() {
	compute();
	int a, b, d;
	while (scanf("%d %d %d", &a, &b, &d) != EOF && a != 0) {
		ans.clear();
		avail.clear();
		for (int i = a; i <= b; i++) {
			ans.push_back(i);
			avail.insert(i);
		}
		if (!backtracking(0, ans.size(), d)) {
			printf("No anti-prime sequence exists.\n");
		}
		else {
			for (int i = 0; i < (int)ans.size(); i++) {
				if (i > 0) printf(",");
				printf("%d", ans[i]);
			}
			printf("\n");
		}

	}

	return 0;
}