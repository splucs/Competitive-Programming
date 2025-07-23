class KMP {
	string P;
	vector<int> b;
public:
	KMP(string _P) : P(_P) {
		int m = P.size();
		b.assign(m + 1, -1);
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			b[++i] = ++j;
		}
	}
	string match(string T) {
        int n = T.size();
		vector<char> ans;
        vector<int> ansIdx;
        ansIdx.push_back(0);
		for (int i = 0; i < n;) {
            int j = ansIdx.back();
			while (j >= 0 && T[i] != P[j]) j = b[j];
            ans.push_back(T[i]);
			i++; j++;
            ansIdx.push_back(j);
			if (j == (int)P.size()) {
				ans.resize(ans.size() - P.size());
				ansIdx.resize(ansIdx.size() - P.size());
				j = b[j];
			}
		}
		return string(ans.begin(), ans.end());
	}
};

class Solution {
public:
    string removeOccurrences(string s, string part) {
        KMP kmp(part);
        return kmp.match(s);
    }
};
