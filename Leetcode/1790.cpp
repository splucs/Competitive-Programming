class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        vector<int> diffIdx;
        int n = s1.size();
        for (int i = 0; i < n; i++) {
            if (s1[i] != s2[i]) {
                diffIdx.push_back(i);
            }
        }
        if (diffIdx.size() == 0) {
            return true;
        }
        if (diffIdx.size() != 2) {
            return false;
        }
        int i = diffIdx[0], j = diffIdx[1];
        return s1[i] == s2[j] && s1[j] == s2[i];
    }
};
