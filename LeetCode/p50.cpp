class Solution {
public:
    double power(double x, unsigned int p) {
        double res = 1;
        while (p) {
            if (p & 1) res *= x;
            x *= x;
            p >>= 1;
        }
        return res;
    }

    double myPow(double x, int n) {
        return n >= 0 ? power(x, n) : power(1 / x, -n);
    }
};
