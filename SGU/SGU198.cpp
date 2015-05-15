#include <bits/stdc++.h>
using namespace std;

const int MAXV = 310;
const int MAXE = MAXV * MAXV;
const double EPS = 1e-9;

int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    double operator * (const Point &rhs) const {
        return x * rhs.x + y * rhs.y;
    }
};

double dist(const Point &a, const Point &b) {
    return hypot(a.x - b.x, a.y - b.y);
}

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double angle(const Point &a, const Point &b) {
    return atan2(cross(a, b), a * b);
}

int u[MAXE], v[MAXE];
double cost[MAXE];
double dis[MAXV];
int ecnt;

void add_edge(int a, int b, double c) {
    u[ecnt] = a; v[ecnt] = b; cost[ecnt++] = c;
}

bool bellman_ford(int n) {
    for(int zz = 0; zz < n; ++zz) {
        bool flag = false;
        for(int i = 0; i < ecnt; ++i) {
            double d = dis[u[i]] + cost[i];
            if(sgn(d - dis[v[i]]) < 0) {
                dis[v[i]] = d;
                flag = true;
            }
        }
        if(!flag) return false;
    }
    return true;
}

Point p[MAXV];
double r[MAXV];
int n;

int main() {
    scanf("%d", &n);
    for(int i = 0; i <= n; ++i)
        scanf("%lf%lf%lf", &p[i].x, &p[i].y, &r[i]);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) if(i != j) {
            if(sgn(r[i] + r[j] + r[n] + r[n] - dist(p[i], p[j])) > 0)
                add_edge(i, j, angle(p[i] - p[n], p[j] - p[n]));
        }
    }
    puts(bellman_ford(n) ? "NO" : "YES");
}
