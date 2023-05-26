class SegmentTree {
	vector<int> a;
	int n, neutral;
public:
	SegmentTree(int sz) {
        neutral = -1e7;
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, neutral);
	}
	void update(int i, int x) {
		a[i += n] = x;
		for (i >>= 1; i; i >>= 1)
			a[i] = max(a[i<<1], a[1+(i<<1)]);
	}
	int query(int l, int r) {
		int ans = neutral;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, a[l++]);
			if (r & 1) ans = max(ans, a[--r]);
		}
		return ans;
	}
};

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // P[i] = piles[0] + piles[1] + ... + piles[i] = partial sum array
        vector<int> P(n);
        for (int i = 0; i < n; i++) {
            P[i] = piles[i] + (i > 0 ? P[i-1] : 0);
        }

        // dp[i][m] = maximum balance given it's our turn, we're at pile i and M = m
        // Let Q[i][m] = P[i-1] - dp[i][m]
        vector<vector<int> > dp(n+1, vector<int>(n+1, 0));

        // cols is the columns of Q
        // cols[m][i] = Q[i][m]
        vector<SegmentTree> cols(n+1, SegmentTree(n+1));
        // diag is the diagonals of Q
        // diag[i-m+n][m] = Q[i][m];
        vector<SegmentTree> diag(2*n, SegmentTree(n+1));

        for (int i = n; i >= 0; i--) {
            for (int m = 1; m <= n; m++) {
                dp[i][m] = 0;
                // base case
                if (i == n) continue;

                if (i > 0) dp[i][m] -= P[i-1];
                int colQuery = cols[m].query(i+1, min(i+m, n));
                int diagQuery = diag[i+n].query(m, min(2*m, n-i));
                dp[i][m] += max(colQuery, diagQuery);
            }

            for (int m = 1; m <= n; m++) {
                // Calculate Q[i][m] and update in the segment trees
                int q = -dp[i][m];
                if (i > 0) q += P[i-1];
                
                cols[m].update(i, q);
                diag[i-m+n].update(m, q);
            }
        }

        return (dp[0][1] + P[n-1])/2;
    }
};

