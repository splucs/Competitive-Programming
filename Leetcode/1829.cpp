class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        int n = nums.size();
        vector<int> ans(n);
        int fullMask = (1<<maximumBit)-1, cur = 0;
        for (int i = 0; i < n; i++) {
            cur ^= nums[i];
            ans[n-i-1] = fullMask ^ cur;
        }
        return ans;
    }
};
