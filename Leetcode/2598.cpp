class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        vector<int> freq(value, 0);
        for (int num : nums) {
            freq[(num % value + value) % value]++;
        }
        int minFreq = nums.size()+1;
        int ans = -1;
        for (int i = 0; i < value; i++) {
            if (freq[i] < minFreq) {
                minFreq = freq[i];
                ans = i;
            }
        }
        return ans + minFreq*value;
    }
};
