class Solution {
private:
    inline int abs(int d) {
        return d < 0 ? -d : d;
    }
public:
    int findClosest(int x, int y, int z) {
        int dx = abs(x-z);
        int dy = abs(y-z);
        if (dx < dy) {
            return 1;
        } else if (dx > dy) {
            return 2;
        } else {
            return 0;
        }
    }
};
