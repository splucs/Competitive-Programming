#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int arr[MAXN], N, sn, Q;
bool app[MAXN];

struct query {
	int l, r, id;
	int ans;
	query() {l=r=id=-1;}
	query(int _id, int _l, int _r) {
		r = _r; l = _l; id = _id;
	}
} qrs[MAXN];
bool lrcomp(query a, query b) {
	if (a.l/sn != b.l/sn) return a.l/sn < b.l/sn;
	return a.r > b.r;
}
bool idcomp(query a, query b) {
	return a.id < b.id;
}

int freq[MAXN], curAns;
void check(int i) {
	if (i < 0 || i >= N) return;
	if (app[i]) {
		if (freq[arr[i]] == 2) curAns -= 2;
		else if (freq[arr[i]] > 2) curAns--;
		freq[arr[i]]--;
	}
	else {
		freq[arr[i]]++;
		if (freq[arr[i]] == 2) curAns += 2;
		else if (freq[arr[i]] > 2) curAns++;
	}
	app[i] = !app[i];
}

void mo() {
	sn = sqrt(N);
	sort(qrs, qrs+Q, lrcomp);
	memset(&freq, 0, sizeof freq);
	memset(&app, false, sizeof app);
	int l = 1, r = 0;
	curAns = 0;
	for(int i=0; i<Q; i++) {
		query &q = qrs[i];
		while(r > q.r) check(r--);
		while(r < q.r) check(++r);
		while(l < q.l) check(l++);
		while(l > q.l) check(--l);
		q.ans = curAns;
	}
	sort(qrs, qrs+Q, idcomp);
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) scanf("%d", &arr[i]);
	scanf("%d", &Q);
	for(int j=0; j<Q; j++) {
		scanf("%d %d", &qrs[j].l, &qrs[j].r);
		qrs[j].l--; qrs[j].r--;
		qrs[j].id = j;
	}
	mo();
	for(int j=0; j<Q; j++) printf("%d\n", qrs[j].ans);
	return 0;
}