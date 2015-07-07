////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-23 17:57:29
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3694
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:320KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const double EPS = 1e-8;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    bool read() {
        return scanf("%lf%lf", &x, &y) != EOF;
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    double length() {
        return sqrt(x * x + y * y);
    }
};

double dist(const Point &a, const Point &b) {
    return (a - b).length();
    //return hypot(a.x - b.x, a.y - b.y);
}

struct Seg {
    Point st, ed;
    Seg() {}
    Seg(Point st, Point ed):st(st), ed(ed) {}
};
typedef Seg Line;

void Coefficient(const Line &L, double &A, double &B, double &C) {
    A = L.ed.y - L.st.y;
    B = L.st.x - L.ed.x;
    C = L.ed.x * L.st.y - L.st.x * L.ed.y;
}

Point operator * (const Line &a, const Line &b) {
    double A1, B1, C1, A2, B2, C2;
    Coefficient(a, A1, B1, C1);
    Coefficient(b, A2, B2, C2);
    Point I;
    if(fabs(A1 * B2 - A2 * B1) < EPS) return I;
    I.x = - (B2 * C1 - B1 * C2) / (A1 * B2 - A2 * B1);
    I.y =   (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);
    return I;
}

Point p[4];
int n = 4;

double sum_dist(const Point &t) {
    double ret = 0;
    for(int i = 0; i < n; ++i)
        ret += dist(p[i], t);
    return ret;
}

double solve() {
    double ans = 1e100;
    for(int i = 0; i < n; ++i)
        ans = min(ans, sum_dist(p[i]));
    ans = min(ans, sum_dist(Seg(p[0], p[1]) * Seg(p[2], p[3])));
    ans = min(ans, sum_dist(Seg(p[0], p[2]) * Seg(p[1], p[3])));
    ans = min(ans, sum_dist(Seg(p[0], p[3]) * Seg(p[1], p[2])));
    return ans;
}

int main() {
    while(true) {
        for(int i = 0; i < n; ++i)
            if(!p[i].read()) return 0;
        if(p[0].x < 0) break;
        printf("%.4f\n", solve());
    }
}
