class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int i = 0, sum = 0;
        int ans = n+1;
        for (int j = 0; j < n; j++) {
            sum += nums[j];
            while(target <= sum - nums[i]) {
                sum -= nums[i++];
            }
            if (sum >= target && j-i < ans) ans = j-i; 
        }
        if (ans > n) return 0;
        return ans+1;
    }
};
