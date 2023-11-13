class Solution {
private:
    inline bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
            || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
public:
    string sortVowels(string s) {
        int n = s.size();
        vector<int> lowerCase(26, 0);
        vector<int> upperCase(26, 0);
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (!isVowel(c)) continue;
            if ('a' <= c && c <= 'z') {
                lowerCase[c-'a']++;
            }
            if ('A' <= c && c <= 'Z') {
                upperCase[c-'A']++;
            }
        }

        vector<char> vowels;
        for (int i = 0; i < 26; i++) {
            while (upperCase[i] --> 0) {
                vowels.push_back(i+'A');
            }
        }
        for (int i = 0; i < 26; i++) {
            while (lowerCase[i] --> 0) {
                vowels.push_back(i+'a');
            }
        }
        
        for (int i = 0, j = 0; i < n; i++) {
            char c = s[i];
            if (!isVowel(c)) continue;
            if ('a' <= c && c <= 'z') {
                s[i] = vowels[j++];
            }
            if ('A' <= c && c <= 'Z') {
                s[i] = vowels[j++];
            }
        }
        return s;
    }
};
