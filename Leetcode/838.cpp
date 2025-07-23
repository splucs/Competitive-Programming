class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        vector<int> qIdx, instant(n, -1);
        qIdx.reserve(n);
        for (int i = 0; i < n; i++) {
            if (dominoes[i] == '.') {
                continue;
            }
            qIdx.push_back(i);
            instant[i] = 0;
        }

        for (int t = 0; t < (int)qIdx.size(); t++) {
            int i = qIdx[t];
            int dir = dominoes[i];
            if (dir == '.') {
                continue;
            }

            int j = dir == 'R' ? i + 1 : i - 1;
            if (j < 0 || j == n) {
                continue;
            }

            if (instant[j] == -1) {
                qIdx.push_back(j);
                instant[j] = instant[i] + 1;
                dominoes[j] = dir;
            }
            if (instant[j] == instant[i] + 1 && dominoes[j] != dir) {
                dominoes[j] = '.';
            }
        }
        return dominoes;
    }
};
