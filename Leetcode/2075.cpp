class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        int cols = encodedText.size() / rows;
        string ans = "";
        for (int sj = 0; sj < cols; sj++) {
            for(int i = 0, j = sj; j < cols && i < rows; i++, j++) {
                ans += encodedText[i*cols + j];
            }
        }
        while (!ans.empty() && ans.back() == ' ') {
            ans.pop_back();
        }
        return ans;
    }
};
