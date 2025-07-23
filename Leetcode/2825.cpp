#define inc(c) ((c) == 'z' ? 'a' : (c) + 1)
class Solution {
public:
    bool canMakeSubsequence(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        int j = 0;
        for (int i = 0; i < n && j < m; i++) {
            if (str1[i] == str2[j] || inc(str1[i]) == str2[j]) {
                j++;
            }
        }
        return j == m;
    }
};
