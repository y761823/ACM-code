#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const double EPS = 1e-10;
const double PI = acos(-1.0);//3.14159265358979323846
const double INF = 1;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

inline double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y, ag;
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
    Point operator * (const double &b) const {
        return Point(x * b, y * b);
    }
    Point operator / (const double &b) const {
        return Point(x / b, y / b);
    }
    double operator * (const Point &rhs) const {
        return x * rhs.x + y * rhs.y;
    }
    double length() {
        return sqrt(x * x + y * y);
    }
    double angle() {
        return atan2(y, x);
    }
    Point unit() {
        return *this / length();
    }
    void makeAg() {
        ag = atan2(y, x);
    }
    void print() {
        printf("%.10f %.10f\n", x, y);
    }
};
typedef Point Vector;

double dist(const Point &a, const Point &b) {
    return (a - b).length();
}

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
//ret >= 0 means turn right
double cross(const Point &sp, const Point &ed, const Point &op) {
    return cross(sp - op, ed - op);
}

double area(const Point& a, const Point &b, const Point &c) {
    return fabs(cross(a - c, b - c)) / 2;
}
//counter-clockwise
Point rotate(const Point &p, double angle, const Point &o = Point(0, 0)) {
    Point t = p - o;
    double x = t.x * cos(angle) - t.y * sin(angle);
    double y = t.y * cos(angle) + t.x * sin(angle);
    return Point(x, y) + o;
}

double includedAngle(const Point &a, const Point &b, const Point &o) {
    double ret = abs((a - o).angle() - (b - o).angle());
    if(sgn(ret - PI) > 0) ret = 2 * PI - ret;
    return ret;
}

struct Seg {
    Point st, ed;
    double ag;
    Seg() {}
    Seg(Point st, Point ed): st(st), ed(ed) {}
    void read() {
        st.read(); ed.read();
    }
    void makeAg() {
        ag = atan2(ed.y - st.y, ed.x - st.x);
    }
};
typedef Seg Line;

//ax + by + c > 0
Line buildLine(double a, double b, double c) {
    if(sgn(a) == 0 && sgn(b) == 0) return Line(Point(sgn(c) > 0 ? -1 : 1, INF), Point(0, INF));
    if(sgn(a) == 0) return Line(Point(sgn(b), -c/b), Point(0, -c/b));
    if(sgn(b) == 0) return Line(Point(-c/a, 0), Point(-c/a, sgn(a)));
    if(b < 0) return Line(Point(0, -c/b), Point(1, -(a + c) / b));
    else return Line(Point(1, -(a + c) / b), Point(0, -c/b));
}

void moveRight(Line &v, double r) {
    double dx = v.ed.x - v.st.x, dy = v.ed.y - v.st.y;
    dx = dx / dist(v.st, v.ed) * r;
    dy = dy / dist(v.st, v.ed) * r;
    v.st.x += dy; v.ed.x += dy;
    v.st.y -= dx; v.ed.y -= dx;
}

bool isOnSeg(const Seg &s, const Point &p) {
    return (p == s.st || p == s.ed) ||
        (((p.x - s.st.x) * (p.x - s.ed.x) < 0 ||
          (p.y - s.st.y) * (p.y - s.ed.y) < 0) &&
         sgn(cross(s.ed, p, s.st)) == 0);
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
//point of intersection
Point operator * (const Line &a, const Line &b) {
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

double Point_to_Line(const Point &p, const Line &L) {
    return fabs(cross(p, L.st, L.ed)/dist(L.st, L.ed));
}

double Point_to_Seg(const Point &p, const Seg &L) {
    if(sgn((L.ed - L.st) * (p - L.st)) < 0) return dist(p, L.st);
    if(sgn((L.st - L.ed) * (p - L.ed)) < 0) return dist(p, L.ed);
    return Point_to_Line(p, L);
}

double Seg_to_Seg(const Seg &a, const Seg &b) {
    double ans1 = min(Point_to_Seg(a.st, b), Point_to_Seg(a.ed, b));
    double ans2 = min(Point_to_Seg(b.st, a), Point_to_Seg(b.ed, a));
    return min(ans1, ans2);
}

struct Circle {
    Point c;
    double r;
    Circle() {}
    Circle(Point c, double r): c(c), r(r) {}
    void read() {
        c.read();
        scanf("%lf", &r);
    }
    double area() const {
        return PI * r * r;
    }
    bool contain(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) + rhs.r - r) <= 0;
    }
    bool contain(const Point &p) const {
        return sgn(dist(c, p) - r) <= 0;
    }
    bool intersect(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) - r - rhs.r) < 0;
    }
    bool tangency(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) - r - rhs.r) == 0;
    }
    Point pos(double angle) const {
        Point p = Point(c.x + r, c.y);
        return rotate(p, angle, c);
    }
};

