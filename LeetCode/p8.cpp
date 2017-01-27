class Solution {
public:
    int adjust(long long x, bool flag) {
        if (flag) x *= -1;
        if (x > numeric_limits<int>::max())
            return numeric_limits<int>::max();
        if (x < numeric_limits<int>::min())
            return numeric_limits<int>::min();
        return (int)x;
    }

    int myAtoi(string str) {
        if (str.empty())
            return 0;
            
        int i = 0;
        while(str[i] == ' ' && i < (int)str.length())
            i++;
        
        bool flag = false;
        if (str[i] == '-')
            flag = true, i++;
        if (!flag && str[i] == '+')
            i++;
        long long res = 0;
        while (true) {
            if (i >= (int)str.length() || !isdigit(str[i]))
                return adjust(res, flag);
            res = res * 10 + str[i++] - '0';
            if (res > numeric_limits<int>::max())
                return adjust(res, flag);
        }
    }
};
