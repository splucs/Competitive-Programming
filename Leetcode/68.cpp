class Solution {
private:
    string buildLine(vector<string>& words, int maxWidth) {
        int numSpaces = maxWidth;
        for (string word : words) numSpaces -= word.size();

        string ans;
        int numDiv = words.size()-1;
        if (numDiv == 0) {
            ans = words[0];
            for (int i = 0; i < numSpaces; i++) ans.push_back(' ');
            return ans;
        }

        int divQuo = numSpaces/numDiv;
        int divRem = numSpaces%numDiv;
        for (int i = 0; i < numDiv; i++) {
            ans = ans + words[i];
            for (int j = 0; j < divQuo; j++) ans.push_back(' ');
            if (i < divRem) ans.push_back(' ');
        }
        ans = ans + words[numDiv];
        return ans;
    }
    string buildLastLine(vector<string>& words, int maxWidth) {
        int numSpaces = maxWidth;
        string ans;
        for (int i = 0; i < (int)words.size(); i++) {
            if (i > 0) {
                ans.push_back(' ');
                numSpaces--;
            }
            ans = ans + words[i];
            numSpaces -= words[i].size();
        }
        for (int i = 0; i < numSpaces; i++) ans.push_back(' ');
        return ans;
    }
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> curLine;
        vector<string> ans;
        int curLineLen = 0;
        for (string word : words) {
            int toAdd = word.size();
            if (curLineLen > 0) toAdd++;

            if (curLineLen + toAdd <= maxWidth) {
                curLine.push_back(word);
                curLineLen += toAdd;
            } else {
                ans.push_back(buildLine(curLine, maxWidth));
                curLine.clear();
                curLine.push_back(word);
                curLineLen = word.size();
            }
        }
        ans.push_back(buildLastLine(curLine, maxWidth));
        return ans;
    }
};
