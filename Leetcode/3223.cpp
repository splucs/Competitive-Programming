class Solution {
public:
    int minimumLength(string s) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c-'a']++;
        }
        int ans = 0;
        for (int f : freq) {
            if (f > 0) {
                ans += (1 + ((f-1)&1));
            }
        }
        return ans;
    }
};
