#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXN = 4010;
const double EPS = 1e-10;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    double operator * (const Point &rhs) const {
        return x * rhs.x + y * rhs.y;
    }
    Point operator / (const double &rhs) const {
        return Point(x / rhs, y / rhs);
    }
    bool operator < (const Point &rhs) const {
        if(y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
    double angle() const {
        return atan2(y, x);
    }
};
typedef Point Vector;

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double cross(const Point &sp, const Point &op, const Point &ep) {
    return cross(sp - op, ep - op);
}

void Graham_scan(Point *p, int n, int *stk, int &top) {
    sort(p, p + n);
    top = 1;
    stk[0] = 0; stk[1] = 1;
    for(int i = 2; i < n; ++i) {
        while(top && cross(p[stk[top - 1]], p[stk[top]], p[i]) <= 0) --top;
        stk[++top] = i;
    }
    int len = top;
    stk[++top] = n - 2;
    for(int i = n - 3; i >= 0; --i) {
        while(top != len && cross(p[stk[top - 1]], p[stk[top]], p[i]) <= 0) --top;
        stk[++top] = i;
    }
}

Point rotate(const Point &p, double angle, const Point &o = Point(0, 0)) {
    Point t = p - o;
    double x = t.x * cos(angle) - t.y * sin(angle);
    double y = t.y * cos(angle) + t.x * sin(angle);
    return Point(x, y) + o;
}

Point p[MAXN], q[MAXN];
int stk[MAXN], top;
int n, T;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        n <<= 2;
        for(int i = 0; i < n; ++i) p[i].read();
        p[n] = p[0];
        Graham_scan(p, n, stk, top);

        double res = 1e100;
        for(int i = 0; i < top; ++i) {
            Point x = p[stk[i]], y = p[stk[i + 1]];
            double ll = 1e100, rr = -1e100, uu = -1e100, dd = 1e100;
            double angle = -(y - x).angle();
            for(int i = 0; i < n; ++i) {
                Point v = rotate(p[i], angle, x);
                ll = min(ll, v.x), rr = max(rr, v.x);
                dd = min(dd, v.y), uu = max(uu, v.y);
            }
            res = min(res, (rr - ll) * (uu - dd));
        }
        printf("Case #%d:\n%.f\n", t, res);
    }
}
