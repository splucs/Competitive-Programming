class Solution {
private:
    bool isSubFolder(const string& s, const string& pref) {
        if (s.size() <= pref.size()) {
            return false;
        }
        for (int i = 0; i < (int)pref.size(); i++) {
            if (s[i] != pref[i]) {
                return false;
            }
        }
        return s[pref.size()] == '/';
    }
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        sort(folder.begin(), folder.end());
        vector<string> ans;
        for (int i = 0; i < (int)folder.size(); i++) {
            if (ans.empty() || !isSubFolder(folder[i], ans.back())) {
                ans.push_back(folder[i]);
            }
        }
        return ans;
    }
};
