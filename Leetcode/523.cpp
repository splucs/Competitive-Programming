class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_set<int> seen;
        int sum = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            int newSum = (sum + nums[i]) % k;
            if (seen.count(newSum)) {
                return true;
            }
            seen.insert(sum);
            sum = newSum;
        }
        return false;
    }
};
