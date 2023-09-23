class Solution {
private:
    bool isPredecessor(string &from, string &to) {
        int n = from.size();
        int m = to.size();
        for (int i = 0, j = 0; i < n; i++, j++) {
            while (j < m && to[j] != from[i]) j++;
            if (j == m) return false;
        }
        return true;
    }
public:
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> idsBySize(17);
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            int s = words[i].size();
            idsBySize[s].push_back(i);
        }
        for (int s = 1; s <= 16; s++) {
            for (int i : idsBySize[s]) {
                for (int j : idsBySize[s-1]) {
                    if (isPredecessor(words[j], words[i])) {
                        dp[i] = max(dp[i], 1 + dp[j]);
                    }
                }
            }
        }
        int ans = 1;
        for (int d : dp) ans = max(ans, d);
        return ans;
    }
};
