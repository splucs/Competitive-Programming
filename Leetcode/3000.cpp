class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int maxDiag2 = 0;
        int maxArea = 0;
        for (const vector<int>& dimension : dimensions) {
            int x = dimension[0], y = dimension[1];
            int diag2 = x*x + y*y;
            int area = x*y;
            if (diag2 > maxDiag2 || (diag2 == maxDiag2 && area > maxArea)) {
                maxDiag2 = diag2;
                maxArea = area;
            }
        }
        return maxArea;
    }
};
