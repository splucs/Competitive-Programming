class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
        while (j1 < (int)word1.size() && j2 < (int)word2.size()) {
            if (word1[j1][i1] != word2[j2][i2]) {
                return false;
            }
            i1++;
            if (i1 == word1[j1].size()) {
                j1++;
                i1 = 0;
            }
            i2++;
            if (i2 == word2[j2].size()) {
                j2++;
                i2 = 0;
            }
        }
        return j1 == word1.size() && j2 == word2.size();
    }
};
