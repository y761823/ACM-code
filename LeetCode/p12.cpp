class Solution {
public:
    string str1[10] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    string str2[10] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string str3[10] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string str4[4] = {"", "M", "MM", "MMM"};

    string intToRoman(int num) {
        return str4[num / 1000] + str3[num / 100 % 10] + str2[num / 10 % 10] + str1[num % 10];
    }
};
