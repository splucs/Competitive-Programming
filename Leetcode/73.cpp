class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        bool firstRowIsZero = false, firstColIsZero = false;
        for (int i = 0; i < n; i++) {
            if (matrix[i][0] == 0) {
                firstColIsZero = true;
                break;
            }
        }
        for (int j = 0; j < m; j++) {
            if (matrix[0][j] == 0) {
                firstRowIsZero = true;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (firstColIsZero) {
            for (int i = 0; i < n; i++) {
                matrix[i][0] = 0;
            }
        }
        if (firstRowIsZero) {
            for (int j = 0; j < m; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};
