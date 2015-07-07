////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-29 21:21:52
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4766
////Problem Title: 
////Run result: Accept
////Run time:546MS
////Run memory:252KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const double INF = 1e100;
const double EPS = 1e-4;

struct Point {
    double x, y;
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    double small();
    Point(double xx = 0, double yy = 0): x(xx), y(yy) {}
};

double operator ^ (const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

Point operator + (const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator / (const Point &a, double b) {
    return Point(a.x / b, a.y / b);
}

Point operator * (const Point &a, double b) {
    return Point(a.x * b, a.y * b);
}

double dist(const Point &a, const Point &b = Point(0, 0)) {
    double x = a.x - b.x, y = a.y - b.y;
    return sqrt(x * x + y * y);
}

Point small(Point x) {
    double dis = dist(x);
    return x / dis;
}

Point turn90(const Point &a) {
    return small(Point(-a.y, a.x));
}

double len3(double a, double b) {
    return sqrt(b * b - a * a);
}

Point p[MAXN], src;
double d;
int n;

struct Circle {
    double r;
    Point centre;
} c;

struct Triangle {
    Point t[3];
    double Area() {
        return fabs((t[1] - t[0]) ^ (t[2] - t[0]))/2;
    }
};

Circle circumcircleOfTriangle(Triangle t) {
    Circle tmp;
    double a, b, c, c1, c2;
    Point A(t.t[0].x, t.t[0].y);
    Point B(t.t[1].x, t.t[1].y);
    Point C(t.t[2].x, t.t[2].y);
    a = dist(B, C);
    b = dist(A, C);
    c = dist(A, B);
    tmp.r = a * b * c / t.Area() / 4;
    c1 = (A.x * A.x + A.y * A.y - B.x * B.x - B.y * B.y) / 2;
    c2 = (A.x * A.x + A.y * A.y - C.x * C.x - C.y * C.y) / 2;
    tmp.centre.x = (c1 * (A.y - C.y) - c2 * (A.y - B.y)) / ((A.x - B.x) * (A.y - C.y) - (A.x - C.x) * (A.y - B.y));
    tmp.centre.y = (c1 * (A.x - C.x) - c2 * (A.x - B.x)) / ((A.y - B.y) * (A.x - C.x) - (A.y - C.y) * (A.x - B.x));
    return tmp;
}

Circle MinCircle2(int tce, Triangle ce) {
    Circle tmp;
    if(tce == 0) tmp.r = -2;
    else if(tce == 1) {
        tmp.centre = ce.t[0];
        tmp.r = 0;
    }
    else if(tce == 2) {
        tmp.r = dist(ce.t[0], ce.t[1]) / 2;
        tmp.centre.x = (ce.t[0].x + ce.t[1].x) / 2;
        tmp.centre.y = (ce.t[0].y + ce.t[1].y) / 2;
    }
    else if(tce == 3) tmp = circumcircleOfTriangle(ce);
    return tmp;
}

void MinCircle(int t, int tce, Triangle ce) {
    Point tmp;
    c = MinCircle2(tce, ce);
    if(tce == 3) return;
    for(int i = 1; i <= t; ++i) {
        if(dist(p[i], c.centre) > c.r) {
            ce.t[tce] = p[i];
            MinCircle(i - 1, tce + 1, ce);
            tmp = p[i];
            for(int j = i; j >= 2; --j) p[j] = p[j - 1];
            p[1] = tmp;
        }
    }
}

double run() {
    Triangle ce;
    MinCircle(n, 0, ce);
    return c.r;
}

double judge(const Point &x, double ans) {
    double ret = dist(x, src);
    if(ret + EPS > ans) return INF;
    for(int i = 1; i <= n; ++i)
        if(dist(p[i], x) > d + EPS) return INF;
    return ret;
}

double solve() {
    double ret = INF;
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j) if(dist(p[i], p[j]) > 2 * d + EPS) return -1;
    if(judge(src, ret) < EPS) return 0;
    for(int i = 1; i <= n; ++i) {
        Point pp = p[i] + small(src - p[i]) * d;
        ret = min(ret, judge(pp, ret));
    }
    if(ret != INF) return ret;
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            Point t1 = (p[i] + p[j]) / 2;
            double dis = len3(dist(p[i], p[j]) / 2, d);
            Point t2 = turn90(p[j] - p[i]);
            ret = min(ret, judge(t1 + t2 * dis, ret));
            Point t3 = turn90(p[i] - p[j]);
            ret = min(ret, judge(t1 + t3 * dis, ret));
        }
    }
    if(ret != INF) return ret;
    return -1;
}

int main() {
    while(scanf("%lf%lf%lf", &src.x, &src.y, &d) != EOF) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) p[i].read();
        double ans;
        //if(run() > d + EPS) ans = -1;
        //else
            ans = solve();
        if(ans < 0) puts("X");
        else printf("%.2f\n", ans);
    }
}
