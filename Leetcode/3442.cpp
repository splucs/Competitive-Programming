class Solution {
public:
    int maxDifference(string s) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        int maxOdd = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] & 1) {
                maxOdd = max(maxOdd, freq[i]);
            }
        }
        int minEven = s.size();
        for (int i = 0; i < 26; i++) {
            if ((freq[i] & 1) == 0 && freq[i] > 0) {
                minEven = min(minEven, freq[i]);
            }
        }
        return maxOdd - minEven;
    }
};
