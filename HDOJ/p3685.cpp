////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-04-06 17:54:02
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3685
////Problem Title: 
////Run result: Accept
////Run time:281MS
////Run memory:1224KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 50010;
const double EPS = 1e-10;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    double operator * (const Point &rhs) const {
        return x * rhs.x + y * rhs.y;
    }
    Point operator / (const double &rhs) const {
        return Point(x / rhs, y / rhs);
    }
    bool operator < (const Point &rhs) const {
        if(y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
};
typedef Point Vector;

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double cross(const Point &sp, const Point &op, const Point &ep) {
    return cross(sp - op, ep - op);
}

void Graham_scan(Point *p, int n, int *stk, int &top) {
    sort(p, p + n);
    top = 1;
    stk[0] = 0; stk[1] = 1;
    for(int i = 2; i < n; ++i) {
        while(top && cross(p[stk[top - 1]], p[stk[top]], p[i]) <= 0) --top;
        stk[++top] = i;
    }
    int len = top;
    stk[++top] = n - 2;
    for(int i = n - 3; i >= 0; --i) {
        while(top != len && cross(p[stk[top - 1]], p[stk[top]], p[i]) <= 0) --top;
        stk[++top] = i;
    }
}

Point barycenter(Point *p, int n) {
    double area = 0;
    Point res;
    for(int i = 0; i < n; ++i) {
        double t = cross(p[i], p[i + 1]) / 2;
        res.x += t * (p[i].x + p[i + 1].x) / 3;
        res.y += t * (p[i].y + p[i + 1].y) / 3;
        area += t;
    }
    return res / area;
}

Point p[MAXN];
int stk[MAXN], top;
int n, T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) p[i].read();
        p[n] = p[0];
        Point O = barycenter(p, n);
        Graham_scan(p, n, stk, top);

        int ans = 0;
        for(int i = 0; i < top; ++i) {
            Point &A = p[stk[i]], &B = p[stk[i + 1]];
            ans += (sgn((O - A) * (B - A)) > 0 && sgn((O - B) * (A - B)) > 0);
        }
        printf("%d\n", ans);
    }
}
