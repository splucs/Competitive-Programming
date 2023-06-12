class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int last = 0;
        int n = nums.size();
        vector<string> ans;
        for (int i = 1; i <= n; i++) {
            if (i < n && nums[i] == nums[i-1] + 1) continue;
            if (last == i-1) {
                ans.push_back(to_string(nums[last]));
            } else {
                ans.push_back(to_string(nums[last]) + "->" + to_string(nums[i-1]));
            }
            last = i;
        }
        return ans;
    }
};
