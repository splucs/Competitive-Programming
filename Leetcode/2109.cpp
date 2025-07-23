class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        vector<char> ans;
        ans.reserve(s.size() + spaces.size());
        int i = 0;
        for (int spaceIdx : spaces) {
            while (i < spaceIdx) {
                ans.push_back(s[i++]);
            }
            ans.push_back(' ');
        }
        while (i < (int)s.size()) {
            ans.push_back(s[i++]);
        }
        return string(ans.begin(), ans.end());
    }
};
