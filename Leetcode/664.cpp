class Solution {
private:
    vector<vector<int>> dp;
    string s;
    int DP(int l, int r) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int &ans = dp[l][r];
        if (l == r) {
            return ans = 0;
        }
        
        int i = l, j = r;
        for (; i < j && s[i] == s[l]; i++);
        for (; i < j && s[j-1] == s[l]; j--);

        ans = 1 + DP(i, j);

        for (int kl = i; kl < j; kl++) {
            if (s[kl] != s[l]) {
                continue;
            }
            int kr = kl;
            while (s[kl] == s[kr+1]) kr++;
            ans = min(ans, DP(i, kl) + DP(kr, j));
            kl = kr;
        }
        return ans;
    }
public:
    int strangePrinter(string _s) {
        s.swap(_s);
        int n = s.size();
        dp.assign(n+1, vector<int>(n+1, -1));
        return DP(0, n);
    }
};
