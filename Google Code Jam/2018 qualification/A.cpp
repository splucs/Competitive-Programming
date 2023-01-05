#include <bits/stdc++.h>
using namespace std;
#define MAXN 39
#define INF (1 << 30)

char arr[MAXN];
typedef long long ll;
int N;

ll simulate() {
  ll pwr = 1;
  ll dmg = 0;
  for(int i = 0; i < N; i++) {
    if (arr[i] == 'C') pwr <<= 1;
    if (arr[i] == 'S') dmg += pwr;
  }
  return dmg;
}

int ans;
bool increase() {
  for(int i = N-1; i > 0; i--) {
    if (arr[i] == 'S' && arr[i-1] == 'C') {
      ans++;
      swap(arr[i-1], arr[i]);
      return true;
    }
  }
  return false;
}

int main() {
  int T;
  ll D;
  scanf("%d", &T);
  for(int caseNo = 1; caseNo <= T; caseNo++) {
    scanf("%lld %s", &D, &arr);
    N = strlen(arr);
    ans = 0;
    while(simulate() > D) {
      if (!increase()) break;
    }
    if (simulate() <= D) printf("Case #%d: %d\n", caseNo, ans);
    else printf("Case #%d: IMPOSSIBLE\n", caseNo);
  }
  return 0;
}