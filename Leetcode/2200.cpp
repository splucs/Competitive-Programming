class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        vector<int> ans;
        int n = nums.size();
        int lastIdx = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] != key) {
                continue;
            }
            for (int j = max(lastIdx+1, i-k); j <= i+k && j < n; j++) {
                ans.push_back(j);
            }
            lastIdx = i+k;
        }
        return ans;
    }
};
