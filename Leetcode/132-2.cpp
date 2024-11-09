#define INF 0x3f3f3f3f
#define ALFA 26

class PalindromicTree {
private:
	int root1, root2;
    vector<vector<int>> nxt;
    vector<int> len, link, dp;
    int cnt = 0;

	string s;
	int suff;
	char reduce(char c) { return c-'a'; }
	int getlink(int u, int pos) {
		for(; true; u = link[u]) {
			int st = pos - 1 - len[u];
			if (st >= 0 && s[st] == s[pos])
				return u;
		}
	}
public:
	PalindromicTree(int n) {
        nxt.assign(n+3, vector<int>(ALFA, -1));
        len.resize(n+3);
        link.resize(n+3);
        dp.assign(n, n);

		root1 = ++cnt; root2 = ++cnt;
		suff = root2;
		len[root1] = -1; link[root1] = root1;
		len[root2] = 0; link[root2] = root1;
	}
	int extend(char c) {
		int pos = s.size(); s.push_back(c);
		c = reduce(c);
		int u = getlink(suff, pos);
		if (nxt[u][c] != -1) {
			suff = nxt[u][c];
			return suff;
		}
		int v = suff = ++cnt;
		len[v] = len[u] + 2;
		nxt[u][c] = v;
		if (len[v] == 1) {
			link[v] = root2;
			return suff;
		}
		u = getlink(link[u], pos);
		link[v] = nxt[u][c];           
		return suff;
	}
    int compute(char c) {
        int j = s.size();
        int u = extend(c);
        for(; u != link[u]; u = link[u]) {
            if (len[u] > 0) {
                int i = j - len[u];
                dp[j] = min(dp[j], 1 + (i == -1 ? -1 : dp[i]));
            }
        }
        return dp[j];
    }
};

class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        PalindromicTree pt(n);
        int ans;
        for (int j = 0; j < n; j++) {
            ans = pt.compute(s[j]);
        }
        return ans;
    }
};
