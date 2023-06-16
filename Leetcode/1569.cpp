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

        // Calculate Pascal's triangle
        vector<vector<int>> pascal(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) pascal[i][j] = 1;
                else pascal[i][j] = (pascal[i-1][j] + pascal[i-1][j-1]) % mod;
            }
        }

        // Compute dp
        vector<int> dp(n);
        for (int u = n-1; u >= 0; u--) {
            int l = left[u], r = right[u];
            if (l != -1 && r != -1) {
                dp[u] = (dp[l]*1ll*dp[r]) % mod;
                dp[u] = (dp[u]*1ll*pascal[size[l]+size[r]][size[l]]) % mod;
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
