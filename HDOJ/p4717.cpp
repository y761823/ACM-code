////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-12 22:52:36
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4717
////Problem Title: 
////Run result: Accept
////Run time:2031MS
////Run memory:308KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-14;
const int MAXN = 310;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    Point operator * (const double &rhs) const {
        return Point(x * rhs, y * rhs);
    }
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
};

inline double dist(const Point &a, const Point &b) {
    Point t(a - b);
    return sqrt(t.x * t.x + t.y * t.y);
}

Point a[MAXN], v[MAXN];
int n, T;

double maxlen(double t) {
    double ans = 0;
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            ans = max(ans, dist(a[i] + v[i] * t, a[j] + v[j] * t));
    return ans;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) a[i].read(), v[i].read();
        double l = 0, r = 1e8;
        for(int i = 0; i < 100; ++i) {
            double m1 = l + (r - l) / 3;
            double m2 = r - (r - l) / 3;
            if(maxlen(m1) < maxlen(m2)) r = m2;
            else l = m1;
        }
        printf("Case #%d: %.2f %.2f\n", t, l, maxlen(l));
    }
}
