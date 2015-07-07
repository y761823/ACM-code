////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-13 19:34:15
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4998
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:320KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;

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

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}

Point intersection(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}

struct Seg {
    Point st, ed;
    double ag;
    Seg() {}
    Seg(Point st, Point ed): st(st), ed(ed) {}
    void read() {
        st.read(); ed.read();
    }
    double makeAg() {
        return ag = atan2(ed.y - st.y, ed.x - st.x);
    }
};
typedef Seg Line;

Point rotate(const Point &p, double angle, const Point &o = Point(0, 0)) {
    Point t = p - o;
    double x = t.x * cos(angle) - t.y * sin(angle);
    double y = t.y * cos(angle) + t.x * sin(angle);
    return Point(x, y) + o;
}

Point o1 = Point(200, 0), o2 = Point(0, 200);
Point a1, a2;
Point c;
double r;
int T, n;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        a1 = o1, a2 = o2;
        for(int i = 0; i < n; ++i) {
            c.read(); scanf("%lf", &r);
            a1 = rotate(a1, r, c);
            a2 = rotate(a2, r, c);
        }
        Point u1 = (o1 + a1) / 2, u2 = u1 + rotate(o1 - a1, PI / 2);
        Point v1 = (o2 + a2) / 2, v2 = v1 + rotate(o2 - a2, PI / 2);
        Point res = intersection(u1, u2, v1, v2);
        double ans = Line(res, a1).makeAg() - Line(res, o1).makeAg();
        if(sgn(ans) < 0) ans += 2 * PI;
        printf("%.10f %.10f %.10f\n", res.x, res.y, ans);
    }
}