class Solution {
private:
    string number2(int num) {
        switch(num) {
            case 0:
                return "";
            case 1:
                return " One";
            case 2:
                return " Two";
            case 3:
                return " Three";
            case 4:
                return " Four";
            case 5:
                return " Five";
            case 6:
                return " Six";
            case 7:
                return " Seven";
            case 8:
                return " Eight";
            case 9:
                return " Nine";
            case 10:
                return " Ten";
            case 11:
                return " Eleven";
            case 12:
                return " Twelve";
            case 13:
                return " Thirteen";
            case 14:
                return " Fourteen";
            case 15:
                return " Fifteen";
            case 16:
                return " Sixteen";
            case 17:
                return " Seventeen";
            case 18:
                return " Eighteen";
            case 19:
                return " Nineteen";
        }

        int quo = num/10, rem = num%10;
        switch(quo) {
            case 2:
                return " Twenty" + number2(rem);
            case 3:
                return " Thirty" + number2(rem);
            case 4:
                return " Forty" + number2(rem);
            case 5:
                return " Fifty" + number2(rem);
            case 6:
                return " Sixty" + number2(rem);
            case 7:
                return " Seventy" + number2(rem);
            case 8:
                return " Eighty" + number2(rem);
            case 9:
                return " Ninety" + number2(rem);
        }
        return " Error";
    }
    string number3(int num) {
        if (num >= 100) {
            return number2(num/100) + " Hundred" + number2(num%100);
        }
        return number2(num);
    }
public:
    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        }

        string ans = "";
        vector<string> suffixes = {" Billion", " Million", " Thousand", ""};
        for (int i = 0, b = 1000000000; i < 4; i++, b /= 1000) {
            if (num >= b) {
                ans += number3(num / b) + suffixes[i];
                num %= b;
            }
        }

        return string(ans.begin()+1, ans.end());
    }
};
