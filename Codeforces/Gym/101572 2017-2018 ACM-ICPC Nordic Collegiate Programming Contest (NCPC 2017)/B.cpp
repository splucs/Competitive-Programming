#include <bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define cl(x, v) memset((x), (v), sizeof(x))
#define db(x) cerr << #x << " == " << x << endl
#define dbs(x) cerr << x << endl
#define _ << ", " <<

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vii;

const ld EPS = 1e-9, PI = acos(-1.);
const int INF = 0x3f3f3f3f, MOD = 1e9+7;
const int N = 1e5+5;

int n, v1[N], v2[N], id[N], ans[4], cur[4];
char nm[50];
map<int, string> mp;

bool cp(int i, int j) { return v2[i] < v2[j]; }

int main () {
    scanf("%d", &n);

    for(int i=0; i<n; ++i) {
        int v11, v12, v22, v21;
        scanf("%s %d.%d %d.%d", nm, &v11, &v12, &v21, &v22);
        v1[i] = 100*v11 + v12;
        v2[i] = 100*v21 + v22;
        mp[i] = nm;
        id[i] = i;
    }

    sort(id, id+n, cp);
    for(int i=0; i<4; ++i) ans[i] = i;

    for(int i=0; i<n; ++i) {
        cur[0] = id[i];

        for(int k=1, j=0; k<4; ++j) {
            if (j == i) continue;
            cur[k++] = id[j];
        }

        int sm1 = v1[cur[0]], sm2 = v1[ans[0]];
        for(int i=1; i<4; ++i) sm1 += v2[cur[i]], sm2 += v2[ans[i]];
        if (sm1 < sm2) for(int i=0; i<4; ++i) ans[i] = cur[i];
    }

    int sm = v1[ans[0]];
    for(int i=1; i<4; ++i) sm += v2[ans[i]];
    printf("%d.%02d\n", sm/100, sm%100);
    for(int i=0; i<4; ++i) printf("%s\n", mp[ans[i]].c_str());
    return 0;
}