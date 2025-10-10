class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        // Sort by increasing x, solve ties by decreasing y.
        sort(points.begin(), points.end(), [&](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            }
            return a[1] > b[1];
        });

        int n = points.size();
        int ans = 0;
        vector<int> st;
        for (int i = 0; i < n; i++) {
            int y0 = points[i][1];
            st.clear();
            for (int j = 0; j < i; j++) {
                int y = points[j][1];
                if (y < y0) {
                    continue;
                }
                while (!st.empty() && y <= st.back()) {
                    st.pop_back();
                }
                st.push_back(y);
            }
            ans += st.size();
        }
        return ans;
    }
};
