class Solution {
public:
    int firstUniqChar(string s) {
        int n = s.size();

        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c-'a']++;
        }

        for (int i = 0; i < n; i++) {
            if (freq[s[i]-'a'] <= 1) {
                return i;
            }
        }
        return -1;
    }
};
