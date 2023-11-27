#define MOD 1000000007

typedef vector<int> column;
typedef vector<vector<int>> matrix;

matrix multiply(matrix &a, matrix &b) {
    int n = a.size();
    matrix c(n, column(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] = (c[i][j] + a[i][k]*1ll*b[k][j]) % MOD;
            }
        }
    }
    return c;
}

matrix power(matrix a, int k) {
    int n = a.size();
    matrix ans(n, column(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;
    }

    for (; k; k >>= 1) {
        if (k&1) {
            ans = multiply(ans, a);
        }
        a = multiply(a, a);
    }
    return ans;
}

class Solution {
    vector<vector<int>> g = {
        {4, 6}, // 0
        {6, 8}, // 1
        {7, 9}, // 2
        {4, 8}, // 3
        {3, 9, 0}, // 4
        {}, // 5
        {1, 7, 0}, // 6
        {2, 6}, // 7
        {1, 3}, // 8
        {2, 4} // 9
    };
    matrix getRecursion() {
        int n = 10;
        matrix r(n, column(n, 0));
        for (int u = 0; u < n; u++) {
            for (int v : g[u]) {
                r[u][v] = 1;
            }
        }
        return r;
    }
public:
    int knightDialer(int n) {
        matrix r = power(getRecursion(), n-1);
        int ans = 0;
        for (int u = 0; u < 10; u++) {
            for (int v = 0; v < 10; v++) {
                ans = (ans + r[u][v]) % MOD;
            }
        }
        return ans;
    }
};
