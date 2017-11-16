#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

set<int> available;
char w[MAXN], tipo[MAXN];
vector<vector<int> > viz;

void visit(int v) {
	available.erase(v);
	w[v] = 'S';
	queue<int> q;
	
	q.push(v);
	int aux;
	
	while(!q.empty()) {
		v = q.front();
		q.pop();
		
		if (tipo[v] == 'C') {
			for (int i = 0; i < (int)viz[v].size(); i++) {
				aux = viz[v][i];
				if (available.find(aux) != available.end()) {
					if (w[v] == 'S') w[aux] = 'V';
					else w[aux] = 'S';
					
					available.erase(aux);
					q.push(aux);
				}
			}
		} else {
			set<int> removed;
			
			for (int i = 0; i < (int)viz[v].size(); i++) {
				aux = viz[v][i];
				if (available.find(aux) != available.end()) {
					available.erase(aux);
					removed.insert(aux);
				}
			}
			
			for (set<int>::iterator it = available.begin(); it != available.end(); it++) {
				if (w[v] == 'S') w[*it] = 'V';
				else w[*it] = 'S';
					
				q.push(*it);
			}
			available.clear();
			for (set<int>::iterator it = removed.begin(); it != removed.end(); it++) {
				available.insert(*it);
			}
			removed.clear();
		}
	}
}

int main() {
	int n, k, val;
	bool possible;
	
	while(scanf("%d", &n) != EOF) {
		available.clear();
		viz.clear();
		viz.resize(n+5);
		possible = true;
		
		for (int i = 1; i <= n; i++) {
			available.insert(i);
			scanf(" %c %d", &tipo[i], &k);

			for (int j = 0; j < k; j++) {
				scanf("%d", &val);
				viz[i].push_back(val);
			}
			if (tipo[i] == 'C' && k == 0) possible = false;
			else if (tipo[i] == 'N' && k == n-1) possible = false;
		}
		
		for (int i = 1; possible && i <= n; i++) {
			if (available.find(i) != available.end()) {
				visit(i);
			}
		}
		
		if (!possible) printf("Impossible\n");
		else {
			for (int i = 1; i <= n; i++) printf("%c", w[i]);
			printf("\n");
		}
	}
}