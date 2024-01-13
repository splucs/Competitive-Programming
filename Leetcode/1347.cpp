class Solution {
public:
    int minSteps(string s, string t) {
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c-'a']++;
        }
        for (char c : t) {
            cnt[c-'a']-- ;
        }
        int ans = 0;
        for (int x : cnt) {
            ans += x > 0 ? x : 0;
        }
        return ans;
    }
};
