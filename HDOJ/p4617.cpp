////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-11-23 21:15:56
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4617
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:332KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;

const double EPS = 1e-8;
const double INF = 1e50;
const double PI = acos(-1.0);

inline int sgn(double x) {
    return (x > EPS) - (x < EPS);
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
    double length() const {
        return sqrt(x * x + y * y + z * z);
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

const int MAXN = 35;

Plane3D s[MAXN];
Line3D l[MAXN];
double r[MAXN];
int T, n;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) s[i].read();
        for(int i = 0; i < n; ++i) {
            Point3D v = vector_of_plane(s[i]);
            l[i] = Line3D(s[i].a, s[i].a + v);
            r[i] = dist(s[i].a, s[i].b);
        }
        double ans = INF;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                double d;
                if(isParallel(l[i], l[j])) d = point_to_line(l[i].st, l[j]);
                else d = line_to_line(l[i], l[j]);
                ans = min(ans, d - r[i] - r[j]);
            }
        }
        if(sgn(ans) <= 0) puts("Lucky");
        else printf("%.2f\n", ans);
    }
}