double CommonArea(const Circle &A, const Circle &B) {
    double area = 0.0;
    const Circle & M = (A.r > B.r) ? A : B;
    const Circle & N = (A.r > B.r) ? B : A;
    double D = dist(M.c, N.c);
    if((D < M.r + N.r) && (D > M.r - N.r)) {
        double cosM = (M.r * M.r + D * D - N.r * N.r) / (2.0 * M.r * D);
        double cosN = (N.r * N.r + D * D - M.r * M.r) / (2.0 * N.r * D);
        double alpha = 2 * acos(cosM);//2.0 * ArcCos(cosM);
        double beta = 2 * acos(cosN);//2.0 * ArcCos(cosN);
        double TM = 0.5 * M.r * M.r * (alpha - sin(alpha));
        double TN = 0.5 * N.r * N.r * (beta - sin(beta));
        area = TM + TN;
    }
    else if(D <= M.r - N.r) {
        area = N.area();
    }
    return area;
}

int intersection(const Seg &s, const Circle &cir, Point &p1, Point &p2) {
    double angle = includedAngle(s.ed, cir.c, s.st);
    double B = dist(cir.c, s.st);
    double a = 1, b = -2 * B *  cos(angle), c = sqr(B) - sqr(cir.r);
    double delta = sqr(b) - 4 * a * c;
    if(sgn(delta) < 0) return 0;
    double x1 = (-b - sqrt(delta)) / (2 * a), x2 = (-b + sqrt(delta)) / (2 * a);
    Vector v = (s.ed - s.st).unit();
    p1 = s.st + v * x1;
    p2 = s.st + v * x2;
    return 1 + sgn(delta);
}

double CommonArea(const Circle &cir, Point p1, Point p2) {
    if(cir.contain(p1) && cir.contain(p2)) {
        return area(cir.c, p1, p2);
    } else if(!cir.contain(p1) && !cir.contain(p2)) {
        Point q1, q2;
        int t = intersection(Line(p1, p2), cir, q1, q2);
        if(t == 0) {
            double angle = includedAngle(p1, p2, cir.c);
            return 0.5 * sqr(cir.r) * angle;
        } else {
            double angle1 = includedAngle(p1, p2, cir.c);
            double angle2 = includedAngle(q1, q2, cir.c);
            if(isOnSeg(Seg(p1, p2), q1))return 0.5 * sqr(cir.r) * (angle1 - angle2 + sin(angle2));
            else return 0.5 * sqr(cir.r) * angle1;
            //return 0.5 * sqr(cir.r) * angle1 - 0.5 * sqr(cir.r) * (angle2 - sin(angle2));
        }
    } else {
        if(cir.contain(p2)) swap(p1, p2);
        Point q1, q2;
        intersection(Line(p1, p2), cir, q1, q2);
        double angle = includedAngle(q2, p2, cir.c);
        double a = area(cir.c, p1, q2);
        double b = 0.5 * sqr(cir.r) * angle;
        return a + b;
    }
}

struct Triangle {
    Point p[3];
    Triangle() {}
    Triangle(Point *t) {
        for(int i = 0; i < 3; ++i) p[i] = t[i];
    }
    void read() {
        for(int i = 0; i < 3; ++i) p[i].read();
    }
    double area() const {
        return ::area(p[0], p[1], p[2]);
    }
    Point& operator[] (int i) {
        return p[i];
    }
};

