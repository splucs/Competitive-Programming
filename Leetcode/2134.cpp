class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> countZeroes(n+1);
        int numOnes = 0;

        countZeroes[0] = 0;
        for (int i = 0; i < n; i++) {
            countZeroes[i+1] = countZeroes[i];
            if (nums[i] == 1) {
                numOnes++;
            } else {
                countZeroes[i+1]++;
            }
        }
        int ans = n;
        for (int i = 1; i <= n; i++) {
            int sum = 0;
            if (i + numOnes - 1 > n) {
                sum = countZeroes[n] - countZeroes[i-1] + countZeroes[i+numOnes-1-n];
            } else {
                sum = countZeroes[i+numOnes-1] - countZeroes[i-1];
            }
            ans = min(ans, sum);
        }
        return ans;
    }
};
