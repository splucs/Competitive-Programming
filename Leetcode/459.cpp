class KMP {
    string P;
    vector<int> b;
public:
    KMP(string _P) : P(_P) {
        int m = P.size();
        b.assign(m + 1, -1);
        for(int i = 0, j = -1; i < m;) {
            while (j >= 0 && P[i] != P[j]) j = b[j];
            b[++i] = ++j;
        }
    }
    int match(string T) {
        int ans = 0;
        for (int i = 0, j = 0, n = T.size(); i < n;) {
            while (j >= 0 && T[i] != P[j]) j = b[j];
            i++; j++;
            if (j == (int)P.size()) {
                ans++;
                j = b[j];
            }
        }
        return ans;
    }
};

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        KMP kmp(s);
        return kmp.match(s+s) > 2;
    }
};
