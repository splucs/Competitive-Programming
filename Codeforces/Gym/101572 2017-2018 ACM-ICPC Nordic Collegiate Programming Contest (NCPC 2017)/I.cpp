#include <bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define mp make_pair
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
const int N = 1e3+5;

int cnt=1, n, k;
int vis[N], dis[N];
char st[N], st2[N];
map <string, int> id;
map <int, string> idrev;
vi adj[N], ans;

int main () {
    scanf("%d ", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s ", st);
        if (!id.count(st)) id[st] = cnt++, idrev[cnt-1] = st;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%s %d ", st, &k);
        for (int j = 0; j < k; j++) {
            scanf("%*s ");
            int ok = 1;
            while (ok) {
                scanf("%s", st2);
                if (st2[strlen(st2)-1] != ',') ok = 0;
                if (ok) {
                    int n = strlen(st2);
                    st2[n-1] = 0;
                }
                adj[id[st]].pb(id[st2]);
                //printf("got %s %d\n", st2, id[st2]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cl(dis, 0);
        cl(vis, 0);
        queue <int> q;
        q.push(i);
        vis[i] = i;
        vi cur;

        while (!cur.size() and q.size()) {
            int x = q.front(); q.pop();
            for (auto v : adj[x]) {
                if (v == i) {
                    while (x != i) cur.push_back(x), x = vis[x];
                    cur.push_back(i);
                    break;
                } else  if (!vis[v]) {
                    vis[v] = x;
                    q.push(v), dis[v] = dis[x]+1;
                }
            }
        }

        if (cur.size() and (!ans.size() or cur.size() < ans.size()))
            ans = cur;
    }

    reverse(ans.begin(), ans.end());
    if (!ans.size()) printf("SHIP IT");
    else for (auto x : ans) printf("%s ", idrev[x].c_str()); printf("\n");
    return 0;
}