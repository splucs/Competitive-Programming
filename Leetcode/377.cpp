class Solution {
    vector<int> dp;
    vector<int> coins;

    int recurse(int n) {
        int &ans = dp[n];
        if (ans >= 0) return ans;

        ans = 0;
        for (int coin : coins) {
            if (n >= coin) ans += recurse(n-coin);
        }
        return ans;
    }
public:
    int combinationSum4(vector<int>& nums, int target) {
        dp.assign(target+1, -1);
        coins = nums;
        dp[0] = 1;
        return recurse(target);
    }
};
