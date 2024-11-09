class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        vector<bool> isAllowed(26, false);
        for (char c : allowed) {
            isAllowed[c-'a'] = true;
        }
        int ans = words.size();
        for (string& word : words) {
            for (char c : word) {
                if (!isAllowed[c-'a']) {
                    ans--;
                    break;
                }
            }
        }
        return ans;
    }
};
