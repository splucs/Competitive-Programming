class Solution {
public:
    bool isValid(string word) {
        if (word.size() < 3) {
            return false;
        }
        int numbers = 0, vowels = 0, consonants = 0;
        for (char c : word) {
            if ('0' <= c && c <= '9') {
                numbers++;
            }
            else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowels++;
            }
            else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                vowels++;
            }
            else if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
                consonants++;
            }
            else {
                return false;
            }
        }
        if (vowels == 0 || consonants == 0) {
            return false;
        }
        return true;
    }
};
