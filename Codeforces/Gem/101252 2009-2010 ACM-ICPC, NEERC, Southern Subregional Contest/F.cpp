#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXT 10
#define INF (1<<30)

const int neutral = -INF;
int comp(int a, int b) {
	return max(a, b);
}

class SegmentTree {
private:
	vector<int> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r) {
		if (l == r) {
			st[p] = neutral;
			pos[l] = p;
		}
		else {
			build(left(p), l, (l + r) / 2);
			build(right(p), (l + r) / 2 + 1, r);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	int find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = find(left(p), l, (l + r) / 2, a, b);
		int p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree() {
		size = MAXN;
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1);
	}
	int query(int a, int b) {
		if (b < a) return neutral;
		return find(1, 0, size - 1, a, b);
	}
	void update(int n, int num) {
		st[pos[n]] = num;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

int N, arr[MAXN];
int dp[MAXN], A[MAXN];
SegmentTree st;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	//while(!feof(stdin)) {
		scanf(" %d ", &N);
		for(int i=1; i<=N; i++) {
			scanf(" %d ", &arr[i]);
		}
		
		st = SegmentTree();
		int ans = 1;
		stack<int> s;
		
		for(int i=1; i<=N; i++) {
			dp[i] = i-1;
			A[i] = -1;
			
			int a = arr[i];
			int j = st.query(a, a);
			if (j >= 0 && dp[i] > i - j - 1 + dp[j]) {
				dp[i] = i - j - 1 + dp[j];
				A[i] = j;
				s.push(j);
				st.update(arr[j], neutral);
			}
			
			a = arr[i]-2;
			for(int t=0; t<MAXT; t++) {
				j = st.query(0, a);
				if (j >= 0 && dp[i] > i - j - 1 + dp[j]) {
					dp[i] = i - j - 1 + dp[j];
					A[i] = j;
					s.push(j);
					st.update(arr[j], neutral);
				}
				else break;
			}
			
			a = arr[i]+2;
			for(int t=0; t<MAXT; t++) {
				j = st.query(a, MAXN-1);
				if (j >= 0 && dp[i] > i - j - 1 + dp[j]) {
					dp[i] = i - j - 1 + dp[j];
					A[i] = j;
					s.push(j);
					st.update(arr[j], neutral);
				}
				else break;
			}
			
			while(!s.empty()) {
				j = s.top(); s.pop();
				st.update(arr[j], j);
			}
			st.update(arr[i], i);
			
			//printf("dp[%d] = %d, A[%d] = %d\n", i, dp[i], i, A[i]);
			if (dp[ans]+N-ans > dp[i]+N-i) ans = i;
		}
	
		printf("%d\n", dp[ans]);
		while(ans != -1) {
			s.push(arr[ans]);
			ans = A[ans];
		}
		while(!s.empty()) {
			printf("%d ", s.top());
			s.pop();
		}
		printf("\n");
	//}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}