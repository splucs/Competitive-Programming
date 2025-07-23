class Solution {
private:
    vector<vector<long long>> memo;
    vector<vector<int>> g;
    vector<int> nums;
    int k;

    long long recurse(int u, int p, int c) {
        if (memo[u][c] != -1) {
            return memo[u][c];
        }

        vector<int> children;
        for (int v : g[u]) {
            if (v == p) {
                continue;
            }
            children.push_back(v);
        }

        int n = children.size();
        int num = nums[u];
        if (c == 1) {
            num ^= k;
        }
        if (n == 0) {
            return num;
        }

        vector<vector<long long>> dp(n, vector<long long>(2));
        dp[0][0] = recurse(children[0], u, 0);
        dp[0][1] = recurse(children[0], u, 1);
        for (int i = 1; i < n; i++) {
            int v = children[i];
            for (int ic = 0; ic < 2; ic++) {
                dp[i][ic] = max(dp[i-1][ic] + recurse(v, u, 0), dp[i-1][ic^1] + recurse(v, u, 1));
            }
        }
        long long ans = max(dp[n-1][0] + num, dp[n-1][1] + (num^k));
        memo[u][c] = ans;
        return ans;
    }
public:
    long long maximumValueSum(vector<int>& _nums, int _k, vector<vector<int>>& edges) {
        k = _k;
        nums.swap(_nums);
        int n = nums.size();
        memo.assign(n, vector<long long>(2, -1));
        g.resize(n);
        for (const vector<int>& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        return recurse(0, -1, 0);
    }
};
