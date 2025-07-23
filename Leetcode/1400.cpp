class Solution {
private:
public:
    bool canConstruct(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c-'a']++;
        }
        int numOdd = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] & 1) {
                numOdd++;
            }
        }
        return numOdd <= k && s.size() >= k;
    }
};
