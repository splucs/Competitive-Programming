const int ALL_FLAGS = (1<<10)-2;

class Solution {
private:
    vector<vector<int>> grid;
    int n, m;

    bool checkSum3(int i, int j, int di, int dj) {
        int sum = 0;
        for (int k = 0; k < 3; k++) {
            if (i < 0 || j < 0 || i >= n || j >= m) {
                return false;
            }
            sum += grid[i][j];
            i += di, j += dj;
        }
        return sum == 15;
    }
    bool checkSum(int i, int j) {
        return checkSum3(i, j, -1, 0)
            && checkSum3(i, j-1, -1, 0)
            && checkSum3(i, j-2, -1, 0)
            && checkSum3(i, j, 0, -1)
            && checkSum3(i-1, j, 0, -1)
            && checkSum3(i-2, j, 0, -1)
            && checkSum3(i, j, -1, -1)
            && checkSum3(i, j-2, -1, 1);
    }
    bool checkMask(int i, int j) {
        if (i < 2 || j < 2) {
            return false;
        }
        int mask = 0;
        for (int di = 0; di < 3; di++) {
            for (int dj = 0; dj < 3; dj++) {
                mask ^= (1<<grid[i-di][j-dj]);
            }
        }
        return mask == ALL_FLAGS;
    }
public:
    int numMagicSquaresInside(vector<vector<int>>& _grid) {
        grid.swap(_grid);
        n = grid.size(), m = grid[0].size();

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (checkSum(i, j) && checkMask(i, j)) {
                    ans++;
                }
            }
        }

        return ans;
    }
};
