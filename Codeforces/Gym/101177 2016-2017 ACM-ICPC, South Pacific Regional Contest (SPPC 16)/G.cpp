#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

struct task {
	int t, mask, prio, st, stamp;
};

bool operator <(task a, task b) {
	return a.prio < b.prio;
}

typedef long long ll;
vector<task> students[MAXN];
map<ll, vector<task> > endtsks;
int N, d[MAXN], curstate, am[3];
char buffer[MAXN];
int added[MAXN], started[MAXN];
ll ans[MAXN];
priority_queue<task> avail[8];

void addtask(int i) {
	if (added[i] == d[i]) return;
	for(int mask = 0; mask < 8; mask++) {
		if ((mask & students[i][added[i]].mask) == students[i][added[i]].mask)
			avail[mask].push(students[i][added[i]]);
	}
	added[i]++;
}

int main() {
	
	while(scanf(" %d", &N) != EOF) {
		curstate = 0;
		for(int i=0; i<3; i++) {
			scanf("%d", &am[i]);
			if (am[i] > 0) curstate |= (1<<i);
		}
		for(int i=0; i<N; i++) {
			scanf("%d", &d[i]);
		}
		for(int i=0; i<N; i++) {
			students[i].clear();
			added[i] = started[i] = 0;
			for(int j=0; j<d[i]; j++) {
				task tsk;
				tsk.st = i;
				tsk.mask = 0;
				tsk.stamp = j;
				scanf(" %d %d", &tsk.t, &tsk.prio);
				gets(buffer);
				int len = strlen(buffer);
				for(int it=0, last = 0; it<len; it++) {
					if (buffer[it] == ' ') last = it;
					if (it - last == 4) {
						if (buffer[it] == 'e') tsk.mask |= 1;
						if (buffer[it] == 'c') tsk.mask |= 2;
						if (buffer[it] == 'p') tsk.mask |= 4;
					}
				}
				students[i].push_back(tsk);
			}
		}
		for(int mask = 0; mask < 8; mask++) avail[mask] = priority_queue<task>();
		endtsks.clear();
		
		for(int i=0; i<N; i++) {
			addtask(i);
		}
		
		ll t = 0;
		while(true) {
			
			//printf("state = %d\n", curstate);
			
			if (endtsks.count(t)) {
				vector<task>::iterator begit = endtsks[t].begin();
				vector<task>::iterator endit = endtsks[t].end();
				for(vector<task>::iterator it = begit; it != endit; it++) {
					task tsk = *it;
					//printf("task from %d, stamp %d, mask %d, ended at %d\n", tsk.st, tsk.stamp, tsk.mask, t);
					for(int i=0; i<3; i++) {
						if (tsk.mask & (1<<i)) am[i]++;
					}
					curstate |= tsk.mask;
					if (added[tsk.st] == d[tsk.st]) ans[tsk.st] = t;
					else addtask(tsk.st);
				}
			}
			
			//printf("state now at %d\n", curstate);
			
			while(true) {
				while(!avail[curstate].empty()) {
					task tsk = avail[curstate].top();
					if (started[tsk.st] <= tsk.stamp) break;
					avail[curstate].pop();
				}
				if (avail[curstate].empty()) break;
				
				task tsk = avail[curstate].top();
				avail[curstate].pop();
				for(int i=0; i<3; i++) {
					if (tsk.mask & (1<<i)) {
						am[i]--;
						if (am[i] == 0) curstate ^= (1<<i);
					}
				}
				endtsks[t+tsk.t].push_back(tsk);
				started[tsk.st]++;
				
				//printf("task from %d, stamp %d, mask %d, started at %d\n", tsk.st, tsk.stamp, tsk.mask, t);
			}
			
			if (endtsks.upper_bound(t) == endtsks.end()) break;
			t = endtsks.upper_bound(t)->first;
		}
		
		for(int i=0; i<N; i++) printf("%I64d ", ans[i]);
		printf("\n");
	}
	
	return 0;
}