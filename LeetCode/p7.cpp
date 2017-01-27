class Solution {
public:
    int reverse(int x) {
        long long res = 0;
        while (x) {
            res = res * 10 + x % 10;
            x /= 10;
        }
        if (res < numeric_limits<int>::min() || res > numeric_limits<int>::max())
            res = 0;
        return res;
    }
};
