class Solution {
private:
    vector<int> digitsN, digitsA, digitsB;
    bool recurse(int i, int carry) {
        if (i == (int)digitsN.size()) {
            return carry == 0;
        }
        int dn = digitsN[i];
        for (int da = 0; da <= 9; da++) {
            int db = (dn - carry - da + 100) % 10;
            if (!digitsA.empty() && digitsA.back() == 0 && da != 0) {
                continue;
            }
            if (i == 0 && da == 0) {
                continue;
            }
            if (!digitsB.empty() && digitsB.back() == 0 && db != 0) {
                continue;
            }
            if (i == 0 && db == 0) {
                continue;
            }
            digitsA.push_back(da);
            digitsB.push_back(db);
            int ncarry = (da + db + carry) / 10;
            if (recurse(i+1, ncarry)) {
                return true;
            }
            digitsA.pop_back();
            digitsB.pop_back();
        }
        return false;
    }
public:
    vector<int> getNoZeroIntegers(int n) {
        for (; n > 0; n /= 10) {
            digitsN.push_back(n%10);
        }
        recurse(0, 0);
        int a = 0, b = 0;
        for (int i = digitsA.size()-1; i >= 0; i--) {
            a = 10*a + digitsA[i];
        }
        for (int i = digitsB.size()-1; i >= 0; i--) {
            b = 10*b + digitsB[i];
        }
        return {a, b};
    }
};
