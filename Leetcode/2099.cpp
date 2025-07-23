class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [=](int i, int j) {
            return nums[i] > nums[j];
        });
        sort(idx.begin(), idx.begin() + k);
        vector<int> ans(k);
        for (int i = 0; i < k; i++) {
            ans[i] = nums[idx[i]];
        }
        return ans;
    }
};
