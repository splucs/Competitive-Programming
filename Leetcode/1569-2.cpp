template <typename T>
T extGcd(T a, T b, T& x, T& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        T g = extGcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}
 
template <typename T>
T modInv(T a, T m) {
    T x, y;
    extGcd(a, m, x, y);
    return (x % m + m) % m;
}

class Solution {
private:
    vector<int> left, right;
public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        int mod = 1e9+7;

        // Build BST
        left.assign(n, -1);
        right.assign(n, -1);
        for (int u = 1; u < n; u++) {
            int cur = 0;
            while(true) {
                if (nums[u] < nums[cur]) {
                    if (left[cur] == -1) {
                        left[cur] = u;
                        break;
                    }
                    cur = left[cur];
                } else {
                    if (right[cur] == -1) {
                        right[cur] = u;
                        break;
                    }
                    cur = right[cur];
                }
            }
        }

        // Calculate size of subtrees
        vector<int> size(n, 0);
        for (int u = n-1; u >= 0; u--) {
            int l = left[u], r = right[u];
            size[u] = 1;
            if (l != -1) size[u] += size[l];
            if (r != -1) size[u] += size[r];
        }

        // Calculate factorials
        vector<int> fac(n+1);
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = (fac[i-1]*1ll*i)%mod;
        }

        // Compute dp
        vector<int> dp(n);
        for (int u = n-1; u >= 0; u--) {
            int l = left[u], r = right[u];
            if (l != -1 && r != -1) {
                // Calcualte pascal with pascal(n, k) = n!/(k!*(n-k)!)
                int den = (fac[size[l]]*1ll*fac[size[r]])%mod;
                int num = fac[size[l]+size[r]];
                int pascal = (num*1ll*modInv(den, mod))%mod;
                dp[u] = (dp[l]*1ll*dp[r]) % mod;
                dp[u] = (dp[u]*1ll*pascal) % mod;
            } else if (l != -1) {
                dp[u] = dp[l];
            } else if (r != -1) {
                dp[u] = dp[r];
            } else {
                dp[u] = 1;
            }
        }

        return (dp[0]-1+mod)%mod;
    }
};
