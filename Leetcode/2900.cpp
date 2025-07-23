class Solution {
public:
    vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {
        int lastBit = 1-groups[0];
        vector<string> ans;
        for (int i = 0; i < (int)words.size(); i++) {
            if (groups[i] == lastBit) {
                continue;
            }
            lastBit = groups[i];
            ans.push_back(words[i]);
        }
        return ans;
    }
};
