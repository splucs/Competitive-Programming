class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();

        // Calculate frequency of each letter for each string
        vector<vector<int>> freq(n, vector<int>(26, 0));
        vector<int> maxFreq(26, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)strs[i].size(); j++) {
                int c = strs[i][j] - 'a';
                freq[i][c]++;
                maxFreq[c] = max(maxFreq[c], freq[i][c]);
            }
        }

        // Initialize array with indexes.
        vector<int> ansIdx(n);
        for (int i = 0; i < n; i++) {
            ansIdx[i] = i;
        }

        // Sort indexes according to frequency.
        for (int c = 25; c >= 0; c--) {
            vector<vector<int>> buckets(maxFreq[c]+1);
            for (int i : ansIdx) {
                buckets[freq[i][c]].push_back(i);
            }
            ansIdx.clear();
            for (vector<int> &bucket : buckets) {
                for (int i : bucket) {
                    ansIdx.push_back(i);
                }
            }
        }

        // Construct answer, just need to verify that freq[i] != freq[i+1].
        vector<vector<string>> ans;
        vector<string> cur;
        int prev = -1;
        for (int i : ansIdx) {
            if (prev == -1) {
                cur.push_back(strs[i]);
                prev = i;
                continue;
            }

            bool same = true;
            for (int c = 0; c < 26 && same; c++) {
                same = freq[i][c] == freq[prev][c];
            }
            if (same) {
                cur.push_back(strs[i]);
                prev = i;
                continue;
            }

            ans.push_back(cur);
            cur.clear();
            cur.push_back(strs[i]);
            prev = i;
        }
        ans.push_back(cur);

        return ans;
    }
};
