#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> arr, sub[2], ans;

int main() {
  int T;
  scanf("%d", &T);
  for(int caseNo = 1; caseNo <= T; caseNo++) {
    scanf("%d", &N);
    arr.resize(N);
    ans.resize(N);
    sub[0].clear();
    sub[1].clear();
    for(int i = 0; i < N; i++) {
      scanf("%d", &arr[i]);
      sub[i % 2].push_back(arr[i]);
    }
    sort(arr.begin(), arr.end());
    sort(sub[0].begin(), sub[0].end());
    sort(sub[1].begin(), sub[1].end());
    int it1 = 0, it2 = 0;
    bool ok = true;
    for(int i = 0; i < N; i++) {
      if (i % 2 == 0) {
        ans[i] = sub[0][it1++];
      }
      else {
        ans[i] = sub[1][it2++];
      }
      if (ans[i] != arr[i]) {
        printf("Case #%d: %d\n", caseNo, i);
        ok = false;
        break;
      }
    }
    if (ok) printf("Case #%d: OK\n", caseNo);
  }
  return 0;
}