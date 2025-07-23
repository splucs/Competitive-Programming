class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int lastInvalid = -1;
        int lastMax = -1;
        int lastMin = -1;
        int n = nums.size();
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] > maxK || nums[i] < minK) {
                lastInvalid = i;
            }
            if (nums[i] == maxK) {
                lastMax = i;
            }
            if (nums[i] == minK) {
                lastMin = i;
            }
            int lastValid = min(lastMax, lastMin);
            if (lastValid > lastInvalid) {
                ans += lastValid - lastInvalid;
            }
        }
        return ans;
    }
};
