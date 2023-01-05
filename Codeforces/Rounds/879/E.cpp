#include <bits/stdc++.h>
using namespace std;
#define MAXK 10

int N, K;

struct SCC {
	int hi[MAXK], lo[MAXK], size;
	
	void read() {
		size = 1;
		for(int i=0; i<K; i++) {
			scanf("%d", &lo[i]);
			hi[i] = lo[i];
		}
	}
	
	void merge(SCC o) {
		size += o.size;
		for(int i=0; i<K; i++) {
			lo[i] = min(lo[i], o.lo[i]);
			hi[i] = max(hi[i], o.hi[i]);
		}
	}
};
	
bool operator <(SCC a, SCC b) {
	for(int i=0; i<K; i++) {
		if (a.hi[i] >= b.lo[i]) return false;
	}
	return true;
}

int main() {
	scanf("%d %d", &N, &K);
	
	set<SCC> s;
	for(int i=0; i<N; i++) {
		
		SCC cur;
		cur.read();
		
		set<SCC>::iterator it0 = s.lower_bound(cur);
		set<SCC>::iterator it1 = s.upper_bound(cur);
		while(it0 != it1) {
			cur.merge(*it0);
			s.erase(it0);
			it0 = s.lower_bound(cur);
		}
		s.insert(cur);
		
		printf("%d\n", s.rbegin()->size);
	}
	
	return 0;
}