#include <cstdio>
#include <cmath>

#define EPS 1e-10
#define Abs(x) x>0?x:-x

typedef double TYPE;
//2D point
struct Point {
    TYPE x, y;
    Point() {}
    Point(double xx, double yy): x(xx), y(yy) {};

    bool operator < (const Point &B) const {
        if(x == B.x) return y < B.y;
        else return x < B.x;
    }
};
//if return>0 then a is on the clockwise of b
TYPE cross(const Point &a, const Point &b, const Point &o) {
    return (o.x - a.x) * (o.y - b.y) - (o.x - b.x) * (o.y - a.y);
}
//distance between a and b
inline double dist(Point a, Point b){
    double x = a.x - b.x, y = a.y - b.y;
    return sqrt(x * x + y * y);
}
//2D twp-point form segment
struct Seg {
    Point st, ed;
    Seg() {}
    Seg(Point aa, Point bb):st(aa), ed(bb) {}
};
//if a straddle b
inline bool straddle(const Seg &A, const Seg &B) {
    return cross(B.st, A.st, B.ed) * cross(B.st, A.ed, B.ed) < EPS;
}

#define MAXN 110

int T, n;
Seg sg[MAXN];

inline bool check(Seg p) {
    if(dist(p.st, p.ed) < EPS) return false;
    for(int i = 0; i < n; ++i)
        if(!straddle(sg[i], p)) return false;
    return true;
}

bool solve() {
    for(int i = 0; i < n; ++i) for(int j = i+1; j < n; ++j) {
        if(check(Seg(sg[i].st, sg[j].st))) return true;
        if(check(Seg(sg[i].st, sg[j].ed))) return true;
        if(check(Seg(sg[i].ed, sg[j].st))) return true;
        if(check(Seg(sg[i].ed, sg[j].ed))) return true;
    }
    return false;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%lf%lf%lf%lf", &sg[i].st.x, &sg[i].st.y, &sg[i].ed.x, &sg[i].ed.y);
        if(n == 1 || solve()) puts("Yes!");
        else puts("No!");
    }
}
