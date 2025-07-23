class Solution {
private:
    int toIndex(char c) {
        switch(c) {
            case 'a':
                return 0;
            case 'e':
                return 1;
            case 'i':
                return 2;
            case 'o':
                return 3;
            case 'u':
                return 4;
        }
        return -1;
    }
    void addVow(int vow[], int &vowCnt, char c) {
        int i = toIndex(c);
        if (i == -1) {
            return;
        }
        vow[i]++;
        if (vow[i] == 1) {
            vowCnt++;
        }
    }
    void addCon(int &con, char c) {
        int i = toIndex(c);
        if (i == -1) {
            con++;
        }
    }
    void removeVow(int vow[], int &vowCnt, char c) {
        int i = toIndex(c);
        if (i == -1) {
            return;
        }
        vow[i]--;
        if (vow[i] == 0) {
            vowCnt--;
        }
    }
    void removeCon(int &con, char c) {
        int i = toIndex(c);
        if (i == -1) {
            con--;
        }
    }
    bool isValid(int vow[], int vowCnt, int con, int k) {
        return vowCnt == 5 && con == k;
    }
public:
    long long countOfSubstrings(string word, int k) {
        int lVowCnt[5], lVowUniq = 0, lConCnt = 0;
        int rVowCnt[5], rVowUniq = 0, rConCnt = 0;
        memset(lVowCnt, 0, sizeof lVowCnt);
        memset(rVowCnt, 0, sizeof rVowCnt);

        int n = word.size();
        long long ans = 0;
        for (int i = 0, lCon = 0, lVow = 0, rCon = 0, rVow = 0; i < n; i++) {
            addVow(lVowCnt, lVowUniq, word[i]);
            addVow(rVowCnt, rVowUniq, word[i]);
            addCon(lConCnt, word[i]);
            addCon(rConCnt, word[i]);
            while (lConCnt > k && lCon < i) {
                removeCon(lConCnt, word[lCon++]);
            }
            while (rConCnt >= k && rCon <= i) {
                removeCon(rConCnt, word[rCon++]);
            }
            while (rVowUniq == 5 && rVow <= i) {
                removeVow(rVowCnt, rVowUniq, word[rVow++]);
            }
            int l = max(lVow, lCon);
            int r = min(rVow, rCon);
            if (r > l) {
                ans += r-l;
            }
        }
        return ans;
    }
};
