#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int N;
char rank[MAXN][10], cur[10], minrank[10];
int diff[MAXN], mp[10], arr[10];

int bubblesort() {
	int ans = 0;
	for(int i=0; i<5; i++) {
		for(int j=1; j<5; j++) {
			if (arr[j] < arr[j-1]){
				swap(arr[j], arr[j-1]);
				ans++;
			}
		}
	}
	return ans;
}

int main() {
	int mindiff, curdiff;
	while(scanf("%d", &N), N) {
		for(int i=0; i<N; i++) {
			scanf(" %s", rank[i]);
		}
		mindiff = 1000009;
		for(int k=0; k<5; k++) cur[k] = 'A' + k;
		do {
			for(int k=0; k<5; k++) mp[cur[k] - 'A'] = k;
			curdiff = 0;
			for(int j=0; j<N; j++) {
				for(int k=0; k<5; k++) arr[k] = mp[rank[j][k] - 'A'];
				curdiff += bubblesort();
			}
			if (curdiff < mindiff) {
				mindiff = curdiff;
				strcpy(minrank, cur);
			}
		} while(next_permutation(cur, cur+5));
		
		printf("%s is the median ranking with value %d.\n", minrank, mindiff);
	}
	return 0;
}