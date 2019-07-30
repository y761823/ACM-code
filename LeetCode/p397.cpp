class Solution {
public:
    int integerReplacement(int _n) {
        int cnt = 0;
        unsigned n = _n;
        while (n != 1) {
            if ((n & 1) == 0) {
                n >>= 1;
            } else if ((n & 3) == 3 && n != 3) {
                n++;
            } else {
                n--;
            }
            cnt++;
        }
        return cnt;
    }
};
