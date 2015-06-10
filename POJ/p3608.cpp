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
double dia_roataing_calipers(Poly &res, int &ix, int &jx) {
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
//a and b must be clockwise
double dia_roataing_calipers(Poly &a, Poly &b) {
    int sa = 0, sb = 0;
    for(int i = 0; i < a.n; ++i) if(sgn(a.p[i].y - a.p[sa].y) < 0) sa = i;
    for(int i = 0; i < b.n; ++i) if(sgn(b.p[i].y - b.p[sb].y) < 0) sb = i;
    double tmp, ans = dist(a.p[0], b.p[0]);
    for(int i = 0; i < a.n; ++i) {
        while(sgn(tmp = cross(a.p[sa], a.p[sa + 1], b.p[sb]) - cross(a.p[sa], a.p[sa + 1], b.p[sb + 1])) < 0)
            sb = (sb + 1) % (b.n - 1);
        if(sgn(tmp) > 0) ans = min(ans, Point_to_Seg(b.p[sb], Seg(a.p[sa], a.p[sa + 1])));
        else ans = min(ans, Seg_to_Seg(Seg(a.p[sa], a.p[sa + 1]), Seg(b.p[sb], b.p[sb + 1])));
        sa = (sa + 1) % (a.n - 1);
    }
    return ans;
}

/*******************************************************************************************/

Poly a, b;

double solve() {
    double ans = 1e100;
    for(int i = 0; i < a.n; ++i)
        for(int j = 0; j < b.n; ++j) ans = min(ans, dist(a.p[i], b.p[j]));
    return ans;
}

int main() {
    while(scanf("%d%d", &a.n, &b.n) != EOF) {
        if(a.n == 0 && b.n == 0) break;
        for(int i = 0; i < a.n; ++i) a.p[i].read();
        a.p[a.n++] = a.p[0];
        for(int i = 0; i < b.n; ++i) b.p[i].read();
        b.p[b.n++] = b.p[0];
        printf("%f\n", min(dia_roataing_calipers(a, b), dia_roataing_calipers(b, a)));
        //printf("%f\n", solve());
    }
    return 0;
}
