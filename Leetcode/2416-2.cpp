class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        int n = words.size();
        vector<int> id(n);
        for (int i = 0; i < n; i++) {
            id[i] = i;
        }
        sort(id.begin(), id.end(), [&](int a, int b) {
            return words[a] < words[b];
        });

        vector<int> upper, lower;
        int curScore = 0;
        vector<int> ans(n);
        for (int it = 0; it < n; it++) {
            int i = id[it];
            int cutOff = 0;
            while (it > 0 && cutOff < (int)words[i].size() && words[i][cutOff] == words[id[it-1]][cutOff]) {
                cutOff++;
            }
            while (cutOff < (int)upper.size()) {
                curScore -= upper.back() - lower.back();
                upper.pop_back();
                lower.pop_back();
            }
            while (upper.size() < words[i].size()) {
                int jt = it, j = upper.size();
                int prevUpper = upper.empty() ? n : upper.back();
                while (jt < prevUpper && j < (int)words[id[jt]].size() && words[i][j] == words[id[jt]][j]) {
                    jt++;
                }
                lower.push_back(it);
                upper.push_back(jt);
                curScore += jt-it;
            }
            ans[i] = curScore;
        }
        return ans;
    }
};

