class Solution {
public:
    vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {
        map<pair<string, string>, vector<int>> dp;
        vector<int> maxSeq(words.size(), 1);
        vector<int> prev(words.size(), -1);
        int ansMaxSeq = 1;
        int ansIdx = 0;
        for (int i = 0; i < (int)words.size(); i++) {
            const string& word = words[i];
            for (int j = 0; j < (int)word.size(); j++) {
                string pref = word.substr(0, j);
                string suff = word.substr(j+1, word.size());
                vector<int> &idx = dp[make_pair(pref, suff)];
                for (int k : idx) {
                    if (word[j] == words[k][j] || groups[i] == groups[k]) {
                        continue;
                    }
                    if (maxSeq[i] < 1 + maxSeq[k]) {
                        maxSeq[i] = 1 + maxSeq[k];
                        prev[i] = k;
                    }
                }
                idx.push_back(i);
            }
            if (ansMaxSeq < maxSeq[i]) {
                ansMaxSeq = maxSeq[i];
                ansIdx = i;
            }
        }
        vector<string> ans;
        for(int i = ansIdx; i != -1; i = prev[i]) {
            ans.push_back(words[i]);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
