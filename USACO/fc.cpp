/*
ID: y7618231
PROG: fc
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const double EPS = 1e-8;

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
    bool operator < (const Point &rhs) const {
        if(y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
};

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}

double dist(const Point &a, const Point &b) {
    Point c = a - b;
    return sqrt(c * c);
}

void Graham_scan(Point p[], int n, int stk[], int &top) {
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

const int MAXN = 10010;

Point p[MAXN];
int stk[MAXN], top, n;

double solve() {
    Graham_scan(p, n, stk, top);
    double res = 0;
    for(int i = 0; i < top; ++i)
        res += dist(p[stk[i]], p[stk[i + 1]]);
    return res;
}

int main() {
#ifndef OYK_JUDGE
    freopen("fc.in", "r", stdin); freopen("fc.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) p[i].read();
    printf("%.2f\n", solve());
}
