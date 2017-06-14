class Solution {
    int power(int x, int p) {
        int res = 1;
        while (p) {
            if (p & 1) res *= x;
            x *= x;
            p >>= 1;
        }
        return res;
    }
public:
    int integerBreak(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        
        int a = n / 3, b = n % 3;
        if (b == 0) return power(3, a);
        if (b == 1) return power(3, a - 1) * 4;
        return power(3, a) * 2;
    }
};
