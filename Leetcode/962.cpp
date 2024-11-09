class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        vector<int> st;
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (st.empty() || nums[st.back()] > nums[i]) {
                st.push_back(i);
            }
            int lo = -1;
            int hi = st.size();
            while(hi > lo + 1) {
                int mid = (hi+lo)>>1;
                if (nums[st[mid]] <= nums[i]) {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            ans = max(ans, i-st[hi]);
        }
        return ans;
    }
};
