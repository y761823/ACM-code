/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int res = 0;
        for (int i = 0; i < points.size(); ++i) {
            map<pair<int, int>, int> tmap;
            int rep = 0;
            for (int j = 0; j < points.size(); ++j) {
                int a = points[j].x - points[i].x, b = points[j].y - points[i].y;
                if (a == 0 && b == 0) {
                    rep++;
                } else {
                    int gcd = __gcd(a, b);
                    tmap[make_pair(a / gcd, b / gcd)]++;
                }
            }
            int maxcnt = 0;
            for (auto& p : tmap)
                maxcnt = max(maxcnt, p.second);
            res = max(res, rep + maxcnt);
        }
        return res;
    }
};
