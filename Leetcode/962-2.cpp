class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        vector<int> st;
        int n = nums.size();
        int ans = 0;
        for (int i = 0, j = 0; i < n; i++, j++) {
            if (st.empty() || nums[st.back()] > nums[i]) {
                st.push_back(i);
            }
            while (j > 0 && nums[st[j-1]] <= nums[i]) {
                j--;
            }
            if (nums[st[j]] <= nums[i]) {
                ans = max(ans, i-st[j]);
            }
        }
        return ans;
    }
};
