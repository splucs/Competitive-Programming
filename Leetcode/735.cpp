class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
        for (int cur : asteroids) {
            if (cur > 0) {
                ans.push_back(cur);
                continue;
            }

            while (!ans.empty() && ans.back() > 0 && ans.back() < -cur) {
                ans.pop_back();
            }

            if (ans.empty()) {
                ans.push_back(cur);
            } else if (ans.back() < 0) {
                ans.push_back(cur);
            } else if (ans.back() == -cur) {
                ans.pop_back();
            }
        }
        return ans;
    }
};
