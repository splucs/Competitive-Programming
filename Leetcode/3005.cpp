class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        vector<int> freq(101, 0);
        for (int num : nums) {
            freq[num]++;
        }
        int maxFreq = 0;
        int ans = 0;
        for (int i = 0; i < (int)freq.size(); i++) {
            if (freq[i] > maxFreq) {
                maxFreq = freq[i];
                ans = 0;
            }
            if (freq[i] == maxFreq) {
                ans += maxFreq;
            }
        }
        return ans;
    }
};
