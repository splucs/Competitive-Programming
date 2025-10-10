class Solution {
private:
    inline int isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
public:
    int maxFreqSum(string s) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c-'a']++;
        }
        int maxVowel = 0, maxCon = 0;
        for (int i = 0; i < 26; i++) {
            if (isVowel(i+'a')) {
                maxVowel = max(maxVowel, freq[i]);
            } else {
                maxCon = max(maxCon, freq[i]);
            }
        }
        return maxVowel + maxCon;
    }
};
