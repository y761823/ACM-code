////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-14 12:26:55
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4573
////Problem Title: 
////Run result: Accept
////Run time:531MS
////Run memory:16100KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXN = 10001;
const double EPS = 1e-9;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y, z;
    Point() {}
    Point(double x, double y, double z): x(x), y(y), z(z) {}
    void read() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    double operator * (const Point &rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
};
double length(const Point &a) {
    return sqrt(a * a);
}
Point cross(const Point &a, const Point &b) {
    Point res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}
Point cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}
double volume(const Point &a, const Point &b, const Point &c, const Point &d) {
    return cross(c - a , b - a) * (d - a) / 6;
}
Point p[MAXN];

struct Face {
    int a, b, c;
    bool flag;
    Face() {}
    Face(int a, int b, int c, bool flag): a(a), b(b), c(c), flag(flag) {}
    bool can_see(const Point &q) {
        return sgn(volume(p[a], p[b], p[c], q)) > 0;
    }
};
Face fac[MAXN * 10];

struct Convex {
    double diff_vol;
    int cnt, mat[MAXN][MAXN];

    void init() {
        cnt = 0;
        for(int i = 0; i < 4; ++i) {
            Face newf = Face((i + 1) % 4, (i + 2) % 4, (i + 3) % 4, true);
            if(newf.can_see(p[i])) swap(newf.a, newf.c);
            mat[newf.a][newf.b] = mat[newf.b][newf.c] = mat[newf.c][newf.a] = cnt;
            fac[cnt++] = newf;
        }
    }

    void restore(int k, int a, int b) {
        int f = mat[a][b];
        if(fac[f].flag) {
            if(fac[f].can_see(p[k])) dfs(k, f);
            else {
                mat[b][a] = mat[a][k] = mat[k][b] = cnt;
                fac[cnt++] = Face(b, a, k, true);
            }
        }
    }

    void dfs(int k, int f) {
        diff_vol += volume(p[fac[f].a], p[fac[f].b], p[fac[f].c], p[k]);
        fac[f].flag = false;
        restore(k, fac[f].b, fac[f].a);
        restore(k, fac[f].c, fac[f].b);
        restore(k, fac[f].a, fac[f].c);
    }

    double update(int k) {
        diff_vol = 0;
        for(int i = 0; i < cnt; ++i) {
            if(!fac[i].flag || !fac[i].can_see(p[k])) continue;
            dfs(k, i);
            break;
        }
        return diff_vol;
    }

    double vol() {
        double res = 0;
        for(int i = 0; i < cnt; ++i) if(fac[i].flag)
            res -= volume(p[fac[i].a], p[fac[i].b], p[fac[i].c], Point(0, 0, 0));
        return res;
    }
} solver;

int n, kase;

void solve() {
    int king = 0;
    double maxans = 0;
    for(int i = 1, tmp = 1; i < n; ++i) {
        if(tmp == 1) {
            tmp += sgn(length(p[0] - p[i]));
            if(tmp > 1) swap(p[1], p[i]);
        } else if(tmp == 2) {
            tmp += sgn(length(cross(p[0], p[1], p[i])));
            if(tmp > 2) swap(p[2], p[i]);
        } else if(tmp == 3) {
            tmp += (sgn(volume(p[0], p[1], p[2], p[i])) != 0);
            if(tmp > 3) {
                swap(p[3], p[i]);
                solver.init();
                for(int j = 4; j <= i; ++j) solver.update(j);
                king = i, maxans = solver.vol();
            }
        } else {
            double v = solver.update(i);
            if(sgn(v - maxans) > 0) {
                maxans = v;
                king = i;
            }
        }
    }
    printf("%d %.2f\n", king + 1, maxans);
}

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i) p[i].read();
        printf("Case #%d:\n", ++kase);
        solve();
    }
}
