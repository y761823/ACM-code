#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <complex>
using namespace std;
typedef long long LL;

typedef complex<double> Point;
#define x real()
#define y imag()

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
double cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}
Point intersection(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}

double area(const Point &a, const Point &b, const Point &c, const Point &d) {
    return abs(cross(a, b, c) / 2) + abs(cross(a, c, d) / 2);
}

const int MAXN = 35;

Point p[MAXN][MAXN];
double a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int n;

void init() {
    p[0][0] = Point(0.0, 0.0);
    p[0][n + 1] = Point(0.0, 1.0);
    p[n + 1][0] = Point(1.0, 0.0);
    p[n + 1][n + 1] = Point(1.0, 1.0);

    for(int i = 1; i <= n; ++i) {
        p[0][i] = Point(0.0, c[i]);
        p[n + 1][i] = Point(1.0, d[i]);
        p[i][0] = Point(a[i], 0.0);
        p[i][n + 1] = Point(b[i], 1.0);
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            p[i][j] = intersection(Point(a[i], 0.0), Point(b[i], 1.0), Point(0.0, c[j]), Point(1.0, d[j]));
    }

    //for(int i = 0; i <= n + 1; ++i) {for(int j = 0; j <= n + 1; ++j) printf("%.3f-%.3f ", p[i][j].x, p[i][j].y); puts("");}
}

double solve() {
    double res = 0;
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= n; ++j)
            res = max(res, area(p[i][j], p[i + 1][j], p[i + 1][j + 1], p[i][j + 1]));
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 1; i <= n; ++i) scanf("%lf", &a[i]);
        for(int i = 1; i <= n; ++i) scanf("%lf", &b[i]);
        for(int i = 1; i <= n; ++i) scanf("%lf", &c[i]);
        for(int i = 1; i <= n; ++i) scanf("%lf", &d[i]);
        init();
        printf("%.6f\n", solve());
    }
}
