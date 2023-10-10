class Solution {
public:
    int minOperations(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        vector<int> unique;
        for (int i = 0; i < n; i++) {
            if (i == 0 || nums[i] != nums[i-1]) {
                unique.push_back(nums[i]);
            }
        }

        int m = unique.size();
        int ans = n;
        for (int i = 0, j = 0; i < m; i++) {
            while (j < m && unique[j]-unique[i] < n) j++;
            ans = min(ans, n-j+i);
        }
        return ans;
    }
};
