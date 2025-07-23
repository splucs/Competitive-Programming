#define MAX_CHAR 26
class Solution {
private:
    int par[MAX_CHAR];
    int find(int u) {
        if (par[u] == u) {
            return u;
        }
        return par[u] = find(par[u]);
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        par[u] = par[v] = min(u, v);
    }
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        for (int u = 0; u < MAX_CHAR; u++) {
            par[u] = u;
        }
        int n = s1.size();
        for (int i = 0; i < n; i++) {
            merge(s1[i]-'a', s2[i]-'a');
        }
        for (char& c : baseStr) {
            c = find(c-'a') + 'a';
        }
        return baseStr;
    }
};
