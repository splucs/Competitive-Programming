class Solution {
private:
    vector<int> elems;
    vector<char> ops;
    void parse(string &expression) {
        int cur = 0;
        for (char c : expression) {
            if ('0' <= c && c <= '9') {
                cur = 10*cur + c -'0';
            } else {
                elems.push_back(cur);
                ops.push_back(c);
                cur = 0;
            }
        }
        elems.push_back(cur);
    }
    int apply(int x, int y, char op) {
        switch(op) {
        case '+':
            return x+y;
        case '-':
            return x-y;
        case '*':
            return x*y;
        }
        return 0;
    }
public:
    vector<int> diffWaysToCompute(string expression) {
        parse(expression);
        int n = elems.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));

        for (int len = 0; len < n; len++) {
            for (int i = 0; i < n-len; i++) {
                if (len == 0) {
                    dp[i][i].push_back(elems[i]);
                    continue;
                }

                int j = len+i;
                for (int k = i; k < j; k++) {
                    for (int x : dp[i][k]) for (int y : dp[k+1][j]) {
                        dp[i][j].push_back(apply(x, y, ops[k]));
                    }
                }
            }
        }
        return dp[0][n-1];
    }
};
