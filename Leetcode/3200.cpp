class Solution {
public:
    int maxHeightOfTriangle(int red, int blue) {
        if (red < blue) {
            swap(red, blue);
        }
        int first = 0, second = 0, n = 1;
        while (second + n <= red && first <= blue) {
            second += n;
            swap(second, first);
            n++;
        }
        return n-1;
    }
};
