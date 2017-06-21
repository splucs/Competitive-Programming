#include <cstdio>
#include <vector>
#define INF (1<<30)
#define MAXN 1009
using namespace std;

typedef long long int ll;

class CHTrick{
private:
    vector<ll> m, n;
    vector<double> p;
public:
    CHTrick(){}
    void clear(){
        m.clear(); n.clear(); p.clear();
    }
    double inter(double nm, double nn, double lm, double ln){
        return (ln - nn)/(nm - lm);
    }
    void push(ll nm, ll nn){
        while(!p.empty() &&
            ((nm == m.back() && nn <= n.back()) ||
            p.back() >= inter(nm, nn, m.back(), n.back()))){
            m.pop_back(); n.pop_back(); p.pop_back();
        }
        p.push_back(p.empty()? 0.0 : inter(nm, nn,
            m.back(), n.back()));
        m.push_back(nm); n.push_back(nn);
    }
    ll query(ll x){
        if (x < 0 || p.empty()) return INF;
        double dx = (double)x;
        int high = p.size()-1, low = 0, mid;
        if (dx >= p[high]) return m[high]*x + n[high];
        while(high > low+1){
            mid = (high+low)/2;
            if (dx < p[mid]) high = mid;
            else low = mid;
        }
        return m[low]*x + n[low];
    }
};

ll w[MAXN], x[MAXN], A[MAXN], B[MAXN], dp[MAXN][MAXN];

int main(){
    int N, K;
    CHTrick cht;
    while(scanf("%d %d", &N, &K)!=EOF){
        for(int i=0; i<N; i++){
            scanf("%lld %lld", x+i, w+i);
            A[i] = w[i] + (i>0 ? A[i-1] : 0);
            B[i] = w[i]*x[i] + (i>0 ? B[i-1] : 0);
            dp[i][1] = x[i]*A[i] - B[i];
        }
        for(int k=2; k<=K; k++){
            dp[0][k] = 0;
            cht.clear();
            for(int i=1; i<N; i++){
                cht.push(-A[i-1], dp[i-1][k-1]+B[i-1]);
                dp[i][k] = x[i]*A[i] - B[i] + cht.query(x[i]);
            }
        }
        printf("%lld\n", dp[N-1][K]);
    }
    return 0;
}