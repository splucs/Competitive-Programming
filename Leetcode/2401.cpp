class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int mask = 0, n = nums.size();
        int ans = 1;
        for (int i = 0, j = 0; j < n; j++) {
            while(mask & nums[j]) {
                mask ^= nums[i++];
            }
            mask ^= nums[j];
            ans = max(ans, j-i+1);
        }
        return ans;
    }
};
