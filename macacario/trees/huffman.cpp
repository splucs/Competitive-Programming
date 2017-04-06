#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
#define MAXN 100009
#define INF (1LL<<60)

typedef long long ll;
typedef pair<ll, int> ii;

class HuffmanTree{
	vector<int> left, right, par;
	int root, size;
	ll cost;
	
public:
	HuffmanTree(int* begin, int* end){
		size = (int)(end - begin);
		int u, v;
		cost = 0;
		ll cu, cv;
		left.assign(2*size+9, -1);
		right.assign(2*size+9, -1);
		par.assign(2*size+9, -1);
		priority_queue<ii> pq;
		for(int i=0; i<size; i++){
			pq.push(ii(-begin[i], i));
		}
		while(pq.size() > 1){
			u = pq.top().second;
			cu = -pq.top().first;
			pq.pop();
			v = pq.top().second;
			cv = -pq.top().first;
			pq.pop();
			root = size++;
			left[root] = u; par[u] = root;
			right[root] = v; par[v] = root;
			cost += cu + cv;
			pq.push(ii(-cu-cv, root));
		}
	}
	ll getCost() { return cost; }
	int getSize() { return size; }
	void getCode(int u, char* buffer){
		vector<int> s;
		while(par[u] >= 0){
			if (left[par[u]] == u) s.push_back(0);
			else s.push_back(1);
			u = par[u];
		}
		while(!s.empty()){
			*buffer = s.back() + '0';
			buffer++; s.pop_back();
		}
		*buffer = '\0';
	}
};

/*
 * Codeforces 101128C
 */

int main()
{
	int T, N, a[MAXN];
	char buffer[MAXN];
	scanf("%d", &T);
	while(T-->0){
		scanf("%d", &N);
		for(int i=0; i<N; i++) scanf("%d", &a[i]);
		HuffmanTree h(a, a+N);
		/*for(int i=0; i<N; i++){
			h.getCode(i, buffer);
			printf("%d -> %s\n", a[i], buffer);
		}*/
		printf("%I64d\n", h.getCost());
	}
	return 0;
}