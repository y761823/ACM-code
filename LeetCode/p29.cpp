class Solution {
public:
    int divide(int dividend, int divisor) {
        if (!divisor) return numeric_limits<int>::max();
        
        int flag = (dividend < 0) ^ (divisor < 0) ? -1 : 1;
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);
        
        long long res = 0, y = 1;
        long long xx = b;
        while ((xx << 1) <= a)
            xx <<= 1, y <<= 1;
        long long x = xx;
            
        while (y) {
            if (a >= x)
                a -= x, res += y;
            x >>= 1, y >>= 1;
        }
        
        res = res * flag;
        if (res > numeric_limits<int>::max())
            return numeric_limits<int>::max();
        return res;
    }
};
