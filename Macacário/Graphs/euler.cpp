#include <vector>
#include <stack>
#define MAXN 100009
using namespace std;

vector<int> adjList[MAXN];
int N, M;

vector<int> euler(int start) {
	vector<int> nedges(N, 0), tour;
	stack<int> dfs;
	dfs.push(start);
	int u = start;
	while (!dfs.empty()) {
		if (nedges[u] < (int)adjList[u].size()) {
			dfs.push(u);
			u = adjList[u][nedges[u]++];
		}
		else {
			tour.push_back(u);
			u = dfs.top();
			dfs.pop();
		}
	}
	for (int i = 0; i < N; i++) {
		if (nedges[u] < (int)adjList[u].size()) {
			tour.clear(); //Não há tour
		}
	}
	return tour; //Ordem inversa
}

int main()
{
	int T;
	scanf("%d", &T);
	vector<int> start
	while (T-- > 0) {
		scanf("%d", &N);

	}
}