////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-07-22 13:35:36
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3007
////Problem Title: 
////Run result: Accept
////Run time:93MS
////Run memory:228KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cmath>

const int MAXN = 1010;

struct Point {
    double x, y;
    Point(double xx = 0, double yy = 0): x(xx), y(yy) {}
};

double operator ^ (const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

double dist(const Point &a, const Point &b) {
    double x = a.x - b.x, y = a.y - b.y;
    return sqrt(x * x + y * y);
}

struct Circle {
    double r;
    Point centre;
};

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

Circle c;
Point a[MAXN];

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
        if(dist(a[i], c.centre) > c.r) {
            ce.t[tce] = a[i];
            MinCircle(i - 1, tce + 1, ce);
            //tmp = a[i];
            //for(int j = i; j >= 2; --j) a[j] = a[j - 1];
            //a[1] = tmp;
        }
    }
}

void run(int n) {
    Triangle ce;
    MinCircle(n, 0, ce);
    printf("%.2f %.2f %.2f\n", c.centre.x, c.centre.y, c.r);
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        for(int i = 1; i <= n; ++i)
            scanf("%lf%lf", &a[i].x, &a[i].y);
        run(n);
    }
}
