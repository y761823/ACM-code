#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef complex<double> Complex;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 155;
const double PI = acos(-1.0);
const double EPS = 1e-10;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    void print() const {
        printf("%.6f %.6f\n", x + EPS, y + EPS);
    }
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    Point operator * (double d) const {
        return Point(x * d, y * d);
    }
    double length() const {
        return hypot(x, y);
    }
};

Point rotate(Point p, double rad, Point o) {
    p = p - o;
    Complex res = Complex(p.x, p.y) * Complex(cos(rad), sin(rad));
    return Point(res.real(), res.imag()) + o;
}

double dist(Point a, Point b) {
    return (a - b).length();
}

Point getPoint(Point a, Point b, double l) {
    Point v = (b - a);
    return a + v * (l / v.length());
}

Point p0, p1;
int n, n0, n1;

Point getCenter(int m) {
    bool flag = (m <= n / 2);
    double a = 2 * PI / n * (flag ? m : n - m);
    double d = dist(p0, p1);
    double r = (2 * m == n) ? d / 2 : sqrt(0.5 * d * d / (1 - cos(a)));
    double b = (PI - a) / 2;
    return getPoint(p0, rotate(p1, flag ? -b : b, p0), r);
}

int main() {
    scanf("%d%d%d", &n, &n0, &n1);
    p0.read(); p1.read();
    Point c = getCenter((n1 - n0 + n) % n);
    double rad = 2 * PI / n;
    Point p = rotate(p0, (n0 - 1) * rad, c);
    for(int i = 0; i < n; ++i) {
        p.print();
        p = rotate(p, -rad, c);
    }
}
