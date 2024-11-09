#define INF 0x3f3f3f3f

class Solution {
private:
    unordered_map<int, vector<int>> xobs, yobs;
    void preprocessObstacles(vector<vector<int>>& obstacles) {
        xobs.clear();
        yobs.clear();
        for (vector<int>& obstacle : obstacles) {
            int ox = obstacle[0], oy = obstacle[1];
            xobs[ox].push_back(oy);
            yobs[oy].push_back(ox);
        }
        for (pair<const int, vector<int>> &entry : xobs) {
            sort(entry.second.begin(), entry.second.end());
        }
        for (pair<const int, vector<int>> &entry : yobs) {
            sort(entry.second.begin(), entry.second.end());
        }
    }
    int upper_bound(vector<int>& o, int x) {
        int lo = -1;
        int hi = o.size();
        while(hi > lo + 1) {
            int mid = (hi+lo)>>1;
            if (o[mid] > x) hi = mid;
            else lo = mid;
        }
        return hi;
    }
    int findNextObstacle(vector<int> &o, int x, int dx) {
        int i = upper_bound(o, x);
        if (dx > 0 && i < o.size()) {
            return o[i]-x-1;
        }
        i--;
        if (i >= 0 && o[i] >= x) i--;
        if (dx < 0 && i >= 0) {
            return x-o[i]-1;
        }
        return INF;
    }
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        preprocessObstacles(obstacles);

        int ans = 0;
        int dx = 0, dy = 1;
        int x = 0, y = 0;
        for (int cmd : commands) {
            if (cmd == -2) {
                swap(dx, dy);
                dx = -dx;
            } else if (cmd == -1) {
                swap(dx, dy);
                dy = -dy;
            } else {
                if (dx == 0) {
                    cmd = min(cmd, findNextObstacle(xobs[x], y, dy));
                } else {
                    cmd = min(cmd, findNextObstacle(yobs[y], x, dx));
                }
                x += cmd*dx;
                y += cmd*dy;
            }
            ans = max(ans, x*x + y*y);
        }
        return ans;
    }
};
