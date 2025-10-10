class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        vector<bool> seen(101, false);
        int ans = 0;
        for (int num : nums) {
            if (num > 0 && !seen[num]) {
                ans++;
            }
            seen[num] = true;
        }
        return ans;
    }
};
