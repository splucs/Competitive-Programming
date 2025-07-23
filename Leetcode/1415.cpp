class Solution {
private:
    string ans;
    int n, k;
    void recurse(int i) {
        if (i == n) {
            k--;
            return;
        }

        for (char c = 'a'; c <= 'c' && k > 0; c++) {
            if (i > 0 && ans[i-1] == c) {
                continue;
            }
            ans[i] = c;
            recurse(i+1);
        }
    }
public:
    string getHappyString(int _n, int _k) {
        n = _n;
        k = _k;
        ans.resize(n);
        recurse(0);
        if (k > 0) {
            return "";
        }
        return ans;
    }
};
