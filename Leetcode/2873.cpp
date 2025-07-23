class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < k; j++) {
                for (int i = 0; i < j; i++) {
                    ans = max(ans, (nums[i] - nums[j])*(long long)nums[k]);
                }
            }
        }
        return ans;
    }
};
