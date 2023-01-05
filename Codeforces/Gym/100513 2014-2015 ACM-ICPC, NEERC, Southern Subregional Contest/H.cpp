#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 1000009

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
const ii neutral = ii(INF, INF);
ii compL(ii a, ii b) {
	if (a.first < b.first) return a;
	if (a.first > b.first) return b;
	if (a.second < b.second) return a;
	if (a.second > b.second) return b;
	return a;
}
ii compR(ii a, ii b) {
	if (a.first < b.first) return a;
	if (a.first > b.first) return b;
	if (a.second > b.second) return a;
	if (a.second < b.second) return b;
	return a;
}

class SegmentTree {
private:
	vector<ii> stL, stR;
	vector<int> pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, ii* A) {
		if (l == r) {
			stL[p] = stR[p] = A[l];
			pos[l] = p;
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			stL[p] = compL(stL[left(p)], stL[right(p)]);
			stR[p] = compR(stR[left(p)], stR[right(p)]);
		}
	}
	ii findL(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return stL[p];
		ii p1 = findL(left(p), l, (l + r) / 2, a, b);
		ii p2 = findL(right(p), (l + r) / 2 + 1, r, a, b);
		return compL(p1, p2);
	}
	ii findR(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return stR[p];
		ii p1 = findR(left(p), l, (l + r) / 2, a, b);
		ii p2 = findR(right(p), (l + r) / 2 + 1, r, a, b);
		return compR(p1, p2);
	}
public:
	SegmentTree() {}
	SegmentTree(ii* begin, ii* end) {
		size = (int)(end - begin);
		stL.assign(4 * size, neutral);
		stR.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	ii queryL(int a, int b) {
		return findL(1, 0, size - 1, a, b);
	}
	ii queryR(int a, int b) {
		return findR(1, 0, size - 1, a, b);
	}
};

int arr[MAXN], N;
SegmentTree st;
vector<iii> ans;
ii vet[MAXN];

void solve(int l, int r) {
	if (l+1 == r) return;
	int p;
	if (arr[l] < arr[r]) p = st.queryR(l+1, r-1).second;
	else p = st.queryL(l+1, r-1).second;
	/*printf("solving from %d to %d\n", l+1, r+1);
	printf("%d found at %d\n", arr[l], l+1);
	printf("%d found at %d\n", arr[r], r+1);
	printf("%d found at %d\n", arr[p], p+1);*/
	if (arr[l] < arr[r]) ans.push_back(iii(l, ii(r, p)));
	else ans.push_back(iii(r, ii(l, p)));
	solve(l, p);
	solve(p, r);
}

bool iiicomp(iii a, iii b) {
	if (arr[a.first] != arr[b.first]) return arr[a.first] < arr[b.first];
	if (arr[a.second.first] != arr[b.second.first]) return arr[a.second.first] < arr[b.second.first];
	if (arr[a.second.second] != arr[b.second.second]) return arr[a.second.second] < arr[b.second.second];
	return false;
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
		arr[i+N] = arr[i];
		vet[i] = ii(arr[i], i);
		vet[i+N] = ii(arr[i+N], i+N);
	}
	st = SegmentTree(vet, vet+2*N);
	int l = st.queryL(0, N-1).second;
	int r = st.queryL(l+1, l+N-1).second;
	solve(l, r);
	solve(r, l+N);
	sort(ans.begin(), ans.end(), iiicomp);
	for(int i=0; i<(int)ans.size(); i++) {
		printf("%d %d %d\n", ans[i].first%N+1, ans[i].second.first%N+1, ans[i].second.second%N+1);
	}
	return 0;
}