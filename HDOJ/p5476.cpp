#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <complex>
using namespace std;
typedef long long LL;

const double EPS = 1e-10;
const double PI = acos(-1);
int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

typedef complex<double> Point;
#define x real()
#define y imag()

void read(Point &p) {
    static double xx, yy;
    scanf("%lf%lf", &xx, &yy);
    p = Point(xx, yy);
}
double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
double cross(const Point &a, const Point &b) { // res > 0 means a on right
    return a.x * b.y - a.y * b.x;
}
Point intersection(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}
double magnitude(const Point &a, const Point &b) {
    return abs(a - b);
}
double cosIncludeAngle(const Point &a, const Point &b, const Point &o) {
    Point p1 = a - o, p2 = b - o;
    double t = abs(p1) * abs(p2);
    return sgn(t) ? dot(p1, p2) / t : 0;
}
double includedAngle(const Point &a, const Point &b, const Point &o) {
    return acos(cosIncludeAngle(a, b, o));
}

void pingfenxian(const Point &a, const Point &b, Point &c, Point &d) {
    c = (a + b) * 0.5;
    Point t = (a - b);
    d = c + Point(-t.y, t.x);
}

Point ac, ac2, m, d, cen;
Point a, b, c;
int T;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        read(a); read(b); read(c);
        pingfenxian(a, c, ac, ac2);
        m = (b + c) * 0.5;
        cen = intersection(ac, ac2, a, m);
        d = cen + (cen - a);
        double ang = includedAngle(b, c, d);
        double tmp = ang * magnitude(b, d);
        printf("Case #%d: %.4f\n", t, magnitude(a, m) + tmp);
    }
}
