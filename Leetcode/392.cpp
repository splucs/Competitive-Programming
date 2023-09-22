class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, n = t.size();
        for (char c : s) {
            while (i < n && t[i] != c) i++;
            if (i == n) return false;
            i++;
        }
        return true;
    }
};
