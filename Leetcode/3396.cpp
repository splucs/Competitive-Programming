class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        vector<bool> seen(101, false);
        int i = nums.size()-1;
        for (; i >= 0 && !seen[nums[i]]; i--) {
            seen[nums[i]] = true;
        }
        return (i+3)/3;
    }
};
