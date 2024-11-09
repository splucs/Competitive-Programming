#define ALFA 26
#define MAXS 2509

class Solution {
private:
    int go[MAXS][ALFA], link[MAXS], h[MAXS], cnt = 0;
    vector<int> pats[MAXS], adj[MAXS];

    int suffix(int u, char c) {
        while (u && !go[u][c]) u = link[u];
        return go[u][c];
    }

    void aho() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < (int)adj[u].size(); i++) {
                int c = adj[u][i];
                int v = go[u][c];
                link[v] = u ? suffix(link[u], c) : 0;
                pats[v].insert(pats[v].end(), pats[link[v]].begin(), pats[link[v]].end());
                q.push(v);
            }
        }
    }

    void insert(string& s, int id) {
        int u = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int &v = go[u][s[i]-'a'];
            if (!v) {
                v = ++cnt;
                adj[u].push_back(s[i]-'a');
                h[v] = i + 1;
            }
            u = v;
        }
        pats[u].push_back(id);
    }

    vector<pair<int, int>> match(string& s) { //(id, end pos)
        vector<pair<int, int>> ans;
        for (int i = 0, u = 0; i < (int)s.size(); i++) {
            u = suffix(u, s[i]-'a');
            for(int j = 0; j < (int)pats[u].size(); j++) {
                int id = pats[u][j];
                ans.push_back(make_pair(id, i));
            }
        }
        return ans;
    }
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        for (string& word : dictionary) {
            insert(word, word.size()); 
        }
        aho();
        vector<pair<int, int>> matches = match(s);
        int n = s.size(), m = matches.size();
        vector<int> dp(n, 0);
        for (int i = 0, j = 0; i < n; i++) {
            dp[i] = 1 + (i > 0 ? dp[i-1] : 0);
            for (; j < m && matches[j].second == i; j++) {
                dp[i] = min(dp[i], i >= matches[j].first ? dp[i-matches[j].first] : 0);
            }
        }
        return dp[n-1];
    }
};
