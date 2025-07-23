class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        // last[i][j] = max sequence seen so far where the last element
        // has parity i and parity between adjacent elements is j
        int last[2][2] = {{0, 0}, {0, 0}};
        for (int i = 0; i < n; i++) {
            int p = nums[i] & 1;
            for (int b = 0; b < 2; b++) {
                last[p][b] = 1 + last[p^b][b];
                ans = max(ans, last[p][b]);
            }
        }
        return ans;
    }
};
