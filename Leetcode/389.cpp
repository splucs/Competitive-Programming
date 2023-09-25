class Solution {
public:
    char findTheDifference(string s, string t) {
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c-'a']++;
        for (char c : t) cnt[c-'a']--;
        char ans;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] < 0) {
                ans = i+'a';
            }
        }
        return ans;
    }
};
