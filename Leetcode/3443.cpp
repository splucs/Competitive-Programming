class Solution {
private:
    int inline abs(int x) {
        return x < 0 ? -x : x;
    }
public:
    int maxDistance(string str, int k) {
        int n = 0, s = 0, e = 0, w = 0;
        int ans = 0;
        for (char c : str) {
            switch(c) {
            case 'N':
                n++;
                break;
            case 'S':
                s++;
                break;
            case 'E':
                e++;
                break;
            case 'W':
                w++;
                break;
            }

            ans = max(ans, abs(n-s) + abs(e-w) + 2*min(k, min(n, s) + min(e, w)));
        }
        return ans;
    }
};
