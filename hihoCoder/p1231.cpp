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
double sqr(double x) {
    return x * x;
}

typedef complex<double> Point;
#define x real()
#define y imag()

void read(Point &p) {
    static double xx, yy;
    scanf("%lf%lf", &xx, &yy);
    p = Point(xx, yy);
}
Point normal(Point p) {
    return p / abs(p);
}
int type(const Point &p) {
    if(sgn(p.y)) return p.y < 0;
    return p.x < 0;
}
double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
double cross(const Point &a, const Point &b) { // res > 0 means a on right
    return a.x * b.y - a.y * b.x;
}
double cross(const Point &o, const Point &a, const Point &b) { // res < 0 means turn right
    return cross(a - o, b - o);
}
double magnitude(const Point &a, const Point &b) {
    return abs(a - b);
}
Point intersection(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}
bool cmp_ang(const Point &a, const Point &b) {
    if(type(a) != type(b)) return type(a) < type(b);
    return cross(a, b) > 0;
}
//counter-clockwise
Point rotate(const Point &p, double angle, const Point &o = Point(0, 0)) {
    Point t = p - o;
    double xx = t.x * cos(angle) - t.y * sin(angle);
    double yy = t.y * cos(angle) + t.x * sin(angle);
    return Point(xx, yy) + o;
}

double cosIncludeAngle(const Point &a, const Point &b, const Point &o) {
    Point p1 = a - o, p2 = b - o;
    double t = norm(p1) * norm(p2);
    return sgn(t) ? dot(p1, p2) / t : 0;
}

double includedAngle(const Point &a, const Point &b, const Point &o) {
    return acos(cosIncludeAngle(a, b, o));
}

bool isIntersected(const Point &s1, const Point &e1, const Point &s2, const Point &e2) {
    return (max(s1.x, e1.x) >= min(s2.x, e2.x)) &&
        (max(s2.x, e2.x) >= min(s1.x, e1.x)) &&
        (max(s1.y, e1.y) >= min(s2.y, e2.y)) &&
        (max(s2.y, e2.y) >= min(s1.y, e1.y)) &&
        (cross(s2, e1, s1) * cross(e1, e2, s1) >= 0) &&
        (cross(s1, e2, s2) * cross(e2, e1, s2) >= 0);
}

struct Line {
    Point st, ed;
    Line(Point st = 0, Point ed = 0): st(st), ed(ed) {}
    Point operator * (const Line &rhs) const {
        return intersection(st, ed, rhs.st, rhs.ed);
    }
};

bool isInSegRec(const Line &s, const Point &p) {
    return sgn(min(s.st.x, s.ed.x) - p.x) <= 0 && sgn(p.x - max(s.st.x, s.ed.x)) <= 0
        && sgn(min(s.st.y, s.ed.y) - p.y) <= 0 && sgn(p.y - max(s.st.y, s.ed.y)) <= 0;
}

bool isOnSeg(const Line &s, const Point &p) {
    return sgn((p.x - s.st.x) * (p.x - s.ed.x)) <= 0 &&
        sgn((p.y - s.st.y) * (p.y - s.ed.y)) <= 0 &&
        sgn(cross(p, s.st, s.ed)) == 0;
}

double point_to_line(const Point& p, const Line& l) {
    return fabs(cross(p, l.st, l.ed)) / magnitude(l.st, l.ed);
}

struct Circle {
    Point c;
    double r;
    Circle() {}
    Circle(Point c, double r): c(c), r(r) {}
    bool contain(const Point &p) const {
        return sgn(magnitude(c, p) - r) <= 0;
    }
    bool isIntersect(const Line &l) {
        return sgn(point_to_line(c, l) - r) <= 0;
    }
};
void read(Circle &cir) {
    read(cir.c);
    scanf("%lf", &cir.r);
}

void intersect(Circle cir, Line l, Point &p1, Point &p2) {
    Point v = l.ed - l.st, p = cir.c + Point(-v.y, v.x);
    p = intersection(p, cir.c, l.st, l.ed);
    double t = sqrt(sqr(cir.r) - sqr(magnitude(p, cir.c))) / abs(v);
    p1 = p + v * t;
    p2 = p - v * t;
}

bool on_polygon(Point p[], int n, const Point& q) {
    for(int i = 0; i < n; ++i)
        if(isOnSeg(Line(p[i], p[i + 1]), q)) return true;
    return false;
}
bool in_polygon(Point p[], int n, Point q1, int offset = 1e7) {
    Point q2 = q1 + Point(offset, EPS);
    int cnt = 0;
    for(int i = 0; i < n; ++i)
        cnt += isIntersected(q1, q2, p[i], p[i + 1]);
    return cnt & 1;
}

const int MAXN = 1010;

vector<Point> q;
Point p[MAXN];
Circle cir;
int n;

double getArc(Point a, Point b) {
    a -= cir.c; b -= cir.c;
    double ang = arg(b) - arg(a);
    if(sgn(ang) < 0) ang += 2 * PI;
    Point t = cir.c + polar(cir.r, arg(a) + ang / 2);
    if(on_polygon(p, n, t) || in_polygon(p, n, t))
        return ang * cir.r;
    return 0;
}

double solve() {
    Point q1, q2;
    double res = 0;
    q.clear();
    for(int i = 0; i < n; ++i) {
        Line l(p[i], p[i + 1]);
        if(!cir.isIntersect(l)) continue;
        intersect(cir, l, q1, q2);

        bool in1 = isInSegRec(l, q1), in2 = isInSegRec(l, q2);
        if(in1 && in2) {
            res += magnitude(q1, q2);
            q.push_back(q1); q.push_back(q2);
        } else if(in1 || in2) {
            if(in2) q1 = q2;
            if(sgn(magnitude(l.st, cir.c) - cir.r) < 0) res += magnitude(l.st, q1);
            else res += magnitude(l.ed, q2);
            q.push_back(q1);
        } else if(cir.contain(l.st) && cir.contain(l.ed)) {
            res += magnitude(l.st, l.ed);
        }
    }
    if(!q.empty()) {
        sort(q.begin(), q.end(), cmp_ang);
        for(size_t i = 0; i + 1 < q.size(); ++i) {
            res += getArc(q[i], q[i + 1]);
        }
        res += getArc(q.back(), q.front());
    }
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        for(int i = 0; i < n; ++i) read(p[i]);
        p[n] = p[0];
        read(cir);
        printf("%.0f\n", solve());
    }
}
