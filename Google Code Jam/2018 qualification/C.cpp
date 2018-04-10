#include <bits/stdc++.h>
using namespace std;
#define MAXN 15

int N, M;
int field[MAXN][MAXN];
int count(int i, int j) {
  int ans = 0;
  for(int it = i-1; it <= i+1; it++) {
    for(int jt = j-1; jt <= j+1; jt++) {
      if (field[it][jt] == 0) ans++;
    }
  }
  return ans;
}

int i, j;
void find() {
  int mx = -1;
  for(int it = 2; it < N; it++) {
    for(int jt = 2; jt < M; jt++) {
      int cur = count(it, jt);
      if (cur > mx) {
        i = it;
        j = jt;
        mx = cur;
        if (mx == 9) return;
      }
    }
  }
}

int main() {
  int T, A;
  scanf("%d", &T);
  for(int caseNo = 1; caseNo <= T; caseNo++) {
    scanf("%d", &A);
    if (A < 9) A = 9;
    M = N = sqrt(A);
    if (N*M < A) M++;
    memset(&field, 0, sizeof field);

    int il = -1, jl = -1;
    while(true) {
      find();
      printf("%d %d\n", i, j);
      fflush(stdout);
      scanf("%d %d", &il, &jl);

      //error
      if (il == -1 && jl == -1) return 0;
      //ok
      if (il == 0 && jl == 0) break;
      field[il][jl] = 1;
    }
  }
  return 0;
}