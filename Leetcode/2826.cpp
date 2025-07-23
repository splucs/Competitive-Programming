#define MAX_NUM 3
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        int cnt[MAX_NUM], dp[MAX_NUM], minDp[MAX_NUM];
        memset(&cnt, 0, sizeof cnt);
        memset(&minDp, 0, sizeof cnt);
        for (int i = 0; i < n; i++) {
            cnt[nums[i]-1]++;
            dp[0] = i+1 - cnt[0];
            for (int u = 1; u < MAX_NUM; u++) {
                minDp[u] = min(minDp[u], dp[u-1] - (i+1 - cnt[u]));
                dp[u] = i+1 - cnt[u] + minDp[u];
            }
        }
        return dp[MAX_NUM-1];
    }
};
