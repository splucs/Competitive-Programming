class Solution {
public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1) {
            return word;
        }
        int n = word.size();
        int m = n - numFriends + 1;
        int opt = 0;
        for (int i = 1; i < n; i++) {
            int j = 0;
            for (; j < m && i+j < n && word[i+j] == word[opt+j]; j++);
            if (i+j < n && j < m && word[i+j] > word[opt+j]) {
                opt = i;
            }
        }
        return word.substr(opt, m);
    }
};
