class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                continue;
            }
            for (int j = i+1, k = i+2; j < n; j++) {
                while(k < n && (k <= j || nums[i] + nums[j] > nums[k])) {
                    k++;
                }
                ans += k-j-1;
            }
        }
        return ans;
    }
};