double CommonArea(Triangle tir, const Circle &cir) {
    double ret = 0;
    ret += sgn(cross(tir[0], cir.c, tir[1])) * CommonArea(cir, tir[0], tir[1]);
    ret += sgn(cross(tir[1], cir.c, tir[2])) * CommonArea(cir, tir[1], tir[2]);
    ret += sgn(cross(tir[2], cir.c, tir[0])) * CommonArea(cir, tir[2], tir[0]);
    return abs(ret);
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
//the convex hull is clockwise
void Graham_scan(Point *p, int n, int *stk, int &top) {//stk[0] = stk[top]
    sort(p, p + n);
    top = 1;
    stk[0] = 0; stk[1] = 1;
    for(int i = 2; i < n; ++i) {
        while(top && cross(p[i], p[stk[top]], p[stk[top - 1]]) <= 0) --top;
        stk[++top] = i;
    }
    int len = top;
    stk[++top] = n - 2;
    for(int i = n - 3; i >= 0; --i) {
        while(top != len && cross(p[i], p[stk[top]], p[stk[top - 1]]) <= 0) --top;
        stk[++top] = i;
    }
}
//use for half_planes_cross
bool cmpAg(const Line &a, const Line &b) {
    if(sgn(a.ag - b.ag) == 0)
        return sgn(cross(b.ed, a.st, b.st)) < 0;
    return a.ag < b.ag;
}
//clockwise, plane is on the right
bool half_planes_cross(Line *v, int vn, Poly &res, Line *deq) {
    int i, n;
    sort(v, v + vn, cmpAg);
    for(i = n = 1; i < vn; ++i) {
        if(sgn(v[i].ag - v[i-1].ag) == 0) continue;
        v[n++] = v[i];
    }
    int head = 0, tail = 1;
    deq[0] = v[0], deq[1] = v[1];
    for(i = 2; i < n; ++i) {
        if(isParallel(deq[tail - 1], deq[tail]) || isParallel(deq[head], deq[head + 1]))
            return false;
        while(head < tail && sgn(cross(v[i].ed, deq[tail - 1] * deq[tail], v[i].st)) > 0)
            --tail;
        while(head < tail && sgn(cross(v[i].ed, deq[head] * deq[head + 1], v[i].st)) > 0)
            ++head;
        deq[++tail] = v[i];
    }
    while(head < tail && sgn(cross(deq[head].ed, deq[tail - 1] * deq[tail], deq[head].st)) > 0)
        --tail;
    while(head < tail && sgn(cross(deq[tail].ed, deq[head] * deq[head + 1], deq[tail].st)) > 0)
        ++head;
    if(tail <= head + 1) return false;
    res.n = 0;
    for(i = head; i < tail; ++i)
        res.p[res.n++] = deq[i] * deq[i + 1];
    res.p[res.n++] = deq[head] * deq[tail];
    res.n = unique(res.p, res.p + res.n) - res.p;
    res.p[res.n] = res.p[0];
    return true;
}

//ix and jx is the points whose distance is return, res.p[n - 1] = res.p[0], res must be clockwise
double dia_rotating_calipers(Poly &res, int &ix, int &jx) {
    double dia = 0;
    int q = 1;
    for(int i = 0; i < res.n - 1; ++i) {
        while(sgn(cross(res.p[i], res.p[q + 1], res.p[i + 1]) - cross(res.p[i], res.p[q], res.p[i + 1])) > 0)
            q = (q + 1) % (res.n - 1);
        if(sgn(dist(res.p[i], res.p[q]) - dia) > 0) {
            dia = dist(res.p[i], res.p[q]);
            ix = i; jx = q;
        }
        if(sgn(dist(res.p[i + 1], res.p[q]) - dia) > 0) {
            dia = dist(res.p[i + 1], res.p[q]);
            ix = i + 1; jx = q;
        }
    }
    return dia;
}
//a and b must be clockwise, find the minimum distance between two convex hull
double half_rotating_calipers(Poly &a, Poly &b) {
    int sa = 0, sb = 0;
    for(int i = 0; i < a.n; ++i) if(sgn(a.p[i].y - a.p[sa].y) < 0) sa = i;
    for(int i = 0; i < b.n; ++i) if(sgn(b.p[i].y - b.p[sb].y) < 0) sb = i;
    double tmp, ans = dist(a.p[0], b.p[0]);
    for(int i = 0; i < a.n; ++i) {
        while(sgn(tmp = cross(a.p[sa], a.p[sa + 1], b.p[sb + 1]) - cross(a.p[sa], a.p[sa + 1], b.p[sb])) > 0)
            sb = (sb + 1) % (b.n - 1);
        if(sgn(tmp) < 0) ans = min(ans, Point_to_Seg(b.p[sb], Seg(a.p[sa], a.p[sa + 1])));
        else ans = min(ans, Seg_to_Seg(Seg(a.p[sa], a.p[sa + 1]), Seg(b.p[sb], b.p[sb + 1])));
        sa = (sa + 1) % (a.n - 1);
    }
    return ans;
}

double rotating_calipers(Poly &a, Poly &b) {
    return min(half_rotating_calipers(a, b), half_rotating_calipers(b, a));
}

/*******************************************************************************************/

Triangle tir;
Circle cir;

int main() {
    while(scanf("%lf%lf", &tir[0].x, &tir[0].y) != EOF) {
        tir[1].read();
        tir[2].read();
        cir.read();
        //cout<<Point_to_Line(cir.c, Line(tir[0], tir[1]))<<endl;
        if(sgn(cross(tir[0], tir[1], tir[2])) == 0) puts("0.00");
        else printf("%.2f\n", CommonArea(tir, cir) + EPS);
    }
}
