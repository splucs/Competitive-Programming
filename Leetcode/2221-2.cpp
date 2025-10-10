struct Triangle{
    vector<vector<int>> base;
    int p;
    Triangle(int _p) : p(_p) {
        base.assign(p, vector<int>(p, 0));
        for (int i = 0; i < p; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || i == j) {
                    base[i][j] = 1;
                } else {
                    base[i][j] = (base[i-1][j-1] + base[i-1][j]) % p;
                }
            }
        }
    }
    // calculates the value of generalized Sierpinsky triangle of base p in position (i, j)
    int query(int i, int j) {
        int ans = 1;
        for(; i > 0 && j > 0; i /= p, j /= p) {
            ans = (ans * base[i%p][j%p]) % p;
        }
        return ans;
    }
};
class Solution {
private:
    // results of chinese remainder theorem for primes 2 and 5
    vector<vector<int>> crt = {
        {0, 6, 2, 8, 4},
        {5, 1, 7, 3, 9}
    };
public:
    int triangularSum(vector<int>& nums) {
        Triangle t2(2), t5(5);

        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int c2 = t2.query(n-1, i);
            int c5 = t5.query(n-1, i);
            int c = crt[c2][c5];
            ans = (ans + c*nums[i]) % 10;
        }
        return ans;
    }
};
