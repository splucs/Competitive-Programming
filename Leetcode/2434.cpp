class Solution {
public:
    string robotWithString(string s) {
        s.push_back('|');
        int n = s.size();
        vector<char> nxt(n);
        char cur = s.back();
        for (int i = n-1; i >= 0; i--) {
            cur = min(cur, s[i]);
            nxt[i] = cur;
        }
        string t = "", ans = "";
        for (int i = 0; i < n; i++) {
            while (!t.empty() && t.back() <= nxt[i]) {
                ans.push_back(t.back());
                t.pop_back();
            }
            t.push_back(s[i]);
        }
        return ans;
    }
};
