class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();

        vector<int> firstIdx(26, n);
        vector<int> lastIdx(26, 0);
        for (int i = 0; i < n; i++) {
            int j = s[i]-'a';
            firstIdx[j] = min(firstIdx[j], i);
            lastIdx[j] = max(lastIdx[j], i);
        }
        
        int ans = 0;
        for (int j = 0; j < 26; j++) {
            vector<bool> seen(26, false);
            for (int i = firstIdx[j]+1; i < lastIdx[j]; i++) {
                int k = s[i]-'a';
                if (!seen[k]) {
                    seen[k] = true;
                    ans++;
                }
            }
        }
        return ans;
    }
};
