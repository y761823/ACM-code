class Solution {
public:
    int mySqrt(int x) {
        long long r = x;
        while (r * r > x)
            r = (r * r + x) / (2 * r);
        return (int)r;
    }
};
