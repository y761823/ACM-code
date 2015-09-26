#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <complex>
using namespace std;
typedef long long LL;

const double EPS = 1e-10;
int sgn(double x) {
    return (x > EPS) - (x < -EPS);
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
    double t = abs(p1) * abs(p2);
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
    Point s, e; double angle;
    Line(Point s = 0, Point e = 0): s(s), e(e) {}
    double get_angle() {
        return angle = arg(e - s);
    }
    Point operator * (const Line &rhs) const {
        return intersection(s, e, rhs.s, rhs.e);
    }
    bool operator < (const Line &rhs) const {
        return angle < rhs.angle;
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

typedef vector<Point> Polygon;
double get_area(const Polygon& p) {
    double res = cross(p.back(), p.front());
    for(size_t i = 0; i < p.size() - 1; ++i)
        res += cross(p[i], p[i + 1]);
    return fabs(res) / 2;
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

void half_planes_cross(vector<Line> &l, int n, Polygon &poly) {
    for(int i = 0; i < n; ++i) l[i].get_angle();
    sort(l.begin(), l.end());
    vector<Point> q(n);
    int head = 0, tail = 0;
    for(int i = 1; i < n; ++i) {
        while(head != tail && sgn(cross(l[i].s, l[i].e, q[tail - 1])) <= 0) --tail;
        while(head != tail && sgn(cross(l[i].s, l[i].e, q[head])) <= 0) ++head;
        l[++tail] = l[i];
        if(head < tail) q[tail - 1] = l[tail - 1] * l[tail];
    }
    while(head != tail && sgn(cross(l[head].s, l[head].e, q[tail - 1])) <= 0) --tail;
    if(head < tail) q[tail] = l[head] * l[tail];
    poly.assign(q.begin() + head, q.begin() + tail + 1);
}
