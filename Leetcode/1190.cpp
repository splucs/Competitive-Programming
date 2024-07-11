class Solution {
private:
    string s;
    string ans;
    vector<int> parPair;

    void calculateParPair() {
        vector<int> openIdx;
        parPair.assign(s.size(), -1);
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') {
                openIdx.push_back(i);
            }
            if (s[i] == ')') {
                parPair[i] = openIdx.back();
                parPair[openIdx.back()] = i;
                openIdx.pop_back();
            }
        }
    }

    void go(int begin, int end, int dir) {
        for (int i = begin; i != end; i += dir) {
            if (s[i] == '(' || s[i] == ')') {
                go(parPair[i]-dir, i, -dir);
                i = parPair[i];
            } else {
                ans.push_back(s[i]);
            }
        }
    }
public:
    string reverseParentheses(string _s) {
        s.swap(_s);
        ans.clear();
        calculateParPair();
        go(0, s.size(), 1);
        return ans;
    }
};
