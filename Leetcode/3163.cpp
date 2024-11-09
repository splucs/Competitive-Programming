class Solution {
public:
    string compressedString(string word) {
        vector<char> comp;
        for (int i = 0, j; i < (int)word.size();) {
            for (j = i+1; j < i+9 && j < (int)word.size() && word[i] == word[j]; j++);
            comp.push_back(j-i + '0');
            comp.push_back(word[i]);
            i = j;
        }
        return string(comp.begin(), comp.end());
    }
};
