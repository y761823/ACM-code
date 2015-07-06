#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

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
    bool operator < (const Point &rhs) const {
        if(y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    Point operator * (const int &b) const {
        return Point(x * b, y * b);
    }
    Point operator / (const int &b) const {
        return Point(x / b, y / b);
    }
    double length() const {
        return sqrt(x * x + y * y);
    }
    Point unit() const {
        return *this / length();
    }
};
typedef Point Vector;

double dist(const Point &a, const Point &b) {
    return (a - b).length();
}

double across(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
//turn left
bool cross(const Point &sp, const Point &ed, const Point &op) {
    return sgn(across(sp - op, ed - op)) > 0;
}

/*******************************************************************************************/

const int MAXN = 55;

Point p[MAXN];
bool del[MAXN];
int n, T;

void solve() {
    memset(del, 0, sizeof(del));
    int last = 0;
    for(int i = 1; i < n; ++i)
        if(p[i] < p[last]) last = i;
    for(int i = 0; i < n; ++i) {
        printf(" %d", last + 1);
        del[last] = true;
        int t = 0;
        for(t = 0; t < n; ++t) if(!del[t]) break;
        for(int j = 0; j < n; ++j) {
            if(del[j] || j == t) continue;
            if(cross(p[j], p[t], p[last])) t = j;
        }
        last = t;
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int t;
        for(int i = 0; i < n; ++i)
            scanf("%d", &t), p[i].read();
        printf("%d", n);
        solve();
        puts("");
    }
}
