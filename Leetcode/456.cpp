#define INF (1e9 + 1)

struct interval {
    int lo, hi;
    interval(int _lo, int _hi) : lo(_lo), hi(_hi) {}
    interval() : lo(INF), hi(INF) {}
};

class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        vector<interval> intervalStack;
        int n = nums.size();
            
        int curLo = INF, curHi = INF;
        for (int i = 0; i < n; i++) {
            int x = nums[i];

            if (x <= curLo) {
                intervalStack.push_back(interval(curLo, curHi));
                curLo = curHi = x;
                continue;
            }

            if (x < curHi) {
                return true;
            }
            while (!intervalStack.empty()) {
                interval cur = intervalStack.back();
                if (x <= cur.lo) {
                    break;
                }
                if (x < cur.hi) {
                    return true;
                }
                intervalStack.pop_back();
            }

            curHi = x;
        }
        return false;
    }
};
