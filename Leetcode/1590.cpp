class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int totalRem = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            totalRem = (totalRem + nums[i]) % p;
        }
        if (totalRem == 0) {
            return 0;
        }

        unordered_map<int, int> lastIdx;
        int curRem = 0;
        int ans = n;
        lastIdx[0] = -1;
        for (int i = 0; i < n; i++) {
            curRem = (curRem + nums[i]) % p;
            int targetRem = (curRem - totalRem + p) % p;
            if (lastIdx.count(targetRem)) {
                ans = min(ans, i - lastIdx[targetRem]);
            }
            lastIdx[curRem] = i;
        }

        if (ans == n) {
            return -1;
        }
        return ans;
    }
};
