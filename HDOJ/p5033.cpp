////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-21 21:15:28
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5033
////Problem Title: 
////Run result: Accept
////Run time:671MS
////Run memory:4244KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define sqr(x) ((x) * (x))

typedef long long LL;
typedef long double LD;

const int MAXN = 100010;
const double EPS = 1e-8;
const double PI = acos(-1.0);//3.14159265358979323846
const double INF = 1;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    bool operator < (const Point &rhs) const {
        return x < rhs.x;
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
};

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}

struct Query {
    double x;
    int id;
    void read(int i) {
        id = i;
        scanf("%lf", &x);
    }
    bool operator < (const Query &rhs) const {
        return x < rhs.x;
    }
} que[MAXN];
Point p[MAXN], stk[MAXN];
int T, n, q, top;
double ans[MAXN];

void solve() {
    for(int i = 0; i < q; ++i)
        ans[i] = 0;

    stk[top = 1] = p[0];
    for(int i = 1, j = 0; i < n; ++i) {
        while(j < q && que[j].x <= p[i].x) {
            while(top >= 2 && cross(Point(que[j].x, 0), stk[top], stk[top - 1]) <= 0)
                --top;
            ans[que[j].id] += atan2(stk[top].y, que[j].x - stk[top].x);
            ++j;
        }
        while(top >= 2 && cross(p[i], stk[top], stk[top - 1]) <= 0) --top;
        while(top && stk[top].y <= p[i].y) --top;
        stk[++top] = p[i];
    }

    stk[top = 1] = p[n - 1];
    for(int i = n - 2, j = q - 1; i >= 0; --i) {
        while(j >= 0 && que[j].x >= p[i].x) {
            while(top >= 2 && cross(Point(que[j].x, 0), stk[top], stk[top - 1]) >= 0)
                --top;
            ans[que[j].id] += atan2(stk[top].y, stk[top].x - que[j].x);
            --j;
        }
        while(top >= 2 && cross(p[i], stk[top], stk[top - 1]) >= 0) --top;
        while(top && stk[top].y <= p[i].y) -- top;
        stk[++top] = p[i];
    }

    for(int i = 0; i < q; ++i)
        printf("%.10f\n", (PI - ans[i]) * 180 / PI);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) p[i].read();
        sort(p, p + n);
        scanf("%d", &q);
        for(int i = 0; i < q; ++i) que[i].read(i);
        sort(que, que + q);
        printf("Case #%d:\n", t);
        solve();
    }
}
