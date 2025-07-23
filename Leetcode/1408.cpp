class KMP {
	string P;
	vector<int> b;
public:
	KMP(string _P) : P(_P) {
		int m = P.size();
		b.assign(m + 1, -1);
		for (int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			b[++i] = ++j;
		}
	}
	bool match(string T) {
		for (int i = 0, j = 0, n = T.size(); i < n;) {
			while (j >= 0 && T[i] != P[j]) j = b[j];
			i++; j++;
			if (j == (int)P.size()) {
                return true;
				j = b[j];
			}
		}
		return false;
	}
};

class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        int n = words.size();
        vector<KMP> kmp;
        kmp.reserve(n);
        for (int i = 0; i < n; i++) {
            kmp.push_back(KMP(words[i]));
        }
        vector<string> ans;
        for (int i = 0; i < n; i++) {
            bool found = false;
            for (int j = 0; j < n && !found; j++) {
                if (i != j && kmp[i].match(words[j])) {
                    found = true;
                }
            }
            if (found) {
                ans.push_back(words[i]);
            }
        }
        return ans;
    }
};
