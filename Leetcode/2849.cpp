class Solution {
private:
    inline int abs(int x) {
        return x > 0 ? x : -x;
    }
public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        int dx = abs(fx-sx);
        int dy = abs(fy-sy);

        int mint = dx + dy - min(dx, dy);
        // Can't reach it if t is not enough to make the minimum time.
        if (t < mint) {
            return false;
        }
        // Can reach in minimum time.
        if (mint == t) {
            return true;
        }
        // If there's 2 or more cycles to spare, walk in circles of 2 or 3 at finish until time is up.
        if (mint+1 < t) {
            return true;
        }
        // If mint+1 == t (only case remaining), we can extend the path by one with a detour if there is a path.
        return mint > 0;
    }
};
