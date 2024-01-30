class Solution {
private:
    vector<int> vals;
    void applyOp(char op) {
        int second = vals.back();
        vals.pop_back();
        int first = vals.back();
        vals.pop_back();

        int res;
        switch(op) {
        case '+':
            res = first + second;
            break;
        case '-':
            res = first - second;
            break;
        case '*':
            res = first * second;
            break;
        case '/':
            res = first / second;
            break;
        }
        vals.push_back(res);
    }
    int atoi(const string &num) {
        int res = 0;
        for (char c : num) {
            res = c - '0' + (res*10);
        }
        return res;
    }
public:
    int evalRPN(vector<string>& tokens) {
        vals.clear();
        for (const string& token : tokens) {
            if (token[0] >= '0' && token[0] <= '9') {
                vals.push_back(atoi(token));
            } else if (token.size() > 1 && token[0] == '-') {
                vals.push_back(-atoi(token.substr(1)));
            } else {
                applyOp(token[0]);
            }
        }
        return vals.back();
    }
};
