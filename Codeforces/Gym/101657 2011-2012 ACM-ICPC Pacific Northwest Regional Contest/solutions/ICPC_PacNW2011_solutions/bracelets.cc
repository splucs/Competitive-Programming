#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

enum DIRECTIONS { NONE, UP, LEFT, DIAG };

/** Class for performing cyclic longest common subsequence.
 *
 * Naive algorithm: For a pair of strings s and t (with t being shorter), it
 * takes O(|s||t|) time to perform dynamic programming to compute the LCS of s
 * and t.  Applying such an algorithm for all |t| possible rotations of the
 * string t gives an O(|s||t|^2) algorithm.
 *
 * Key observation: Each LCS computation involves computing a path through an
 * (|s|+1) x (2|t|+1) dynamic programming matrix, starting at (0,offset) and
 * ending at (|s|,|t|+offset).  However, for different values of offset, these
 * paths will never cross -- i.e., if offset1<offset2<offset3, then the path
 * for offset2 will lie between the paths for offset1 and offset3.
 */
struct CyclicAlignment
{
    string s, t, tt;
    VVI dp, dad, lower, upper;

    CyclicAlignment(const string &s, const string &t) :
        s(s), t(t), tt(t+t),
        dp(s.length() + 1, VI(2 * t.length() + 1)),
        dad(s.length() + 1, VI(2 * t.length() + 1)),
        lower(t.length() + 1, VI(2 * t.length() + 1, 0)),
        upper(t.length() + 1, VI(2 * t.length() + 1, int(s.length())))
    {}

    inline bool valid(int offset, int left, int right, int i, int j)
    {
        return (j >= offset) && (j <= offset + int(t.length())) &&
               (i >= lower[right][j]) && (i <= upper[left][j]);
    }

    int lcs(int offset, int left, int right) 
    {
        assert(lower[right][offset] == 0);
        assert(upper[left][offset + int(t.length())] == int(s.length()));

        for (int j = offset; j <= offset + int(t.length()); ++j) {
            for (int i = lower[right][j]; i <= upper[left][j]; ++i) {
                dp[i][j] = 0;
                dad[i][j] = NONE;
                if (valid(offset, left, right, i-1, j) && dp[i][j] <= dp[i-1][j]) {
                    dp[i][j] = dp[i-1][j];
                    dad[i][j] = UP;
                }
                if (valid(offset, left, right, i, j-1) && dp[i][j] <= dp[i][j-1]) {
                    dp[i][j] = dp[i][j-1];
                    dad[i][j] = LEFT;
                }
                if (valid(offset, left, right, i-1, j-1) && dp[i][j] <= dp[i-1][j-1] + (s[i-1] == tt[j-1])) {
                    dp[i][j] = dp[i-1][j-1] + (s[i-1] == tt[j-1]);
                    dad[i][j] = DIAG;
                }
            }
        }

        for (int j = offset; j <= offset + int(t.length()); ++j) {
            lower[offset][j] = int(s.length());
            upper[offset][j] = 0;
        }
        
        int i = int(s.length());
        int j = offset + int(t.length());
        lower[offset][j] = i;
        upper[offset][j] = i;
        while (j != offset || i != 0) {
            switch (dad[i][j]) {
                case UP: --i; break;
                case LEFT: --j; break;
                case DIAG: --i; --j; break;
                default: assert(false);
            }
            lower[offset][j] = min(lower[offset][j], i);
            upper[offset][j] = max(upper[offset][j], i);
        }
        return dp[s.length()][offset + int(t.length())];
    }

    int solve(int left, int right)
    {
        if (left + 1 < right) {
            int mid = (left + right) / 2;
            int best = lcs(mid, left, right);
            return max(best, max(solve(left, mid), solve(mid, right)));
        }
        return 0;
    }

    int solve()
    {
        int best1 = lcs(0, 0, 0);
        int best2 = lcs(t.length(), t.length(), t.length());
        assert(best1 == best2);
        return max(best1, solve(0, t.length()));
    }
};

int main(int argc, char **argv)
{
    string s, t;
    while (cin >> s >> t) {
        string u = s;
        reverse(u.begin(), u.end());
        CyclicAlignment align1(s, t);
        CyclicAlignment align2(u, t);
        cout << 2 * max(align1.solve(), align2.solve()) << endl;
    }
    return 0;
}
