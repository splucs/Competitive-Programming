class Solution {
private:
    vector<int> getRevisions(string& version) {
        int cur = 0;
        vector<int> ans;
        for (char c : version) {
            if (c == '.') {
                ans.push_back(cur);
                cur = 0;
            } else {
                cur = 10*cur + (c - '0');
            }
        }
        ans.push_back(cur);
        return ans;
    }
public:
    int compareVersion(string version1, string version2) {
        vector<int> rev1 = getRevisions(version1);
        vector<int> rev2 = getRevisions(version2);
        for (int i = 0; i < (int)rev1.size() || i < (int)rev2.size(); i++) {
            int num1 = i < (int)rev1.size() ? rev1[i] : 0;
            int num2 = i < (int)rev2.size() ? rev2[i] : 0;
            if (num1 < num2) {
                return -1;
            } else if (num1 > num2) {
                return 1;
            }
        }
        return 0;
    }
};
