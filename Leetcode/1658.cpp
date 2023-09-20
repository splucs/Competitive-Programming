class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        int i = 0, j = n;
        while (i < n && x > 0) {
            x -= nums[i++];
        }
        if (x > 0) return -1;

        int ans = n+1, cost;
        if (x == 0) ans = i;
        while (i > 0) {
            x += nums[--i];
            while (j > i && x > 0) {
                x -= nums[--j];
            }
            cost = n-j+i;
            if (x == 0) ans = ans > cost ? cost : ans;
        }

        if (ans > n) return -1;
        return ans;
    }
};
