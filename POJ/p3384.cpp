#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-8
#define MAXN 1000

inline int sgn(double x) {
    if(fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}

struct Point {
    double x, y;
    Point(double xx = 0, double yy = 0): x(xx), y(yy) {}
    bool operator == (const Point &b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
};
//cross
inline double operator ^ (const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

inline Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

struct Line {
    Point s, e;
    double ag;
};

struct polygon {
    Point v[MAXN];
    int n;
} pg, res;

inline double dist(Point &a, Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double Cross(Point o, Point s, Point e) {
    return (s - o) ^ (e - o);
}
//cross_point
Point operator * (const Line &a, const Line &b) {
    Point res;
    double u = Cross(a.s, a.e, b.s), v = Cross(a.e, a.s, b.e);
    res.x = (b.s.x * v + b.e.x * u)/(u + v);
    res.y = (b.s.y * v + b.e.y * u)/(u + v);
    return res;
}

int parallel(Line a, Line b) {
    double u = (a.e.x - a.s.x) * (b.e.y - b.s.y) - (a.e.y - a.s.y) * (b.e.x - b.s.x);
    return sgn(u) == 0;
}

inline void set_vector(double x1, double y1, double x2, double y2, Line &v) {
    v.s.x = x1; v.s.y = y1;
    v.e.x = x2; v.e.y = y2;
    v.ag = atan2(y2 - y1, x2 - x1);
}

Line vct[MAXN], deq[MAXN];

bool cmp(const Line &a, const Line &b) {
    if(sgn(a.ag - b.ag) == 0)
        return sgn(Cross(b.s, b.e, a.s)) < 0;
    return a.ag < b.ag;
}

int half_planes_cross(Line *v, int vn) {
    int i, n;
    //sort(v, v + vn, cmp);
    for(i = n = 1; i < vn; ++i) {
        if(sgn(v[i].ag - v[i-1].ag) == 0) continue;
        v[n++] = v[i];
    }
    int head = 0, tail = 1;
    deq[0] = v[0], deq[1] = v[1];
    for(i = 2; i < n; ++i) {
        if(parallel(deq[tail - 1], deq[tail]) || parallel(deq[head], deq[head + 1]))
            return false;
        while(head < tail && sgn(Cross(v[i].s, v[i].e, deq[tail - 1] * deq[tail])) > 0)
            --tail;
        while(head < tail && sgn(Cross(v[i].s, v[i].e, deq[head] * deq[head + 1])) > 0)
            ++head;
        deq[++tail] = v[i];
    }
    while(head < tail && sgn(Cross(deq[head].s, deq[head].e, deq[tail - 1] * deq[tail])) > 0)
        --tail;
    while(head < tail && sgn(Cross(deq[tail].s, deq[tail].e, deq[head] * deq[head + 1])) > 0)
        ++head;
    if(tail <= head + 1) return false;
    res.n = 0;
    for(i = head; i < tail; ++i)
        res.v[res.n++] = deq[i] * deq[i + 1];
    res.v[res.n++] = deq[head] * deq[tail];
    res.n = unique(res.v, res.v + res.n) - res.v;
    res.v[res.n] = res.v[0];
    return true;
}

void moving(Line v[], int vn, double r) {
    for(int i = 0; i < vn; ++i) {
        double dx = v[i].e.x - v[i].s.x, dy = v[i].e.y - v[i].s.y;
        dx = dx / dist(v[i].s, v[i].e) * r;
        dy = dy / dist(v[i].s, v[i].e) * r;
        v[i].s.x += dy; v[i].e.x += dy;
        v[i].s.y -= dx; v[i].e.y -= dx;
    }
}

int ix, jx;

double dia_roataing_calipers() {
    double dia = 0;
    ix = jx = 0;
    int q = 1;
    for(int i = 0; i < res.n; ++i) {
        while(sgn(Cross(res.v[i+1], res.v[i], res.v[q+1]) - Cross(res.v[i+1], res.v[i], res.v[q])) > 0)
            q = (q + 1) % res.n;
        if(sgn(dist(res.v[i], res.v[q]) - dia) > 0) {
            dia = dist(res.v[i], res.v[q]);
            ix = i; jx = q;
        }
        if(sgn(dist(res.v[i+1], res.v[q]) - dia) > 0) {
            dia = dist(res.v[i+1], res.v[q]);
            ix = i+1; jx = q;
        }
    }
    return dia;
}

int main() {
    int n;
    double r;
    while(scanf("%d%lf", &n, &r) != EOF) {
        for(int i = 0; i < n; ++i) scanf("%lf%lf", &pg.v[i].x, &pg.v[i].y);
        pg.v[n] = pg.v[0];
        for(int i = 0; i < n; ++i)
            set_vector(pg.v[i].x, pg.v[i].y, pg.v[i+1].x, pg.v[i+1].y, vct[i]);
        moving(vct, n, r);
        half_planes_cross(vct, n);
        /*
        int ix = 0, jx = 0;
        double maxdis = 0;
        for(int i = 0; i < res.n; ++i) {
            for(int j = 0; j < res.n; ++j) {
                if(i == j) continue;
                double t = dist(res.v[i], res.v[j]);
                if(sgn(t - maxdis) > 0) {
                    maxdis = t;
                    ix = i, jx = j;
                }
            }
        }*/
        //printf("%.4f\n", dia_roataing_calipers());
        dia_roataing_calipers();
        printf("%.4f %.4f %.4f %.4f\n", res.v[ix].x, res.v[ix].y, res.v[jx].x, res.v[jx].y);
    }
}
