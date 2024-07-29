class Solution {
private:
    string s;
    int removeAB(int x) {
        string st;
        int ans = 0;
        for (char c : s) {
            if (c == 'b' && !st.empty() && st.back() == 'a') {
                st.pop_back();
                ans += x;
            } else {
                st.push_back(c);
            }
        }
        s.swap(st);
        return ans;
    }
    int removeBA(int y) {
        reverse(s.begin(), s.end());
        int ans = removeAB(y);
        reverse(s.begin(), s.end());
        return ans;
    }
public:
    int maximumGain(string _s, int x, int y) {
        s.swap(_s);
        if (x > y) {
            return removeAB(x) + removeBA(y);
        }
        return removeBA(y) + removeAB(x);
    }
};
