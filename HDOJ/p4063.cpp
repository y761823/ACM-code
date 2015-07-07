////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-30 18:30:43
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 4063
////Problem Title: 
////Run result: Accept
////Run time:750MS
////Run memory:844KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXN = 22;
const int MAXV = MAXN * MAXN * 2;
const int MAXE = MAXV * MAXV;
const double EPS = 1e-6;
const double INF = 1e100;

inline double sqr(double x) {
    return x * x;
}

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
        if(sgn(x - rhs.x) != 0) return x < rhs.x;
        return sgn(y - rhs.y) < 0;
    }
    bool operator == (const Point &rhs) const {
        return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0;
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
    Point operator * (double d) const {
        return Point(x * d, y * d);
    }
    Point operator / (double d) const {
        return Point(x / d, y / d);
    }
    Point rotate() const {
        return Point(-y, x);
    }
    double length() const {
        return sqrt(*this * *this);
    }
};

double dist(const Point &a, const Point &b) {
    return (a - b).length();
}

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}

double Point_to_Line(const Point &p, const Point &st, const Point &ed) {
    return fabs(cross(p, st, ed)) / dist(st, ed);
}

Point intersection(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}

struct Circle {
    Point c;
    double r;
    Circle() {}
    Circle(Point c, double r): c(c), r(r) {}
    void read() {
        c.read();
        scanf("%lf", &r);
    }
    bool contain(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) + rhs.r - r) <= 0;
    }
    bool contain(const Point &p) const {
        return sgn(dist(c, p) - r) <= 0;
    }
    bool intersect(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) - r - rhs.r) < 0;
    }
    bool tangency(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) - r - rhs.r) == 0;
    }
};

int intersection(const Circle &cir, const Point &st, const Point &ed, Point &p1, Point &p2) {
    if(sgn(Point_to_Line(cir.c, st, ed) - cir.r) > 0) return 0;
    Point p = cir.c + (ed - st).rotate();
    p = intersection(p, cir.c, st, ed);
    double t = sqrt(sqr(cir.r) - sqr(dist(p, cir.c))) / dist(st, ed);
    p1 = p + (ed - st) * t;
    p2 = p - (ed - st) * t;
    return 2 - (p1 == p2);
}

int intersection(const Circle &c1, const Circle &c2, Point &p1, Point &p2) {
    if(c1.contain(c2) || c2.contain(c1)) return 0;
    if(!c1.intersect(c2) && !c1.tangency(c2)) return 0;
    double t = 0.5 * (1 + (sqr(c1.r) - sqr(c2.r)) / sqr(dist(c1.c, c2.c)));
    Point u = c1.c + (c2.c - c1.c) * t, v = u + (c1.c - c2.c).rotate();
    return intersection(c1, u, v, p1, p2);
}

struct Graph {
    int head[MAXV], ecnt;
    int to[MAXE], next[MAXE];
    double cost[MAXE];
    int n, st, ed;

    void init() {
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void add_edge(int u, int v, double c) {
        to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; cost[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    double dis[MAXV];
    bool vis[MAXV];

    double dijksrta(int st, int ed, int n) {
        for(int i = 0; i < n; ++i) dis[i] = INF;
        dis[st] = 0;
        memset(vis, 0, sizeof(vis));
        while(true) {
            int u = -1; double d = INF;
            for(int i = 0; i < n; ++i) if(!vis[i])
                if(dis[i] < d) d = dis[i], u = i;
            if(d == INF) break;
            vis[u] = true;
            for(int p = head[u]; ~p; p = next[p]) {
                int &v = to[p];
                if(!vis[v]) dis[v] = min(dis[v], dis[u] + cost[p]);
            }
        }
        return dis[ed];
    }
} G;

Circle cir[MAXN];
int T, n;

Point list[MAXV];

bool havePath(Point st, Point ed) {
    if(ed < st) swap(st, ed);
    if(st == ed) return true;
    Point p1, p2;
    int pcnt = 0;
    list[pcnt++] = st;
    list[pcnt++] = ed;
    for(int i = 0; i < n; ++i) {
        int c = intersection(cir[i], st, ed, p1, p2);
        if(c >= 1) list[pcnt++] = p1;
        if(c >= 2) list[pcnt++] = p2;
    }
    sort(list, list + pcnt);
    for(int i = 0; i < pcnt; ++i) {
        if(list[i] < st || list[i] == st) continue;
        bool flag = false;
        for(int j = 0; j < n && !flag; ++j)
            if(cir[j].contain(list[i]) && cir[j].contain(list[i - 1])) flag = true;
        if(!flag) return false;
        if(list[i] == ed) break;
    }
    return true;
}

Point p[MAXV];
int cnt;

double solve() {
    Point p1, p2;
    cnt = 0;
    p[cnt++] = cir[0].c; p[cnt++] = cir[n - 1].c;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int c = intersection(cir[i], cir[j], p1, p2);
            if(c >= 1) p[cnt++] = p1;
            if(c >= 2) p[cnt++] = p2;
        }
    }
    G.init();
    for(int i = 0; i < cnt; ++i) {
        for(int j = i + 1; j < cnt; ++j)
            if(havePath(p[i], p[j])) G.add_edge(i, j, dist(p[i], p[j]));
    }
    return G.dijksrta(0, 1, cnt);
}

int main() {
    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) cir[i].read();
        double res = solve();
        if(res == INF) printf("Case %d: No such path.\n", kase);
        else printf("Case %d: %.4f\n", kase, res);
    }
}
