#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll sx1[4], sx2[4], sy1[4], sy2[4];

ll sqrint(ll x1b, ll y1b, ll x1t, ll y1t, ll x2b, ll y2b, ll x2t, ll y2t) {
    ll dx = min(x1t,x2t)-max(x1b,x2b);
    ll dy = min(y1t,y2t)-max(y1b,y2b);
    if (dx < 0 || dy < 0) return 0;
    return dx*dy;
}

ll simulate(const ll dx, const ll dy) {
    for(int i=0; i<4; i++) {
        sx1[i] += dx;
        sy1[i] += dy;
    }
    ll ans = 0;
    for(int i1=0; i1<3; i1++){
        for(int j1=0; j1<3; j1++){
            if (i1 == 1 && j1 == 1) continue;
            for(int i2=0; i2<3; i2++){
                for(int j2=0; j2<3; j2++){
                    if (i2 == 1 && j2 == 1) continue;
                    ll cur = sqrint(sx1[i1], sy1[j1], sx1[i1+1], sy1[j1+1], sx2[i2], sy2[j2], sx2[i2+1], sy2[j2+1]);
                    ans += cur;
                }
            }
        }
    }
    for(int i=0; i<4; i++) {
        sx1[i] -= dx;
        sy1[i] -= dy;
    }
    return ans;
}

int main() {
    freopen("frames.in", "r", stdin);
    freopen("frames.out", "w", stdout);

    scanf("%I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d", &sx1[0], &sy1[0], &sx1[3], &sy1[3], &sx1[1], &sy1[1], &sx1[2], &sy1[2]);
    if (sx1[0] > sx1[3]) swap(sx1[0], sx1[3]);
    if (sy1[0] > sy1[3]) swap(sy1[0], sy1[3]);
    if (sx1[1] > sx1[2]) swap(sx1[1], sx1[2]);
    if (sy1[1] > sy1[2]) swap(sy1[1], sy1[2]);
    scanf("%I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d", &sx2[0], &sy2[0], &sx2[3], &sy2[3], &sx2[1], &sy2[1], &sx2[2], &sy2[2]);
    if (sx2[0] > sx2[3]) swap(sx2[0], sx2[3]);
    if (sy2[0] > sy2[3]) swap(sy2[0], sy2[3]);
    if (sx2[1] > sx2[2]) swap(sx2[1], sx2[2]);
    if (sy2[1] > sy2[2]) swap(sy2[1], sy2[2]);
    ll ans = 0, adx, ady;
    for(int i1=0; i1<4; i1++){
        for(int j1=0; j1<4; j1++){
            for(int i2=0; i2<4; i2++){
                for(int j2=0; j2<4; j2++){
                    ll dx = sx2[i2] - sx1[i1];
                    ll dy = sy2[j2] - sy1[j1];
                    ll cur = simulate(dx, dy);
                    if (cur > ans){
                        ans = cur;
                        adx = dx;
                        ady = dy;
                    }
                }
            }
        }
    }
    printf("%I64d\n%I64d %I64d\n", ans, -adx, -ady);

	fclose(stdin);
	fclose(stdout);
	return 0;
}