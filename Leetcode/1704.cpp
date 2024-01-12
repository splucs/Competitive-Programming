class Solution {
    bool inline isVowel(char c) {
        switch (c) {
        case 'a':
            return true;
        case 'e':
            return true;
        case 'i':
            return true;
        case 'o':
            return true;
        case 'u':
            return true;
        case 'A':
            return true;
        case 'E':
            return true;
        case 'I':
            return true;
        case 'O':
            return true;
        case 'U':
            return true;
        }
        return false;
    }
public:
    bool halvesAreAlike(string s) {
        int cnt = 0;
        int n = s.size();
        int halfN = n>>1;
        for (int i = 0; i < halfN; i++) {
            if (isVowel(s[i])) {
                cnt++;
            }
        }
        for (int i = halfN; i < n; i++) {
            if (isVowel(s[i])) {
                cnt--;
            }
        }
        return cnt == 0;
    }
};
