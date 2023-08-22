class Solution {
public:
    string convertToTitle(int columnNumber) {
        long long power = 26;
        int alg = 1;
        while (power < columnNumber) {
            columnNumber -= power;
            power *= 26;
            alg++;
        }

        columnNumber--;
        string ans;
        ans.resize(alg);
        for (int i = alg-1; i >= 0; i--) {
            ans[i] = columnNumber%26 + 'A';
            columnNumber /= 26;
        }
        return ans;
    }
};
