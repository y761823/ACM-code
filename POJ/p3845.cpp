#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 110;
const double EPS = 1e-8;
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
    double length() {
        return sqrt(x * x + y * y);
    }
    Point unit() {
        return *this / length();
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
//ret >= 0 means turn left
double cross(const Point &sp, const Point &ed, const Point &op) {
    return sgn(cross(sp - op, ed - op));
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

/*******************************************************************************************/

Point p[MAXN], ans;
double f[15], sum[MAXN];
double len, sqrt2 = sqrt(2);
int c, n, d;

void dfs(const Point &a, const Point &b, double len, int dep) {
    if(dep == 0) {
        ans = (b - a) * len / dist(a, b) + a;
    } else {
        for(int i = 1; i < n; ++i) {
            if(sgn(sum[i] * dist(a, b) / dist(p[0], p[n - 1]) * f[dep] - len) < 0) continue;
            double angle1 = atan2(p[n - 1].y - p[0].y, p[n - 1].x - p[0].x);
            double angle2 = atan2(b.y - a.y, b.x - a.x);
            Point o = rotate(p[i - 1], angle2 - angle1, p[0]);
            o = (o - p[0]) * dist(a, b) / dist(p[0], p[n - 1]) + a;
            Point t = rotate(p[i], angle2 - angle1, p[0]);
            t = (t - p[0]) * dist(a, b) / dist(p[0], p[n - 1]) + a;
            dfs(o, t, len - sum[i - 1] * f[dep] * dist(a, b) / dist(p[0], p[n - 1]), dep - 1);
            return ;
        }
    }
}

void solve() {
    sum[0] = 0;
    for(int i = 1; i < n; ++i) sum[i] = sum[i - 1] + dist(p[i - 1], p[i]);
    f[1] = 1;
    double tmp = sum[n - 1] / dist(p[0], p[n - 1]);
    for(int i = 2; i <= d; ++i) f[i] = f[i - 1] * tmp;
    dfs(p[0], p[n - 1], len * sum[n - 1] * f[d], d);
}

int main() {
    scanf("%d", &c);
    while(c--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) p[i].read();
        scanf("%d%lf", &d, &len);
        solve();
        printf("(%.10f,%.10f)\n", ans.x, ans.y);
    }
}
