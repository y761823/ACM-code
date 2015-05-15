#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXV = 310;
const double EPS = 1e-6;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

inline bool equ(double a, double b) {
    return sgn(a - b) == 0;
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator * (double d) const {
        return Point(x * d, y * d);
    }
    double norm() const {
        return hypot(x, y);
    }
};

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
double cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}

bool fastjudge(double a1, double a2, double b1, double b2) {
    return max(a1, a2) > min(b1, b2) && max(b1, b2) > min(a1, a2);
}
bool isIntersected(const Point &a1, const Point &a2, const Point &b1, const Point &b2) {
    return fastjudge(a1.x, a2.x, b1.x, b2.x) && fastjudge(a1.y, a2.y, b1.y, b2.y) &&
        cross(a1, a2, b1) * cross(a1, a2, b2) <= 0 && cross(b1, b2, a1) * cross(b1, b2, a2) <= 0;
}

Point intersected(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}

double getValOn(const Point &a, const Point &b, double x) {
    double t = (x - a.x) / (b.x - a.x);
    return (a + (b - a) * t).y;
}

char rgb[] = "RGB";
Point a[MAXV], b[MAXV];
int color[MAXV];
double ans[5];
int n;

int find_bottom(double l, double r) {
    double mid = (l + r) / 2;
    int res = n;
    for(int i = 0; i < n; ++i) if(sgn(a[i].x - l) <= 0 && sgn(r - b[i].x) <= 0) {
        if(res == n || getValOn(a[i], b[i], mid) < getValOn(a[res], b[res], mid))
            res = i;
    }
    return color[res];
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        char c;
        scanf("%lf%lf%lf%lf %c", &a[i].x, &a[i].y, &b[i].x, &b[i].y, &c);
        if(a[i].x > b[i].x) swap(a[i], b[i]);
        color[i] = strchr(rgb, c) - rgb;
    }
    color[n] = 3;

    vector<double> xhash;
    for(int i = 0; i < n; ++i) {
        xhash.push_back(a[i].x);
        xhash.push_back(b[i].x);
        for(int j = i + 1; j < n; ++j) if(isIntersected(a[i], b[i], a[j], b[j])) {
            xhash.push_back(intersected(a[i], b[i], a[j], b[j]).x);
        }
    }
    sort(xhash.begin(), xhash.end());
    xhash.erase(unique(xhash.begin(), xhash.end(), equ), xhash.end());

    for(size_t i = 0; i + 1 < xhash.size(); ++i) {
        double x1 = xhash[i], x2 = xhash[i + 1];
        ans[find_bottom(x1, x2)] += x2 - x1;
    }

    for(int i = 0; i < 3; ++i) printf("%c %f\n", rgb[i], ans[i]);
}
