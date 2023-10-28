const int MOD = 1e9 + 7;

typedef vector<int> column;
typedef vector<column> matrix;

matrix multiply(matrix &a, matrix &b) {
    matrix res(5, column(5, 0));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                res[i][j] = (res[i][j] + a[i][k]*1ll*b[k][j]) % MOD;
            }
        }
    }
    return res;
}

column multiply(matrix &a, column &b) {
    column res(5, 0);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            res[i] = (res[i] + a[i][j]*1ll*b[j]) % MOD;
        }
    }
    return res;
}

matrix power(matrix a, int n) {
    matrix res(5, column(5, 0));
    for (int i = 0; i < 5; i++) {
        res[i][i] = 1;
    }

    for (; n; n >>= 1) {
        if (n&1) {
            res = multiply(res, a);
        }
        a = multiply(a, a);
    }
    return res;
}

class Solution {
private:
    const matrix recursion = {
        {0, 1, 0, 0, 0}, // 'a' can only go to 'e'
        {1, 0, 1, 0, 0}, // 'e' can only go to 'a' or 'i'
        {1, 1, 0, 1, 1}, // 'i' can only go to 'a', 'e', 'o' or 'u'
        {0, 0, 1, 0, 1}, // 'o' can only go to 'i' or 'u'
        {1, 0, 0, 0, 0}, // 'u' can only go to 'a'
    };
public:
    int countVowelPermutation(int n) {
        column initCol(5, 1);

        matrix mat = power(recursion, n-1);

        column ansCol = multiply(mat, initCol);

        int ans = 0;
        for (int j = 0; j < 5; j++) {
            ans = (ans + ansCol[j]) % MOD;
        }
        return ans;
    }
};
