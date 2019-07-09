class Solution {
public:
    int lowbit(int x) {
        return x & -x;
    }
    
    int getNextZero(int x, int bit) { // if bit=00010000, 01011100 -> 01100000
        int res = x & ~(bit - 1);
        return (long)res + bit;
    }
    
    int rangeBitwiseAnd(int m, int n) {
        int res = 0;
        for (int rest = m; rest != 0; rest -= lowbit(rest)) {
            int bit = lowbit(rest);
            int next = getNextZero(m, bit);
            if (next < 0 || next > n)
                res |= bit;
        }
        return res;
    }
};
