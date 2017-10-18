#include <bits/stdc++.h>
using namespace std;
#define INF 100000009
#define MAXN 55

// TopCoder SRM 372 Round 1 - Division I, Level Three
class RadarGuns {
private:
int cost[MAXN][MAXN]; 		// cost matrix
int N;			  			// n elements to match in each side
int lx[MAXN], ly[MAXN];  	// labels of X and Y parts
int xy[MAXN], yx[MAXN];   	// xy[x] - vertex that is matched with x,
							// yx[y] - vertex that is matched with y
bool S[MAXN], T[MAXN]; 		// sets S and T in algorithm
int slack[MAXN], slackx[MAXN]; // slackx[y] such a vertex, that
 				// l(slackx[y]) + l(y) - w(slackx[y],y) = slack[y]
int prev[MAXN]; //array for memorizing alternating paths

// O(n^3)Hungarian algorithm for max weight bipartite matching
// cost[i][j] contains cost of matching i with j
// For minimum cost, set cost[i][j] to -cost[i][j] or M - cost[i][j]

void init_labels() {
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			lx[x] = max(lx[x], cost[x][y]);
		}
	}
}

void update_labels() {
	int delta = INF;
 	for (int y = 0; y < N; y++) {
 		if (!T[y]) delta = min(delta, slack[y]);
 	}
 	for (int x = 0; x < N; x++) {
 		if (S[x]) lx[x] -= delta;
 	}
	for (int y = 0; y < N; y++) {
 		if (T[y]) ly[y] += delta;
		if (!T[y]) slack[y] -= delta;
 	}
}

void add_to_tree(int x, int prevx)  {
	S[x] = true; //add x to S
	prev[x] = prevx; //we need this when augmenting
	for (int y = 0; y < N; y++) {
		if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
 			slack[y] = lx[x] + ly[y] - cost[x][y];
 			slackx[y] = x;
 		}
 	}
}

void augment(int max_match) {
	if (max_match == N) return; //check wether matching is already perfect
	int x, y, root = 0;				//just counters and root vertex
 	queue<int> q;				//q - queue for bfs, wr,rd - write and read
	memset(S, false, sizeof(S)); //init set S
	memset(T, false, sizeof(T)); //init set T
	memset(prev, -1, sizeof(prev)); //init set prev - for the alternating tree
 	for (x = 0; x < N; x++) {
		if (xy[x] == -1) {
			q.push(x);
			root = x;
			prev[x] = -2;
 			S[x] = true;
 			break;
 		}
 	}

 	for (y = 0; y < N; y++) {
		slack[y] = lx[root] + ly[y] - cost[root][y];
		slackx[y] = root;
	}

	while (true) {
 		while (!q.empty()) {
			x = q.front(); q.pop();
			for (y = 0; y < N; y++) { //iterate through all edges in equality graph
				if (cost[x][y] == lx[x] + ly[y] && !T[y]) {
					if (yx[y] == -1) break;
					T[y] = true;
 					q.push(yx[y]);
					add_to_tree(yx[y], x);
				}
			}
 			if (y < N) break;
 		}
 		if (y < N) break; //augmenting path found!

 		update_labels(); //augmenting path not found, so improve labeling
		while (!q.empty()) q.pop(); 
		for (y = 0; y < N; y++) {
			if (!T[y] && slack[y] == 0) {
				if (yx[y] == -1) {
 					x = slackx[y];
 					break;
 				} else {
 					T[y] = true; //else just add y to T,
 					if (!S[yx[y]]) {
 						q.push(yx[y]);
						add_to_tree(yx[y], slackx[y]); //and add edges (x,y) and (y,
					}
 				}
 			}
 		}
 		if (y < N) break; //augmenting path found!
 	}

 	if (y < N) {
 		for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
 			ty = xy[cx];
			yx[cy] = cx;
			xy[cx] = cy;
 		}
		augment(max_match+1);
 	}
}

int maximumWeightedMatching() {
	memset(xy, -1, sizeof(xy)); 
	memset(yx, -1, sizeof(yx));
 	init_labels();
 	augment(0);
 	
 	int ret = 0;
	for (int x = 0; x < N; x++) ret += cost[x][xy[x]];
 	return ret;
}
    
public:
     vector <int> getRange(vector <int> enterTimes, vector <int> exitTimes, int speedTime, int fineCap) {
         N = enterTimes.size();
         sort(enterTimes.begin(), enterTimes.end());
         sort(exitTimes.begin(), exitTimes.end());
         vector<int> sol;
         for (int i = 0; i < N; i++) {
             if (enterTimes[i] >= exitTimes[i]) return sol;
         }
         
         int M = 1000000;
         for (int i = 0; i < N; i++) {
             for (int j = 0; j < N; j++) {
             	if (enterTimes[i] < exitTimes[j] && exitTimes[j] - enterTimes[i] < speedTime) cost[i][j] = M - min((speedTime-exitTimes[j]+enterTimes[i])*(speedTime-exitTimes[j]+enterTimes[i]), fineCap);
                else if (enterTimes[i] < exitTimes[j] && exitTimes[j] - enterTimes[i] >= speedTime) cost[i][j] = M;
                else cost[i][j] = -INF;
             }
         }
         sol.push_back(N*M - maximumWeightedMatching());
         
         for (int i = 0; i < N; i++) {
             for (int j = 0; j < N; j++) {
             	if (enterTimes[i] < exitTimes[j] && exitTimes[j] - enterTimes[i] < speedTime) cost[i][j] = min((speedTime-exitTimes[j]+enterTimes[i])*(speedTime-exitTimes[j]+enterTimes[i]), fineCap);
                else if (enterTimes[i] < exitTimes[j] && exitTimes[j] - enterTimes[i] >= speedTime) cost[i][j] = 0;
                else cost[i][j] = -INF;
             }
         }
         sol.push_back(maximumWeightedMatching());
         
         return sol;
     }
};
