class Solution {
private:
    vector<int> tsa, head, c, tc;

    void bucket(vector<int>& sa, int n, int L) {
        int maxi = max(30, n);
        head.assign(maxi, 0);
	    for (int i = 0; i < n; i++) head[c[i]]++;
	    int k = 0;
    	for (int i = 0; i < maxi; i++)
    		swap(k, head[i]), k += head[i];
    	for (int i = 0; i < n; i++) {
    		int j = (sa[i] - L + n) % n;
    		tsa[head[c[j]]++] = j;
    	}
        sa.swap(tsa);
    }

    vector<int> suffixArray(string& str) {
    	int n = str.size() + 1;
        c.resize(n);
        tc.resize(n);
        tsa.resize(n);
        vector<int> sa(n);

    	for (int i = 0; i < n; i++)
    		sa[i] = i, c[i] = i == n-1 ? 0 : str[i]-'a'+1;
    	bucket(sa, n, 0);
    	for (int L = 1; L < n; L <<= 1) {
    		bucket(sa, n, L);
    		for (int i = 0, cc = -1; i < n; i++)
    			tc[sa[i]] = (i == 0 || c[sa[i]] != c[sa[i - 1]] || c[(sa[i] + L) % n] != c[(sa[i - 1] + L) % n]) ? ++cc : cc;
            c.swap(tc);
	    }
	    for (int i = 0; i < n - 1; i++) sa[i] = sa[i + 1];
        sa.pop_back();
        return sa;
    }

public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1) {
            return word;
        }
        return word.substr(suffixArray(word).back(), word.size() - numFriends + 1);
    }
};
