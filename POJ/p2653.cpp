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
//ret >= 0 means turn left
double cross(const Point &sp, const Point &ed, const Point &op) {
    return sgn(across(sp - op, ed - op));
}

struct Seg {
    Point st, ed;
    Seg() {}
    Seg(Point st, Point ed): st(st), ed(ed) {}
    void read() {
        st.read(); ed.read();
    }
};

bool isIntersected(Point s1, Point e1, Point s2, Point e2) {
    return (max(s1.x, e1.x) >= min(s2.x, e2.x)) &&
        (max(s2.x, e2.x) >= min(s1.x, e1.x)) &&
        (max(s1.y, e1.y) >= min(s2.y, e2.y)) &&
        (max(s2.y, e2.y) >= min(s1.y, e1.y)) &&
        (cross(s2, e1, s1) * cross(e1, e2, s1) >= 0) &&
        (cross(s1, e2, s2) * cross(e2, e1, s2) >= 0);
}

bool isIntersected(Seg a, Seg b) {
    return isIntersected(a.st, a.ed, b.st, b.ed);
}

/*******************************************************************************************/

const int MAXN = 100010;

Seg s[MAXN];
bool isAns[MAXN];
Point p;
int n;

int main() {
    while(scanf("%d", &n) != EOF && n) {
        memset(isAns, true, sizeof(isAns));
        for(int i = 0; i < n; ++i) s[i].read();
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                if(isIntersected(s[i], s[j])) {
                    isAns[i] = false;
                    break;
                }
            }
        bool flag = false;
        printf("Top sticks:");
        for(int i = 0; i < n; ++i) {
            if(!isAns[i]) continue;
            if(flag) printf(",");
            else flag = true;
            printf(" %d", i + 1);
        }
        puts(".");
    }
}
