/*
ID: y7618231
PROG: fence4
LANG: C++11
*/
// http://blog.163.com/terrorist_1992@126/blog/static/104676822201043103320305/
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
#include <vector>
#include <string>
#include <numeric>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const double EPS = 1e-6;

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
    Point operator * (double rhs) const {
        return Point(x * rhs, y * rhs);
    }
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    bool operator == (const Point &rhs) const {
        return x == rhs.x && y == rhs.y;
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

Point intersection(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}

bool fastjudge(double a1, double a2, double b1, double b2) { // ±ØÐë
    return max(a1, a2) >= min(b1, b2) && max(b1, b2) >= min(a1, a2);
}
bool isIntersected(const Point &a1, const Point &a2, const Point &b1, const Point &b2) {
    return fastjudge(a1.x, a2.x, b1.x, b2.x) && fastjudge(a1.y, a2.y, b1.y, b2.y) &&
        cross(a1, a2, b1) * cross(a1, a2, b2) <= 0 && cross(b1, b2, a1) * cross(b1, b2, a2) <= 0;
}

const int MAXN = 222;

Point p[MAXN], watch;
bool canSee[MAXN];
int n;

void checkLine(double angle) {
    double mind = 1e100;
    double vx = cos(angle), vy = sin(angle);
    Point vec(watch.x + vx, watch.y + vy);
    int res = -1;
    for(int i = 0; i < n; ++i) {
        if(cross(watch, vec, p[i]) * cross(watch, vec, p[i + 1]) >= 0) continue;
        Point t = intersection(watch, vec, p[i], p[i + 1]);
        if((t.x - watch.x) * vx < 0 || (t.y - watch.y) * vy < 0) continue;
        double d = dist(watch, t);
        if(d < mind) {
            res = i;
            mind = d;
        }
    }
    if(res != -1) canSee[res] = true;
}

void print(int i, int j) {
    printf("%.0f %.0f %.0f %.0f\n", p[i].x, p[i].y, p[j].x, p[j].y);
}

bool judgeFence() {
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j) {
            if(p[i + 1] == p[j] || p[j + 1] == p[i]) continue;
            if(isIntersected(p[i], p[i + 1], p[j], p[j + 1])) return false;
        }
    return true;
}

void solve() {
    if(!judgeFence()) {
        puts("NOFENCE");
        return ;
    }
    for(int i = 0; i < n; ++i) {
        double angel = atan2(p[i].y - watch.y, p[i].x - watch.x);
        checkLine(angel - 1e-8);
        checkLine(angel + 1e-8);
    }
    printf("%d\n", accumulate(canSee, canSee + n, 0));
    for(int i = 0; i < n - 2; ++i) if(canSee[i]) print(i, i + 1);
    if(canSee[n - 1]) print(n, n - 1);
    if(canSee[n - 2]) print(n - 2, n - 1);
}

int main() {
#ifndef OYK_JUDGE
    freopen("fence4.in", "r", stdin); freopen("fence4.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    watch.read();
    for(int i = 0; i < n; ++i) p[i].read();
    p[n] = p[0];
    solve();
}
