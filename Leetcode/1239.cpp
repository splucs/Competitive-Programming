class Solution {
private:
    int ans, n;
    vector<int> mask;
    vector<vector<bool>> viz;
    int dp(int i, int m) {
        if (i == n) {
            return __builtin_popcount(m);
        }

        if (viz[i][m]) {
            return 0;
        }
        viz[i][m] = true;

        int ans = dp(i+1, m);
        if ((m & mask[i]) == 0) {
            ans = max(ans, dp(i+1, m|mask[i]));
        }
        return ans;
    }
public:
    int maxLength(vector<string>& arr) {
        n = arr.size();
        mask.assign(n, 0);
        for (int i = 0; i < n; i++) {
            for (char c : arr[i]) {
                mask[i] |= (1 << (c-'a'));
            }
            if (arr[i].size() != __builtin_popcount(mask[i])) {
                mask[i] = 0;
            }
        }
        viz.assign(n, vector<bool>(1<<26, false));
        return dp(0, 0);
    }
};
