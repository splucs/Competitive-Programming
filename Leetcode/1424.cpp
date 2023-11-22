struct coordinate {
    int i;
    int j;
    coordinate(int _i, int _j) : i(_i), j(_j) {}
};

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<coordinate> coordinates;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int m = nums[i].size();
            for (int j = 0; j < m; j++) {
                coordinates.push_back(coordinate(i, j));
            }
        }

        sort(coordinates.begin(), coordinates.end(), [=](coordinate first, coordinate second) {
            int firstSum = first.i + first.j;
            int secondSum = second.i + second.j;
            if (firstSum != secondSum) {
                return firstSum < secondSum;
            }
            return first.j < second.j;
        });

        vector<int> ans;
        ans.reserve(coordinates.size());
        for (coordinate c : coordinates) {
            ans.push_back(nums[c.i][c.j]);
        }
        return ans;
    }
};
