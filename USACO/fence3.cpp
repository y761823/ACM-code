/*
ID: y7618231
PROG: fence3
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const double EPS = 1e-4;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    double operator * (const Point &rhs) const {
        return x * rhs.x + y * rhs.y;
    }
    double length() {
        return hypot(x, y);
    }
};

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}

double dist(const Point &a, const Point &b) {
    return (a - b).length();
}

double Point_to_Line(const Point &p, const Point &st, const Point &ed) {
    double d = dist(st, ed);
    if(sgn(d) == 0) return dist(p, st);
    return fabs(cross(p, st, ed)) / d;
}

double Point_to_Seg(const Point &p, const Point &st, const Point &ed) {
    if(sgn((ed - st) * (p - st)) < 0) return dist(p, st);
    if(sgn((st - ed) * (p - ed)) < 0) return dist(p, ed);
    return Point_to_Line(p, st, ed);
}

const int MAXN = 155;
Point st[MAXN], ed[MAXN];
double ansx, ansy, ansd;
int n;

int fx[] = {0, 1, 0, -1};
int fy[] = {1, 0, -1, 0};

double random01() {
    return (double)rand() / RAND_MAX;
}

double get_dis(const Point &p) {
    double res = 0;
    for(int i = 0; i < n; ++i)
        res += Point_to_Seg(p, st[i], ed[i]);
    return res;
}

void solve(double x, double y) {
    double t = 10, v = 0.95, res = get_dis(Point(x, y));
    while(t > 1e-2) {
        for(int f = 0; f < 4; ++f) {
            double nx = x + t * fx[f], ny = y + t * fy[f];
            double tmp = get_dis(Point(nx, ny));
            if(tmp < res) {
                x = nx;
                y = ny;
                res = tmp;
            }
        }
        t *= v;
    }
    if(res < ansd) {
        ansx = x;
        ansy = y;
        ansd = res;
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("fence3.in", "r", stdin); freopen("fence3.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        st[i].read(), ed[i].read();
    ansd = get_dis(Point(ansx = 50, ansy = 50));
    for(int i = 0; i < 10; ++i)
        solve(100 * random01(), 100 * random01());
    printf("%.1f %.1f %.1f\n", ansx, ansy, ansd);
}
