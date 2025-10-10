class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int n = nums.size();
        int fullMask = 1 << n, maxMask = 0;
        int ans = 0;
        for (int mask = 1; mask < fullMask; mask++) {
            int curMask = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    curMask |= nums[i];
                }
            }

            if (curMask > maxMask) {
                maxMask = curMask;
                ans = 0;
            }
            if (curMask == maxMask) {
                ans++;
            }
        }
        return ans;
    }
};
