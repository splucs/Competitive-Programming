class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        vector<int> freq(n+1, 0);
        for (int i = 0; i < n; i++) {
            freq[nums[i]]++;
        }
        int repeated, missing;
        for (int i = 1; i <= n; i++) {
            if (freq[i] > 1) {
                repeated = i;
            } else if (freq[i] < 1) {
                missing = i;
            }
        }
        return {repeated, missing};
    }
};
