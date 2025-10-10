class Solution {
private:
    inline int abs(int x) {
        return x < 0 ? -x : x;
    }
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int n = points.size();
        double ans = 0.0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < j; k++) {
                    int dx1 = points[j][0] - points[i][0], dy1 = points[j][1] - points[i][1];
                    int dx2 = points[k][0] - points[i][0], dy2 = points[k][1] - points[i][1];
                    ans = max(ans, abs(dx1*dy2 - dx2*dy1) / 2.0);
                }
            }
        }
        return ans;
    }
};
