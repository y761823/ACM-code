#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const double EPS = 1e-8;
const double PI = acos(-1.0);//3.14159265358979323846

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
    bool operator == (const Point &rhs) const {
        return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0;
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

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
//ret >= 0 means turn left
double cross(const Point &sp, const Point &ed, const Point &op) {
    return sgn(cross(sp - op, ed - op));
}

double area(const Point& a, const Point &b, const Point &c) {
    return fabs(cross(a - c, b - c)) / 2;
}

struct Seg {
    Point st, ed;
    Seg() {}
    Seg(Point st, Point ed): st(st), ed(ed) {}
    void read() {
        st.read(); ed.read();
    }
};
typedef Seg Line;

bool isOnSeg(const Seg &s, const Point &p) {
    return (p == s.st || p == s.ed) ||
        (((p.x - s.st.x) * (p.x - s.ed.x) < 0 ||
          (p.y - s.st.y) * (p.y - s.ed.y) < 0) &&
         sgn(cross(s.ed, p, s.st) == 0));
}

bool isIntersected(const Point &s1, const Point &e1, const Point &s2, const Point &e2) {
    return (max(s1.x, e1.x) >= min(s2.x, e2.x)) &&
        (max(s2.x, e2.x) >= min(s1.x, e1.x)) &&
        (max(s1.y, e1.y) >= min(s2.y, e2.y)) &&
        (max(s2.y, e2.y) >= min(s1.y, e1.y)) &&
        (cross(s2, e1, s1) * cross(e1, e2, s1) >= 0) &&
        (cross(s1, e2, s2) * cross(e2, e1, s2) >= 0);
}

bool isIntersected(const Seg &a, const Seg &b) {
    return isIntersected(a.st, a.ed, b.st, b.ed);
}

bool isParallel(const Seg &a, const Seg &b) {
    return sgn(cross(a.ed - a.st, b.ed - b.st)) == 0;
}

//return Ax + By + C =0 's A, B, C
void Coefficient(const Line &L, double &A, double &B, double &C) {
    A = L.ed.y - L.st.y;
    B = L.st.x - L.ed.x;
    C = L.ed.x * L.st.y - L.st.x * L.ed.y;
}

Point intersection(const Line &a, const Line &b) {
    double A1, B1, C1;
    double A2, B2, C2;
    Coefficient(a, A1, B1, C1);
    Coefficient(b, A2, B2, C2);
    Point I;
    I.x = - (B2 * C1 - B1 * C2) / (A1 * B2 - A2 * B1);
    I.y =   (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);
    return I;
}

bool isEqual(const Line &a, const Line &b) {
    double A1, B1, C1;
    double A2, B2, C2;
    Coefficient(a, A1, B1, C1);
    Coefficient(b, A2, B2, C2);
    return sgn(A1 * B2 - A2 * B1) == 0 && sgn(A1 * C2 - A2 * C1) == 0 && sgn(B1 * C2 - B2 * C1) == 0;
}

struct Poly {
    int n;
    Point p[MAXN];//p[n] = p[0]
    void init(Point *pp, int nn) {
        n = nn;
        for(int i = 0; i < n; ++i) p[i] = pp[i];
        p[n] = p[0];
    }
    double area() {
        if(n < 3) return 0;
        double s = p[0].y * (p[n - 1].x - p[1].x);
        for(int i = 1; i < n; ++i)
            s += p[i].y * (p[i - 1].x - p[i + 1].x);
        return s / 2;
    }
};

void Graham_scan(Point *p, int n, int *stk, int &top) {//stk[0] = stk[top]
    sort(p, p + n);
    top = 1;
    stk[0] = 0; stk[1] = 1;
    for(int i = 2; i < n; ++i) {
        while(top && cross(p[i], p[stk[top]], p[stk[top - 1]]) >= 0) --top;
        stk[++top] = i;
    }
    int len = top;
    stk[++top] = n - 2;
    for(int i = n - 3; i >= 0; --i) {
        while(top != len && cross(p[i], p[stk[top]], p[stk[top - 1]]) >= 0) --top;
        stk[++top] = i;
    }
}

/*******************************************************************************************/

Point p[MAXN];
Poly poly;
int stk[MAXN], top;
int n, T;

int solve() {
    poly.n = top;
    for(int i = 0; i <= top; ++i) poly.p[i] = p[stk[i]];
    double ret = poly.area() + EPS;
    return int(ret / 50);
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) p[i].read();
    Graham_scan(p, n, stk, top);
    printf("%d\n", solve());
}
