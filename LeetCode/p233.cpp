class Solution {
public:
    int countDigitOne(int n) {
        int res = 0;
        for (long i = 1; i <= n; i *= 10) {
            res += n / (i * 10) * i;
            int t = n / i % 10;
            if (t == 1)
                res += n % i + 1;
            else if (t > 1)
                res += i;
        }
        return res;
    }
};
