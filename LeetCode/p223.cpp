class Solution {
public:
    int computeArea(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
        long sum = long(x2 - x1) * (y2 - y1) + (x4 - x3) * (y4 - y3);
        if (x2 <= x3 || x4 <= x1 || y2 <= y3 || y4 <= y1)
            return (int)sum;
        sum -= (min(x2, x4) - max(x1, x3)) * (min(y2, y4) - max(y1, y3));
        return sum;
    }
};
