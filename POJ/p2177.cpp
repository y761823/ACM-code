#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;

const double EPS = 1e-6;
const double INF = 1e50;
const double PI = acos(-1.0);

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

inline double zero(double x) {
    if(sgn(x) == 0) return 0;
    else return x;
}

inline double sqr(double x) {
    return x * x;
}

struct Point3D {
    double x, y, z;
    Point3D() {}
    Point3D(double x, double y, double z): x(x), y(y), z(z) {}
    void read() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
    double operator * (const Point3D &rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    Point3D operator + (const Point3D &rhs) const {
        return Point3D(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    Point3D operator - (const Point3D &rhs) const {
        return Point3D(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    Point3D operator * (double rhs) const {
        return Point3D(x * rhs, y * rhs, z * rhs);
    }
    Point3D operator / (double rhs) const {
        return Point3D(x / rhs, y / rhs, z / rhs);
    }
    bool operator == (const Point3D &rhs) const {
        return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0 && sgn(z - rhs.z) == 0;
    }
    double length() const {
        return sqrt(x * x + y * y + z * z);
    }
    Point3D unit() const {
        return *this / length();
    }
};

struct Line3D {
    Point3D st, ed;
    Line3D() {}
    Line3D(Point3D st, Point3D ed): st(st), ed(ed) {}
};

struct Plane3D {
    Point3D a, b, c;
    Plane3D() {}
    Plane3D(Point3D a, Point3D b, Point3D c): a(a), b(b), c(c) {}
    void read() {
        a.read(), b.read(), c.read();
    }
};

struct Circle3D {
    Point3D c;
    double r;
    Circle3D() {}
    Circle3D(Point3D c, double r): c(c), r(r) {}
    void read() {
        c.read();
        scanf("%lf", &r);
    }
};

double dist(const Point3D &a, const Point3D &b) {
    return (a - b).length();
}
//叉积
Point3D cross(const Point3D &u, const Point3D &v) {
    Point3D ret;
    ret.x = u.y * v.z - u.z * v.y;
    ret.y = u.z * v.x - u.x * v.z;
    ret.z = u.x * v.y - u.y * v.x;
    return ret;
}
//点到直线距离
double point_to_line(const Point3D &p, const Line3D &l) {
    return cross(p - l.st, l.ed - l.st).length() / dist(l.ed, l.st);
}
//求两直线间的距离
double line_to_line(const Line3D u, const Line3D v) {
    Point3D n = cross(u.ed - u.st, v.ed - v.st);
    return fabs((u.st - v.st) * n) / n.length();
}
//取平面法向量
Point3D vector_of_plane(const Plane3D &s) {
    return cross(s.a - s.b, s.b - s.c);
}
//判断两直线是否平行
bool isParallel(const Line3D &u, const Line3D &v) {
    return sgn(cross(u.ed - u.st, v.ed - v.st).length()) <= 0;
}
//判断直线是否与球相交
bool isIntersect(const Line3D &l, const Circle3D &cir) {
    return sgn(point_to_line(cir.c, l) - cir.r) <= 0;
}
//直线与平面的交点
Point3D intersect(const Line3D &l, const Plane3D &s) {
    Point3D ret = vector_of_plane(s);
    double t = (ret * (s.a - l.st)) / (ret * (l.ed - l.st));
    return l.st + (l.ed - l.st) * t;
}
//在原点上看，两个球的交点
int intersect(const Circle3D &u, const Circle3D &v, Point3D &p1, Point3D &p2) {
    double d = dist(u.c, v.c);
    if(u.c == v.c || sgn(d - u.r - v.r) > 0 || sgn(fabs(u.r - v.r) - d) > 0) return 0;
    double t = (sqr(d) + sqr(u.r) - sqr(v.r)) / (2 * d);
    Point3D mid = u.c + (v.c - u.c).unit() * t;
    Point3D vec = cross(mid, v.c - u.c).unit() * sqrt(zero(sqr(u.r) - sqr(t)));
    p1 = mid + vec;
    p2 = mid - vec;
    return 1 + sgn(vec.length());
}

const int MAXN = 110;

Circle3D cir[MAXN];
Point3D p[MAXN * MAXN], ansVec;
int maxAns, pcnt;
int n;

int count(const Point3D &vec) {
    int ret = 0;
    for(int i = 0; i < n; ++i)
        ret += (sgn(point_to_line(cir[i].c, Line3D(Point3D(0, 0, 0), vec)) - cir[i].r) <= 0);
    return ret;
}

void output(const Point3D &vec) {
    bool flag = false;
    for(int i = 0; i < n; ++i) {
        if(sgn(point_to_line(cir[i].c, Line3D(Point3D(0, 0, 0), vec)) - cir[i].r) <= 0) {
            if(flag) putchar(' ');
            flag = true;
            printf("%d", i + 1);
        }
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) cir[i].read();
    Plane3D plane(Point3D(20000, 0, 0), Point3D(0, 20000, 0), Point3D(0, 0, 20000));
    for(int i = 0; i < n; ++i) {
        double t = 20000 / cir[i].c.length();
        cir[i].c = cir[i].c * t;
        cir[i].r = cir[i].r * t;
    }
    pcnt = 0;
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j) pcnt += intersect(cir[i], cir[j], p[pcnt], p[pcnt + 1]);
    maxAns = 0;
    for(int i = 0; i < n; ++i) {
        int t = count(cir[i].c);
        if(t > maxAns) {
            maxAns = t;
            ansVec = cir[i].c;
        }
    }
    for(int i = 0; i < pcnt; ++i) {
        int t = count(p[i]);
        if(t > maxAns) {
            maxAns = t;
            ansVec = p[i];
        }
    }
    printf("%d\n", maxAns);
    output(ansVec);
}
