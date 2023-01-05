#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

struct problem {
	int time;
	int prob;
	int id;
};

bool operator < (problem a, problem b) {
	return a.time*b.prob < b.time*a.prob;
}

typedef pair<int, int> dd; //problems, penalty
int Tmax, N;
problem arr[MAXN];

dd dp[MAXN][MAXN];
int A[MAXN][MAXN]; 

int main() {
	scanf("%d %d", &N, &Tmax);
	for(int i = 0; i < N; i++) {
		scanf("%d %d", &arr[i].time, &arr[i].prob);
		arr[i].id = i+1;
	}
	sort(arr, arr+N);

	for(int t = 0; t <= Tmax; t++) {
		for(int i = N; i >= 0; i--) {
			if (t == 0 || i == N) {
				dp[t][i] = dd(0, 0);
				A[t][i] = -1;
			}
			else {
				//not try
				dp[t][i] = dp[t][i+1];
				A[t][i] = A[t][i+1];

				//try
				if (t >= arr[i].time) {
					dd opt = dp[t-arr[i].time][i+1];
					opt.first += arr[i].prob;
					opt.second += arr[i].prob*(arr[i].time + Tmax - t);
					if (dp[t][i].first < opt.first ||
						(dp[t][i].first == opt.first && dp[t][i].second > opt.second)) {
						dp[t][i] = opt;
						A[t][i] = i;
					}
				}
			}
		}
	}

	vector<int> ans;
	int t = Tmax;
	int i = A[Tmax][0];
	while(i != -1) {
		ans.push_back(i);
		t -= arr[i].time;
		i = A[t][i+1];
	}

	printf("%u\n", ans.size());
	for(int i = 0; i < (int)ans.size(); i++) {
		printf("%d ", arr[ans[i]].id);
	}
	printf("\n");

	return 0;
}