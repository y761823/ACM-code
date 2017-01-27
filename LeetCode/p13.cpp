class Solution {
public:
    string str[4][10] = {{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
                        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
                        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
                        {"", "M", "MM", "MMM"}};
    int counts[4] = {1, 10, 100, 1000};

    int romanToInt(string s) {
        int res = 0, pos = 0;
        for (int i = 3; i >= 0; --i) {
            for (int j = 9; j >= 0; --j) if (str[i][j].length() > 0)
                if (s.substr(pos, str[i][j].length()) == str[i][j]) {
                    res += counts[i] * j;
                    pos += str[i][j].length();
                    break;
                }
        }
        return res;
    }
};
