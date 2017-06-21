#include <bits/stdc++.h>
#define INF (1<<30)
using namespace std;

const int neutral = -INF; //comp(x, neutral) = x
int comp(int a, int b) {
	return max(a, b);
}

class SegmentTree {
private:
	vector<int> st;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r) {
		if (l == r) {
			st[p] = 1;
		}
		else {
			build(left(p), l, (l + r) / 2);
			build(right(p), (l + r) / 2 + 1, r);
			st[p] = -1;
		}
	}
	void push(int p, int l, int r) {
		if (st[p] >= 0 && l != r) {
			st[right(p)] = st[p];
			st[left(p)] = st[p];
			st[p] = -1;
		}
	}
	void update(int p, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			st[p] = k; push(p, l, r);
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
		}
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = query(left(p), l, (l + r) / 2, a, b);
		int p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(int _size) {
		size = _size;
		st.assign(4 * size, neutral);
		build(1, 0, size - 1);
	}
	int query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, int k) { update(1, 0, size - 1, a, b, k); }
};

typedef long long ll;
typedef pair<ll, ll> ii;

int n, m, nids;
map<ll, int> ip2id;
SegmentTree st(1);

void printSegTree() { //DEBUG
	printf("st: ");
	for(int i=0; i<nids; i++) printf("%d", st.query(i, i));
	printf("\n");
}

ll readIp(){
	ll ans = 0, by[4], p = 256;
	scanf("%I64d.%I64d.%I64d.%I64d", &by[0], &by[1], &by[2], &by[3]);
	for(int i=0; i<4; i++){
		ans = (ans*p + by[i]);
	}
	//printf("ip read : %I64d\n", ans);
	return ans;
}

void readAccessControlList(){
	scanf("%d", &n);
	stack<pair<int, ii> > alist;
	set<ll> ips;
	char word[10], slash;
	ll s, t;
	int p;
	
	while(n--){
		scanf(" %s from ", word);
		ll s = readIp();
		scanf("%c", &slash);
		if (slash == '\n') t = s;
		else{
			scanf("%d", &p);
			p = 32 - p;
			t = s + (1ll<<p) - 1;
		}
		if (word[0] == 'a') p = 1;
		else p = 0;
		alist.push(make_pair(p, ii(s, t)));
		ips.insert(s);
		ips.insert(t);
	}
	ips.insert(0);
	ips.insert((1ll<<32) - 1);
	
	nids = 0;
	for(set<ll>::iterator it = ips.begin(); it!=ips.end(); it++){
		for(int i=-1; i<=1; i++){
			if (!ip2id.count((*it) + i)) ip2id[(*it)+i] = nids++;
		}
	}
	
	st = SegmentTree(nids);
	while(!alist.empty()){
		p = alist.top().first;
		s = alist.top().second.first;
		t = alist.top().second.second;
		alist.pop();
		st.update(ip2id[s], ip2id[t], p);
	}
}

void processQueries(){
	scanf("%d", &m);
	ll ip;
	int id;
	while(m--){
		ip = readIp();
		map<ll, int>::iterator it = ip2id.lower_bound(ip);
		id = it->second;
		if (st.query(id, id)) printf("A");
		else printf("D");
	}
	printf("\n");
}

int main(){
	freopen("access.in", "r", stdin);
	freopen("access.out", "w", stdout);
	
	readAccessControlList();
	processQueries();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}