#include <bits/stdc++.h>
using namespace std;

void mask2board(int mask, int board[3][3]) {
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			board[i][j] = mask%3;
			mask /= 3;
		}
	}
}

int board2mask(const int board[3][3]) {
	int p = 1, mask = 0;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			mask += board[i][j]*p;
			p *= 3;
		}
	}
	return mask;
}

set<int> reachable;
vector<int> allstates;
vector<int> operations;

int join(int mask1, int mask2, int opmask) {
	int tab1[3][3], tab2[3][3], op[3][3], ans[3][3];
	mask2board(mask1, tab1);
	mask2board(mask2, tab2);
	mask2board(opmask, op);
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			ans[i][j] = op[tab1[i][j]][tab2[i][j]];
		}
	}
	return board2mask(ans);
}

void addstate(int mask);

void merge(int mask1, int mask2) {
	for(int i=0; i<(int)operations.size(); i++) {
		addstate(join(mask1, mask2, operations[i]));
	}
}

void addstate(const int mask) {
	if (reachable.count(mask)) return;
	int n = allstates.size();
	allstates.push_back(mask);
	reachable.insert(mask);
	
	for(int i=0; i<n; i++) {
		merge(mask, allstates[i]);
		merge(allstates[i], mask);
	}
}

int op1[3][3] = {{0, 0, 0}, {0, 1, 1}, {0, 1, 2}};
int op2[3][3] = {{0, 1, 2}, {1, 1, 2}, {2, 2, 2}};
int op3[3][3] = {{2, 2, 2}, {1, 2, 2}, {0, 1, 2}};
int op4[3][3] = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
int st1[3][3] = {{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
int st2[3][3] = {{0, 1, 2}, {0, 1, 2}, {0, 1, 2}};

int main() {
	
	operations.push_back(board2mask(op1));
	operations.push_back(board2mask(op2));
	operations.push_back(board2mask(op3));
	operations.push_back(board2mask(op4));
	addstate(board2mask(st1));
	addstate(board2mask(st2));
	
	int N;
	while(scanf("%d", &N) != EOF) {
		
		while(N --> 0) {
			
			char c;
			int board[3][3];
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					scanf(" %c", &c);
					if (c == 'F') board[i][j] = 0;
					if (c == 'U') board[i][j] = 1;
					if (c == 'T') board[i][j] = 2;
				}
			}
			
			int mask = board2mask(board);
			if (reachable.count(mask)) printf("definable\n");
			else printf("undefinable\n");
		}
	}
	
	return 0;
}