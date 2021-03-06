#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

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

struct Seg {
    Point st, ed;
    Seg() {}
    Seg(Point st, Point ed): st(st), ed(ed) {}
    void read() {
        st.read(); ed.read();
    }
};
typedef Seg Line;

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

Point intersection(const Line &A, const Line &B) {
    double A1, B1, C1;
    double A2, B2, C2;
    Coefficient(A, A1, B1, C1);
    Coefficient(B, A2, B2, C2);
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

/*******************************************************************************************/


Line a, b;
int n;

int main() {
    scanf("%d", &n);
    puts("INTERSECTING LINES OUTPUT");
    for(int i = 0; i < n; ++i) {
        a.read(), b.read();
        if(isParallel(a, b)) {
            if(isEqual(a, b)) puts("LINE");
            else puts("NONE");
        }
        else {
            Point ans = intersection(a, b);
            printf("POINT %.2f %.2f\n", ans.x, ans.y);
        }
    }
    puts("END OF OUTPUT");
}
